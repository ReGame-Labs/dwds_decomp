#ifndef ENGINE_BG_BG_SCREEN_TASK_H
#define ENGINE_BG_BG_SCREEN_TASK_H

#include "types.h"

/* The start and the end of tickBgScreen's task, and the freeing of a
 * background's graphics. */

void freeBgScreenTask(void);
void freeBgGraphics(void *graphics); /* a struct BgGraphics */
s32 func_020422ac();
s32 func_020423f0();
s32 func_0204252c();
void startBgScreenTask(void *arg);
void func_02041fe4();

#endif /* ENGINE_BG_BG_SCREEN_TASK_H */
