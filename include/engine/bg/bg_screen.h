#ifndef ENGINE_BG_BG_SCREEN_H
#define ENGINE_BG_BG_SCREEN_H

#include "types.h"

/* The sprites' creation at a place, the screen of two backgrounds
 * (tickBgScreen) and the clearing of both screens. */

struct BgScreenTask;

s32 createSubSpriteAt();
s32 createMainSpriteAt();
void clearScreens(void);
u8 isBgScreenDone(void);
void closeBgScreen(struct BgScreenTask *task);
s32 func_020419c0();
s16 countWifiFriends(void);
void *getSpriteOffset(u16 id);
void tickBgScreen();
s32 initSprites();

#endif /* ENGINE_BG_BG_SCREEN_H */
