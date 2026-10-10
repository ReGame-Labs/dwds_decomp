#ifndef BATTLE_BATTLE_MODE_START_BATTLE_H
#define BATTLE_BATTLE_MODE_START_BATTLE_H

/* The start of the battle's task, and the units' skills, MP costs and
 * abilities as the battle reads them. */

#include "types.h"

struct Battle;
struct BattleStats;
struct Digimon;

void startBattleTask(s8 value);
u8 getEffectLength(struct Battle *battle, s32 unit, s32 length);
s16 getMpCost(struct Battle *battle, s32 unit, s16 cost);
void func_ov002_0224cd48(struct BattleStats *stats, struct Digimon *digimon);
u16 func_ov002_0224cff8(struct Battle *battle, s32 index);
s32 hasAbilityEffect(struct Battle *battle, s32 unit, s32 effect);
void func_ov002_0224cda4(struct BattleStats *stats, struct Digimon *digimon);

#endif /* BATTLE_BATTLE_MODE_START_BATTLE_H */
