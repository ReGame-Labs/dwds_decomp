#ifndef BATTLE_CHARACTERS_CHR_DRAW_H
#define BATTLE_CHARACTERS_CHR_DRAW_H

/* The battle characters' drawing: each screen's tile pool, draw order and BG
 * priority, and whether a character's sequence is done. */

#include "types.h"

void setMainBattleChrsPriority(s16 priority);
void setMainBattleChrPriority(u32 slot, s16 priority);
void freeSubBattleChrTiles(s16 offset);
s16 allocSubBattleChrTiles(s16 size);
void freeMainBattleChrTiles(s16 offset);
s16 allocMainBattleChrTiles(s16 size);
void tickMainBattleChrs(void);
void sortMainBattleChrs(void);
void sortSubBattleChrs(void);
void tickSubBattleChrs(void);
/* Takes the slot, but func_ov002_02233b48 calls it with none: the slot it
 * checks is already in r0. */
u8 isMainBattleChrSeqDone();
u8 isSubBattleChrSeqDone(u32 slot);
void setSubBattleChrPriority(u32 slot, s16 priority);

#endif /* BATTLE_CHARACTERS_CHR_DRAW_H */
