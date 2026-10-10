#ifndef BATTLE_UNIT_PANEL_DRAW_H
#define BATTLE_UNIT_PANEL_DRAW_H

#include "types.h"

/* The battle units' panels: opening, moving and closing them. */

struct UnitPanel;

s32 findUnitPanel(s8 unit);
u8 func_0207d3e8(s8 unit);
void func_0207d404(s8 unit, s32 id, s16 arg2, s16 arg3);
void func_0207d524(s8 unit, s32 value);
void func_0207d638(s8 unit, s16 x, s16 y);
void func_0207d920(s8 unit);
void func_0207d990(s8 unit, s16 x, s16 y);
void func_0207debc(s8 id);
void freeUnitPanelNumbers(struct UnitPanel *panel);
s32 isUnitPanelStill(s8 unit);
s32 func_0207d0fc();

#endif /* BATTLE_UNIT_PANEL_DRAW_H */
