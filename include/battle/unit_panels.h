#ifndef BATTLE_UNIT_PANELS_H
#define BATTLE_UNIT_PANELS_H

#include "types.h"

/* The battle units' panels: what they show of the units, and moving and drawing
 * them once a frame. Then a few lists and modes that the shop screens of
 * menus/shop/farm_shops.c and menus/shop/item_equipment_shop.c read. */

/* Why a unit's panel is redrawn (UNIT_CHANGES). */
enum UnitChange {
    UNIT_UNCHANGED,
    UNIT_CHANGED,         /* by markUnitChanged or the numbers rolling */
    UNIT_CHANGED_BY_PANEL /* the mark of a panel's UNIT_PANEL_MARK_CHANGED, taken back when read */
};

struct UnitPanel;
struct UnitStatus;

struct UnitPanel *getUnitPanel(s32 index);
struct UnitStatus *getUnitStatus(s32 unit);
void freeUnitPanelTexts(void);
void func_0207e5ac(s32 index, const u16 *src);
void func_0207e5f4(s32 index, const u16 *src);
u16 *func_0207e5a0(void);
u16 *func_0207e5e0(s32 index);
u16 *func_0207e628(s32 index);
void func_0207e63c(s8 mode, s8 arg1);
s32 func_0207e694(void);
u8 func_0207e6ac(void);
void func_0207e6bc(s8 value);
s32 isTouchInRect(u32 left, u32 top, u32 right, u32 bottom);
s32 func_0207e6cc();
void markUnitChanged(s32 unit);
s32 isUnitChanged(s32 unit);
void func_0207e574(u16 *src);
s32 func_0207e658(s32 mode);
void initUnitPanels(void);
void updateUnitPanels(void);

#endif /* BATTLE_UNIT_PANELS_H */
