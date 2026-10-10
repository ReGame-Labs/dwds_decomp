#ifndef ITEMS_INVENTORY_H
#define ITEMS_INVENTORY_H

/* The equipment stocks, one for weapons, armor and accessories, and adding
 * and taking away items of any kind. */

#include "types.h"

struct EquipSlot;

BOOL hasAccessory(u32 item);
BOOL hasArmor(u32 item);
BOOL hasWeapon(u32 item);
u8 hasItem(u32 item);
BOOL canAddItem(u32 item, s32 amount);
s32 addItem();
struct EquipSlot *findAccessory(s32 id);
struct EquipSlot *findEquippedAccessory(s32 owner);
s32 countFreeAccessorySlots(void);
s32 findFreeAccessorySlot(void);
struct EquipSlot *findArmor(s32 id);
struct EquipSlot *findEquippedArmor(s32 owner);
s32 countFreeArmorSlots(void);
s32 findFreeArmorSlot(void);
struct EquipSlot *findWeapon(s32 id);
struct EquipSlot *findEquippedWeapon(s32 owner);
s32 countFreeWeaponSlots(void);
s32 findFreeWeaponSlot(void);
void unequipAccessory();
void unequipArmor();
void unequipWeapon();

#endif /* ITEMS_INVENTORY_H */
