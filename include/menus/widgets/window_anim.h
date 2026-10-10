#ifndef MENUS_WIDGETS_WINDOW_ANIM_H
#define MENUS_WIDGETS_WINDOW_ANIM_H

/* Menu windows: their frame graphics, the slide and close animations, and the
 * task that draws every menu display. */

#include "types.h"

/* A window moving to a target position, speed tiles a frame. */
struct WindowSlide {
    /* 0x0 */ u8 flags; /* bit 0: in use */
    /* 0x1 */ u8 window;
    /* 0x2 */ s16 targetX;
    /* 0x4 */ s16 targetY;
    /* 0x6 */ s16 stepX;
    /* 0x8 */ s16 stepY;
    /* 0xA */ s16 speed;
};

struct WindowSlideParams {
    /* 0x0 */ u8 window;
    /* 0x2 */ s16 x;
    /* 0x4 */ s16 y;
    /* 0x6 */ s16 speed;
};

/* A window closing: it shrinks to a line by step percent a frame, then to
 * nothing, and is freed when flags has bit 2. */
struct WindowCloseAnim {
    /* 0x0 */ u16 state;
    /* 0x2 */ u8 flags; /* bit 0: in use */
    /* 0x3 */ u8 window;
    /* 0x4 */ s16 width;  /* percent */
    /* 0x6 */ s16 height; /* percent */
    /* 0x8 */ s16 step;
};

struct WindowCloseParams {
    /* 0x0 */ u8 window;
    /* 0x1 */ u8 flags;
};

extern struct WindowCloseAnim WINDOW_CLOSES[8];
extern struct WindowSlide WINDOW_SLIDES[8];

void startWindowSlide(const struct WindowSlideParams *params);
void tickMenuDisplays(void);
s8 createMenuWindow();
void unloadSubWindowFrame(void);
void unloadMainWindowFrame(void);
s32 tickWindowSlides(void);
s32 stepWindowSlide();
s32 endWindowSlide();
s32 isWindowSlideDone(s32 window);
s32 loadSubWindowFrameInSlot(s8 slot, s32 value);
s32 loadMainWindowFrameInSlot(s8 slot, s32 value);
void tickWindowCloses(void);
void tickWindowClose();
s32 isWindowCloseDone(s32 window);
void startWindowClose(const struct WindowCloseParams *params);

#endif /* MENUS_WIDGETS_WINDOW_ANIM_H */
