#ifndef ITEMS_INVENTORY_QUERIES_H
#define ITEMS_INVENTORY_QUERIES_H

/* The item stock: what each Digimon equips, how many pieces each stock
 * holds, the items below the weapons and the key items. */

#include "types.h"

struct ItemSlot;

/* The three pieces of equipment a Digimon has, each with a stock of its own. */
enum EquipKind {
    EQUIP_WEAPON,
    EQUIP_ARMOR,
    EQUIP_ACCESSORY
};

s32 findKeyItem();
s32 findItemSlot();
void *func_0205c728();
s32 getEquippedItem(s32 owner, s32 kind);
s32 findFreeKeyItemSlot(void);
struct ItemSlot *getItemSlot(u16 item);
s16 func_0205c164();
s16 countKeyItems(void);
s16 countAccessories(void);
s16 countArmor(void);
s16 countWeapons(void);
BOOL removeKeyItem(u16 item);

#endif /* ITEMS_INVENTORY_QUERIES_H */
