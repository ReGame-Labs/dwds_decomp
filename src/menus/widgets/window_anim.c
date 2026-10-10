#include "menus/widgets/window_anim.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/text/font.h"
#include "engine/window/window.h"
#include "menus/widgets/digimon_detail_draw.h"
#include "menus/widgets/icon_display.h"
#include "menus/widgets/item_displays.h"
#include "menus/widgets/item_menu_panel.h"
#include "menus/widgets/number_display.h"
#include "menus/widgets/skill_displays.h"
#include "menus/widgets/status_window_draw.h"

/* The menu displays' task: draws every display, then runs the windows'
 * slides and close animations. */
void tickMenuDisplays(void) {
    func_02059028();
    func_02057770();
    drawNumberDisplays();
    func_02055de4();
    func_02053bf4();
    func_020534b4();
    func_02052f6c();
    func_0205244c();
    func_0205140c();
    func_02050974();
    func_0204fc04();
    func_0204f5f4();
    func_0204ed70();
    func_0204e0c8();
    placeIconDisplaySprite();
    tickWindowSlides();
    tickWindowCloses();
}

/* Starts sliding a window to params' position, in one of 8 slots; does
 * nothing when every slot is busy. */
void startWindowSlide(const struct WindowSlideParams *params) {
    s32 i;
    struct WindowSlide *slide;
    struct Window *window;

    slide = WINDOW_SLIDES;
    for (i = 0; i < 8; i++) {
        if (slide->flags == 0) {
            break;
        }
        slide++;
    }
    if (i == 8) {
        return;
    }
    slide          = &WINDOW_SLIDES[i];
    window         = getWindow(params->window);
    slide->flags   = 1;
    slide->window  = params->window;
    slide->targetX = params->x;
    slide->targetY = params->y;
    slide->speed   = params->speed;
    slide->stepX   = slide->targetX - window->x;
    if (slide->stepX < 0) {
        slide->stepX = -slide->speed;
    } else if (slide->stepX > 0) {
        slide->stepX = slide->speed;
    } else {
        slide->stepX = 0;
    }
    slide->stepY = slide->targetY - window->y;
    if (slide->stepY < 0) {
        slide->stepY = -slide->speed;
    } else if (slide->stepY > 0) {
        slide->stepY = slide->speed;
    } else {
        slide->stepY = 0;
    }
}

/* Whether the window has no slide going on: 0 while it slides. */
s32 isWindowSlideDone(s32 window) {
    s32 i;
    struct WindowSlide *slide;

    slide = WINDOW_SLIDES;
    for (i = 0; i < 8; i++) {
        if ((slide->flags & 1) && slide->window == window) {
            return 0;
        }
        slide++;
    }
    return 1;
}

/* Moves every sliding window a step and ends the slides that arrived. */
s32 tickWindowSlides(void) {
    s32 result;
    s32 i;
    struct WindowSlide *slide;

    slide = WINDOW_SLIDES;
    for (i = 0; i < 8; i++) {
        result = slide->flags & 1;
        if (result != 0) {
            result = stepWindowSlide(slide->window, slide->targetX, slide->targetY, slide->stepX, slide->stepY);
            if (result == 1) {
                result = endWindowSlide(slide->window);
            }
        }
        slide++;
    }
    return result;
}

/* Starts closing a window, in one of 8 slots; does nothing when every slot
 * is busy. */
void startWindowClose(const struct WindowCloseParams *params) {
    s32 i;
    struct WindowCloseAnim *anim;

    anim = WINDOW_CLOSES;
    for (i = 0; i < 8; i++) {
        if (anim->flags == 0) {
            break;
        }
        anim++;
    }
    if (i == 8) {
        return;
    }
    anim        = &WINDOW_CLOSES[i];
    anim->state = 0;
    anim->flags = 1;
    anim->flags |= params->flags;
    anim->window = params->window;
    anim->width  = 100;
    anim->height = 100;
    anim->step   = -15;
}

/* Whether the window has no close animation going on: 0 while it closes. */
s32 isWindowCloseDone(s32 window) {
    s32 i;
    struct WindowCloseAnim *anim;

    anim = WINDOW_CLOSES;
    for (i = 0; i < 8; i++) {
        if ((anim->flags & 1) && anim->window == window) {
            return 0;
        }
        anim++;
    }
    return 1;
}

/* Runs a frame of every window's close animation. */
void tickWindowCloses(void) {
    s32 i;
    struct WindowCloseAnim *anim;

    anim = WINDOW_CLOSES;
    for (i = 0; i < 8; i++) {
        if (anim->flags & 1) {
            tickWindowClose(anim);
        }
        anim++;
    }
}

/* Loads the window frame (file 0x60) into the given graphics slot for the
 * main screen's windows, unloading the one loaded before. */
s32 loadMainWindowFrameInSlot(s8 slot, s32 value) {
    void *files;

    files = func_0204871c(0x60);
    if (MAIN_WINDOW_FRAME_SLOT != -1) {
        unloadMainWindowFrame();
    }
    MAIN_WINDOW_FRAME_SLOT = slot;
    return func_020aa2c0(files, slot, -1, value);
}

/* Loads the window frame (file 0x60) into the given graphics slot for the
 * sub screen's windows, unloading the one loaded before. */
s32 loadSubWindowFrameInSlot(s8 slot, s32 value) {
    void *files;

    files = func_0204871c(0x60);
    if (SUB_WINDOW_FRAME_SLOT != -1) {
        unloadSubWindowFrame();
    }
    SUB_WINDOW_FRAME_SLOT = slot;
    return func_020aa29c(files, slot, -1, value);
}

/* Unloads the main screen's window frame. */
void unloadMainWindowFrame(void) {
    if (MAIN_WINDOW_FRAME_SLOT == -1) {
        return;
    }
    func_020a9610(MAIN_WINDOW_FRAME_SLOT);
    MAIN_WINDOW_FRAME_SLOT = -1;
}

/* Unloads the sub screen's window frame. */
void unloadSubWindowFrame(void) {
    if (SUB_WINDOW_FRAME_SLOT == -1) {
        return;
    }
    func_020a9610(SUB_WINDOW_FRAME_SLOT);
    SUB_WINDOW_FRAME_SLOT = -1;
}
