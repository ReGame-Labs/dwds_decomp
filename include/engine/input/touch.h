#ifndef ENGINE_INPUT_TOUCH_H
#define ENGINE_INPUT_TOUCH_H

#include "types.h"

/* The touch screen: its state, sampled each frame, and its taps. */

struct Touch;

u16 getTouchY(void);
u16 getTouchX(void);
u16 getTouchTap(void);
u16 getTouchRepeat(void);
u16 getTouchFastRepeat(void);
u16 getTouchReleased(void);
u16 getTouchPressed(void);
void setTouchDisabled(s32 off);
void clearTouch(void);
void tickTouch(void);
u16 getTouchHeld(void);
void updateTouch(struct Touch *touch, u16 touching);
BOOL isTouchTap(struct Touch *touch);
BOOL isTouchDoubleTap(struct Touch *touch);

#endif /* ENGINE_INPUT_TOUCH_H */
