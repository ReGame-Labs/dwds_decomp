#include "items/inventory.h"
#include "engine/data.h"
#include "items/inventory_queries.h"

/* Whether there is at least one of the item in stock. */
u8 hasItem(u32 item) {
    if (item < ITEM_ID_WEAPONS) {
        return findItemSlot(item) != -1;
    }
    if (item >= ITEM_ID_WEAPONS && item < ITEM_ID_ARMOR) {
        return hasWeapon(item) != FALSE;
    }
    if (item >= ITEM_ID_ARMOR && item < ITEM_ID_ACCESSORIES) {
        return hasArmor(item) != FALSE;
    }
    if (item >= ITEM_ID_ACCESSORIES && item < ITEM_ID_KEY_ITEMS) {
        return hasAccessory(item) != FALSE;
    }
    if (item >= ITEM_ID_KEY_ITEMS && item < ITEM_ID_END) {
        return findKeyItem(item) != -1;
    }
    return FALSE;
}

/* The first free slot of the weapons stock, -1 when it is full. */
s32 findFreeWeaponSlot(void) {
    s32 i;

    for (i = 0; i < EQUIP_STOCK_SIZE; i++) {
        if (WEAPON_STOCK[i].item == 0xFFFF) {
            return i;
        }
    }
    return -1;
}

/* How many slots of the weapons stock are free. */
s32 countFreeWeaponSlots(void) {
    s32 count;
    s32 i;

    for (i = 0, count = 0; i < EQUIP_STOCK_SIZE; i++) {
        if (WEAPON_STOCK[i].item == 0xFFFF) {
            count++;
        }
    }
    return count;
}

/* The first free slot of the armor stock, -1 when it is full. */
s32 findFreeArmorSlot(void) {
    s32 i;

    for (i = 0; i < EQUIP_STOCK_SIZE; i++) {
        if (ARMOR_STOCK[i].item == 0xFFFF) {
            return i;
        }
    }
    return -1;
}

/* How many slots of the armor stock are free. */
s32 countFreeArmorSlots(void) {
    s32 count;
    s32 i;

    for (i = 0, count = 0; i < EQUIP_STOCK_SIZE; i++) {
        if (ARMOR_STOCK[i].item == 0xFFFF) {
            count++;
        }
    }
    return count;
}

/* The first free slot of the accessories stock, -1 when it is full. */
s32 findFreeAccessorySlot(void) {
    s32 i;

    for (i = 0; i < EQUIP_STOCK_SIZE; i++) {
        if (ACCESSORY_STOCK[i].item == 0xFFFF) {
            return i;
        }
    }
    return -1;
}

/* How many slots of the accessories stock are free. */
s32 countFreeAccessorySlots(void) {
    s32 count;
    s32 i;

    for (i = 0, count = 0; i < EQUIP_STOCK_SIZE; i++) {
        if (ACCESSORY_STOCK[i].item == 0xFFFF) {
            count++;
        }
    }
    return count;
}
