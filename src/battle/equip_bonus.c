#include "battle/equip_bonus.h"
#include "battle/ability_bonus.h"
#include "battle/battle_state.h"
#include "battle/link_party.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/system/display.h"
#include "items/inventory.h"

/* The dodge rate the Digimon's equipment adds. */
s32 getEquipDodgeRate(s32 kind, s32 id) {
    s32 total = 0;
    u16 item;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->dodgeRate;
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->dodgeRate;
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->dodgeRate;
    }
    return total;
}

/* The critical rate the Digimon's equipment adds. */
s32 getEquipCriticalRate(s32 kind, s32 id) {
    s32 total = 0;
    u16 item;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->criticalRate;
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->criticalRate;
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->criticalRate;
    }
    return total;
}

/* The flee rate the Digimon's equipment adds. */
s32 getEquipFleeRate(s32 kind, s32 id) {
    s32 total = 0;
    u16 item;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->fleeRate;
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->fleeRate;
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->fleeRate;
    }
    return total;
}

/* The skill damage the Digimon's equipment adds. */
s32 getEquipSkillDamage(s32 kind, s32 id) {
    s32 total = 0;
    u16 item;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->skillDamage;
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->skillDamage;
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->skillDamage;
    }
    return total;
}

/* The bits bonus the Digimon's equipment adds. */
s32 getEquipBitsBonus(s32 kind, s32 id) {
    s32 total = 0;
    u16 item;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->bits;
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->bits;
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->bits;
    }
    return total;
}

/* The experience bonus the Digimon's equipment adds. */
s32 getEquipExpBonus(s32 kind, s32 id) {
    s32 total = 0;
    u16 item;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->exp;
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->exp;
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->exp;
    }
    return total;
}

/* The resistance to the skills of an element the Digimon's equipment adds:
 * entry index of skillResists. */
s32 func_0207ea48(s32 kind, s32 id, s32 index) {
    s32 total = 0;
    u16 item;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->skillResists[index];
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->skillResists[index];
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->skillResists[index];
    }
    return total;
}

/* The resistance to the status the Digimon's equipment adds. */
s32 getEquipStatusResist(s32 kind, s32 id, s32 status) {
    s32 total = 0;
    u16 item;

    item = getEquippedItem0(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->statusResists[status];
    }
    item = getEquippedItem1(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->statusResists[status];
    }
    item = getEquippedItem2(kind, id);
    if (item != NO_ITEM) {
        total += getItemData(item)->statusResists[status];
    }
    return total;
}

/* The equipment's record from /dat/eq/, loaded into the cache the first time
 * it is asked for in a frame. */
struct ItemData *getItemData(u16 id) {
    s32 i;
    struct ItemCacheEntry *entry;

    registerItemCacheReset();
    entry = ITEM_CACHE;
    for (i = 0; i < ITEM_CACHE_COUNT; i++) {
        if (entry->id == id) {
            return &entry->data;
        }
        entry++;
    }
    entry = ITEM_CACHE;
    for (i = 0; i < ITEM_CACHE_COUNT; i++) {
        if (entry->id == NO_ITEM) {
            break;
        }
        entry++;
    }
    func_02030f78(&entry->data, func_020a142c(id), sizeof(struct ItemData));
    entry->id = id;
    return &entry->data;
}

/* Makes clearItemCache empty the item cache at every VBlank, the first time
 * it is called. */
void registerItemCacheReset(void) {
    if (ITEM_CACHE_REGISTERED != 0) {
        return;
    }
    addVBlankCallback(&clearItemCache);
    ITEM_CACHE_REGISTERED = 1;
}
