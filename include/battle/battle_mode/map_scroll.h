#ifndef BATTLE_BATTLE_MODE_MAP_SCROLL_H
#define BATTLE_BATTLE_MODE_MAP_SCROLL_H

/* The scroll of the battle map: the stylus near an edge of the screen scrolls
 * it, and a task runs it every frame. */

#include "types.h"

void setMapScroll(s16 x, s16 y);
void enableTouchScroll(void);
void disableTouchScroll(void);
void scrollMapByTouch(void);
void tickMapScrollTask(void);
void func_ov002_0222b5d8(void);
s32 func_ov002_0222b240();

#endif /* BATTLE_BATTLE_MODE_MAP_SCROLL_H */
