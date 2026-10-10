#ifndef BATTLE_BATTLE_MODE_ENEMY_AI_H
#define BATTLE_BATTLE_MODE_ENEMY_AI_H

/* The enemies' choice of action: a recovery skill, or one of their skills by
 * its kind, and on whom. */

#include "types.h"

struct Battle;
struct EnemyData;

s32 func_ov002_02250de4(s32 min1, s32 range1, s32 min2, s32 range2);
s32 findRecoverySkill(struct EnemyData *enemy);
u8 func_ov002_02250cf0(struct Battle *battle, s32 count, s8 *slots);
s32 func_ov002_0225018c();
s32 func_ov002_02250718();
s32 func_ov002_02250934();
s32 func_ov002_022509bc();
void chooseEnemyAction(struct Battle *battle, s32 unit);

#endif /* BATTLE_BATTLE_MODE_ENEMY_AI_H */
