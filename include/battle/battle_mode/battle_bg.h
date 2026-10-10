#ifndef BATTLE_BATTLE_MODE_BATTLE_BG_H
#define BATTLE_BATTLE_MODE_BATTLE_BG_H

/* The battle's screens: their setup, the blending set at the vblank, the
 * battle's backgrounds, and one-call wrappers of the unit panels' and sprite
 * slots' functions, which menus/widgets/unit_panel_slots.c and ov006 call
 * too. */

#include "types.h"

void initBattleScreens(void);
void func_ov002_0224b7b8(s8 unit, s32 id, s16 maxHp, s16 maxMp);
void func_ov002_0224b7c4(s8 unit, s32 priority);
void func_ov002_0224b7d0(s8 unit, s16 x, s16 y);
void func_ov002_0224b7dc(s8 unit);
void func_ov002_0224b7e8(s8 unit, s16 x, s16 y);
void func_ov002_0224b7f4(s8 unit);
void func_ov002_0224b800(void);
void func_ov002_0224b80c(void);
void func_ov002_0224b818(void);
void func_ov002_0224b824(void);
void func_ov002_0224b830(void);
void applyBattleSubBlendOff(void);
void applyBattleMainBlendOff(void);
void applyBattleSubBlendWeights(void);
void applyBattleSubBlend(void);
void applyBattleMainBlend(void);
s32 func_ov002_0224bca8();
void loadBattleBgs(void);

#endif /* BATTLE_BATTLE_MODE_BATTLE_BG_H */
