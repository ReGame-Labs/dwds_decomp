#ifndef BATTLE_BATTLE_MODE_BATTLE_H
#define BATTLE_BATTLE_MODE_BATTLE_H

/* The battle's state, its table of random numbers that both DS of a link
 * battle share, and the loading of the backgrounds' graphics. */

#include "types.h"

struct Battle;
struct BgGraphics;

void freeBattleBgGraphics(struct BgGraphics *gfx);
struct Battle *getBattle(void);
s32 tickBattleTask();
void loadBattleBgGraphics(s32 index, struct BgGraphics *gfx);
void applyBattleDispSelect(void);
u32 getBattleRandom(u32 range);

#endif /* BATTLE_BATTLE_MODE_BATTLE_H */
