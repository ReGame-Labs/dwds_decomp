#include "engine/input/touch.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "nitro/tp.h"

#define PI 3.141592653589793

/* MSL's float atan2, the double one (func_0203a234) between two conversions. */
static inline float atan2f(float y, float x) {
    return func_0203a234(y, x);
}

/* The touch screen's task: samples the panel and updates the touch state
 * from it, unless that is switched off. A coordinate the panel could not read
 * keeps its old value. */
void tickTouch(void) {
    struct TPData raw;
    struct TPData point;

    while (TP_RequestRawSampling(&raw) != 0) {
    }
    func_020e70a8(&point, &raw);

    if (point.touch != 0) {
        switch (point.validity) {
            case TP_VALIDITY_VALID:
                TOUCH.prevX   = TOUCH.x;
                TOUCH.prevY   = TOUCH.y;
                TOUCH.x       = point.x;
                TOUCH.y       = point.y;
                TOUCH.offsetX = point.x + TOUCH.xOffset;
                TOUCH.offsetY = point.y + TOUCH.yOffset;
                break;
            case TP_VALIDITY_INVALID_X:
                TOUCH.prevY   = TOUCH.y;
                TOUCH.y       = point.y;
                TOUCH.offsetY = point.y + TOUCH.yOffset;
                break;
            case TP_VALIDITY_INVALID_Y:
                TOUCH.prevX   = TOUCH.x;
                TOUCH.x       = point.x;
                TOUCH.offsetX = point.x + TOUCH.xOffset;
                break;
            case TP_VALIDITY_INVALID_XY:
                break;
        }
    }
    if (TOUCH_DISABLED == 0) {
        updateTouch(&TOUCH, point.touch);
    }
}

/* Whether the screen was touched again within 8 pixels of the first touch of
 * a double tap. */
BOOL isTouchDoubleTap(struct Touch *touch) {
    s16 dx;
    s16 dy;

    if (touch->pressed != 0) {
        dx = touch->x - touch->doubleTapX;
        dy = touch->y - touch->doubleTapY;
        return (dx < 0 ? -dx : dx) <= 8 && (dy < 0 ? -dy : dy) <= 8;
    }
    return FALSE;
}

/* Whether the screen was let go within 8 pixels of where a tap began. */
BOOL isTouchTap(struct Touch *touch) {
    s16 dx;
    s16 dy;

    if (touch->released != 0) {
        dx = touch->x - touch->tapX;
        dy = touch->y - touch->tapY;
        return (dx < 0 ? -dx : dx) <= 8 && (dy < 0 ? -dy : dy) <= 8;
    }
    return FALSE;
}

/* Updates the touch state like a pad's, from whether the screen is touched,
 * and tracks the taps, the double taps and the flicks. */
void updateTouch(struct Touch *touch, u16 touching) {
    s32 angle;

    touch->prevHeld = touch->held;
    touch->held     = touching;
    touch->pressed  = ~touch->prevHeld & touch->held;
    touch->released = ~touch->held & touch->prevHeld;

    if (touch->held != touch->prevHeld) {
        touch->holdFrames = 0;
    } else if (touch->holdFrames < 16) {
        touch->holdFrames++;
    }
    touch->fastRepeat = touch->holdFrames >= 16 ? touch->held : touch->pressed;

    if (touch->held != touch->prevHeld) {
        touch->longHoldFrames = 0;
    } else if (touch->holdFrames >= 16 && touch->longHoldFrames < 60) {
        touch->longHoldFrames++;
    }
    touch->longHeld = touch->longHoldFrames >= 60 ? touch->held : 0;

    if (touch->held != touch->prevHeld) {
        touch->repeatFrames = 0;
    } else if (touch->holdFrames >= 16) {
        touch->repeatFrames++;
    }
    touch->repeat = touch->repeatFrames >= 4 ? touch->held : touch->pressed;
    if (touch->repeatFrames >= 4) {
        touch->repeatFrames = 0;
    }

    switch (touch->doubleTapState) {
        case 0:
            if (touch->pressed != 0) {
                touch->doubleTapX      = touch->x;
                touch->doubleTapY      = touch->y;
                touch->doubleTapFrames = 0;
                touch->doubleTapState  = 1;
            }
            break;
        case 1:
            touch->doubleTapFrames++;
            if (touch->doubleTapFrames > 20) {
                touch->doubleTapFrames = 0;
                touch->doubleTapState  = 0;
            } else if (isTouchDoubleTap(touch)) {
                touch->doubleTap       = touch->pressed;
                touch->doubleTapFrames = 0;
                touch->doubleTapState  = 2;
            }
            break;
        case 2:
            touch->doubleTap       = 0;
            touch->doubleTapFrames = 0;
            touch->doubleTapState  = 0;
            break;
    }

    switch (touch->tapState) {
        case 0:
            if (touch->pressed != 0) {
                touch->tapX       = touch->x;
                touch->tapY       = touch->y;
                touch->tapOffsetX = touch->offsetX;
                touch->tapOffsetY = touch->offsetY;
                touch->tapFrames  = 0;
                touch->tapState   = 1;
            }
            break;
        case 1:
            touch->tapFrames++;
            if (touch->tapFrames > 20) {
                touch->tapFrames = 0;
                touch->tapState  = 0;
            } else if (isTouchTap(touch)) {
                touch->tap       = touch->released;
                touch->tapFrames = 0;
                touch->tapState  = 2;
            }
            break;
        case 2:
            touch->tap       = 0;
            touch->tapFrames = 0;
            touch->tapState  = 0;
            break;
    }

    if (touch->released != 0) {
        angle             = wrapAngle(atan2f(touch->y - touch->prevY, touch->x - touch->prevX) * (180.0 / PI), 0);
        touch->flickSpeed = func_0202d600((touch->prevX - touch->x) * (touch->prevX - touch->x) +
                                          (touch->prevY - touch->y) * (touch->prevY - touch->y));
        touch->flickAngle = angle;
        touch->flick      = touch->flickSpeed > 10;
    } else {
        touch->flick = 0;
    }
}

/* Clears the touch state. */
void clearTouch(void) {
    func_020e23c0(&TOUCH, 0, sizeof(struct Touch));
}

/* Switches the touch state's updates off (nonzero) or on. */
void setTouchDisabled(s32 off) {
    TOUCH_DISABLED = off;
}

/* Whether the screen is touched, as a pad's button is held. */
u16 getTouchHeld(void) {
    return TOUCH.held;
}

/* Whether the screen was touched this frame. */
u16 getTouchPressed(void) {
    return TOUCH.pressed;
}

/* Whether the touch was let go this frame. */
u16 getTouchReleased(void) {
    return TOUCH.released;
}

/* Whether the touch repeats this frame, at the fast rate. */
u16 getTouchFastRepeat(void) {
    return TOUCH.fastRepeat;
}

/* Whether the touch repeats this frame. */
u16 getTouchRepeat(void) {
    return TOUCH.repeat;
}

/* Whether the screen was tapped. */
u16 getTouchTap(void) {
    return TOUCH.tap;
}

/* The x of the point last touched. */
u16 getTouchX(void) {
    return TOUCH.x;
}

/* The y of the point last touched. */
u16 getTouchY(void) {
    return TOUCH.y;
}
