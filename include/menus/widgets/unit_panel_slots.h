#ifndef MENUS_WIDGETS_UNIT_PANEL_SLOTS_H
#define MENUS_WIDGETS_UNIT_PANEL_SLOTS_H

#include "types.h"

/* The unit panel slots (struct UnitPanelSlots), and the count of a number's
 * digits. */

u16 getSlotUnitPanel(s32 index);
s32 countDigits(s32 value);
void func_0204ca8c(s32 id, s16 unk1, s16 unk2);
s32 findUnitPanelSlot(s32 id);
void setUnitPanelValue(s32 id, s32 value);
void moveUnitPanel(s32 id, s16 x, s16 y);
void freeUnitPanel(s32 id);
void freeUnitPanels(void);
void swapUnitPanels(s32 a, s32 b);

#endif /* MENUS_WIDGETS_UNIT_PANEL_SLOTS_H */
