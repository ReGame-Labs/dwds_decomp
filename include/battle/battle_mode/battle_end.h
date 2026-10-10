#ifndef BATTLE_BATTLE_MODE_BATTLE_END_H
#define BATTLE_BATTLE_MODE_BATTLE_END_H

/* The battle's per-frame effects (the message window's timer, popups, palette
 * flashes, units waiting on palette effects) and the check for the battle's
 * end. */

#include "types.h"

void func_ov002_02233b48(void);
void func_ov002_02233964(void);
void func_ov002_022339e0(void);
void func_ov002_02234114(void);
BOOL checkBattleEnd(BOOL dryRun);
void func_ov002_02233bb8(void);
void func_ov002_02234008(void);

#endif /* BATTLE_BATTLE_MODE_BATTLE_END_H */
