#include "items/inventory_queries.h"
#include "engine/data.h"
#include "items/inventory.h"

/* The stock slot of an item below the weapons, NULL when there is none. */
struct ItemSlot *getItemSlot(u16 item) {
    struct ItemSlot *slots = ITEM_STOCK;
    s32 index              = findItemSlot(item);

    if (index == -1) {
        return NULL;
    }
    return &slots[index];
}

/* The first free slot of the key items, -1 when they are full. */
s32 findFreeKeyItemSlot(void) {
    s32 i;
    u16 *items = KEY_ITEMS;

    for (i = 0; i < ITEM_ID_END - ITEM_ID_KEY_ITEMS; i++) {
        if (items[i] == 0xFFFF) {
            return i;
        }
    }
    return -1;
}

/* Takes a key item away: FALSE when there is none. */
BOOL removeKeyItem(u16 item) {
    u16 *items = KEY_ITEMS;
    s32 index;

    index = findKeyItem(item);
    if (index != -1) {
        items[index] = 0xFFFF;
        return TRUE;
    }
    return FALSE;
}

/* How many weapons are in stock. */
s16 countWeapons(void) {
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < EQUIP_STOCK_SIZE; i++) {
        if (WEAPON_STOCK[i].item != 0xFFFF) {
            count++;
        }
    }
    return count;
}

/* How many pieces of armor are in stock. */
s16 countArmor(void) {
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < EQUIP_STOCK_SIZE; i++) {
        if (ARMOR_STOCK[i].item != 0xFFFF) {
            count++;
        }
    }
    return count;
}

/* How many accessories are in stock. */
s16 countAccessories(void) {
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < EQUIP_STOCK_SIZE; i++) {
        if (ACCESSORY_STOCK[i].item != 0xFFFF) {
            count++;
        }
    }
    return count;
}

/* How many key items there are. */
s16 countKeyItems(void) {
    s32 i;
    s32 count;
    u16 *items = KEY_ITEMS;

    for (i = 0, count = 0; i < ITEM_ID_END - ITEM_ID_KEY_ITEMS; i++) {
        if (items[i] != 0xFFFF) {
            count++;
        }
    }
    return count;
}

/* The item the Digimon equips as its weapon, armor or accessory, 0xFFFF for
 * none. */
s32 getEquippedItem(s32 owner, s32 kind) {
    struct EquipSlot *slot;

    switch (kind) {
        case EQUIP_WEAPON:
            slot = findEquippedWeapon(owner);
            return slot != NULL ? slot->item : 0xFFFF;
        case EQUIP_ARMOR:
            slot = findEquippedArmor(owner);
            return slot != NULL ? slot->item : 0xFFFF;
        case EQUIP_ACCESSORY:
            slot = findEquippedAccessory(owner);
            return slot != NULL ? slot->item : 0xFFFF;
        default:
            return 0xFFFF;
    }
}
