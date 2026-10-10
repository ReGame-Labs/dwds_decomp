#ifndef BATTLE_EQUIP_BONUS_H
#define BATTLE_EQUIP_BONUS_H

#include "battle/battle_state.h"
#include "battle/link_party.h"
#include "engine/data.h"
#include "items/inventory.h"
#include "types.h"

/* What a Digimon's equipment adds to its stats in battle, and the cache of the
 * equipment records of /dat/eq/ it reads them from. */

/* Whose a Digimon is, for the stats: the kind argument of these functions and
 * of battle/ability_bonus.c's. */
enum DigimonKind {
    DIGIMON_KIND_OWN,   /* one of the player's: getDigimon */
    DIGIMON_KIND_ENEMY, /* a record of /dat/en/: func_020a14e8; no equipment */
    DIGIMON_KIND_LINK   /* one of the link partner's party: findLinkPartyDigimon */
};

/* The Digimon's item in each of its three equipment slots: for one of the
 * player's, the stock's item it equips; for the others the link partner's.
 * Kept as the game wrote them out in every equipment sum. */
static inline u16 getEquippedItem0(s32 kind, s32 id) {
    struct EquipSlot *slot;
    u16 item = NO_ITEM;

    if (kind == DIGIMON_KIND_OWN) {
        slot = findEquippedWeapon(id);
        if (slot != NULL) {
            item = slot->item;
        }
    } else {
        item = getLinkPartyItem0(id);
    }
    return item;
}

static inline u16 getEquippedItem1(s32 kind, s32 id) {
    struct EquipSlot *slot;
    u16 item = NO_ITEM;

    if (kind == DIGIMON_KIND_OWN) {
        slot = findEquippedArmor(id);
        if (slot != NULL) {
            item = slot->item;
        }
    } else {
        item = getLinkPartyItem1(id);
    }
    return item;
}

static inline u16 getEquippedItem2(s32 kind, s32 id) {
    struct EquipSlot *slot;
    u16 item = NO_ITEM;

    if (kind == DIGIMON_KIND_OWN) {
        slot = findEquippedAccessory(id);
        if (slot != NULL) {
            item = slot->item;
        }
    } else {
        item = getLinkPartyItem2(id);
    }
    return item;
}

void registerItemCacheReset(void);
struct ItemData *getItemData(u16 id);
s32 getEquipStatusResist(s32 kind, s32 id, s32 status);
s32 func_0207ea48(s32 kind, s32 id, s32 index);
s32 getEquipExpBonus(s32 kind, s32 id);
s32 getEquipBitsBonus(s32 kind, s32 id);
s32 getEquipSkillDamage(s32 kind, s32 id);
s32 getEquipFleeRate(s32 kind, s32 id);
s32 getEquipCriticalRate(s32 kind, s32 id);
s32 getEquipDodgeRate(s32 kind, s32 id);

#endif /* BATTLE_EQUIP_BONUS_H */
