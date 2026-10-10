#include "battle/ability_bonus.h"
#include "battle/equip_bonus.h"
#include "battle/exp_level_up.h"
#include "battle/link_party.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"

/* The ability's value: for a percentage, that percent of the amount. */
s32 getAbilityValue(s32 id, s32 amount) {
    struct Ability *ability;

    ability = func_020a1250(id);
    if (ability->percent == 0) {
        return ability->value;
    }
    return amount * ability->value / 100;
}

/* Copies the abilities of the Digimon with the id, looked up by kind. */
void getAbilities(s32 kind, s32 id, s16 *abilities) {
    struct Digimon *digimon;

    if (kind == DIGIMON_KIND_OWN) {
        digimon = getDigimon(id);
    } else if (kind == DIGIMON_KIND_LINK) {
        digimon = findLinkPartyDigimon(id);
    }
    copyAbilities(kind, id, digimon, abilities);
}

/* Empties the equipment record cache; registerItemCacheReset makes it a VBlank
 * callback. */
void clearItemCache(void) {
    s32 i;
    struct ItemCacheEntry *entry;

    entry = ITEM_CACHE;
    for (i = 0; i < ITEM_CACHE_COUNT; i++) {
        entry->id = NO_ITEM;
        entry++;
    }
    ITEM_CACHE_REGISTERED = 0;
}

/* The attack bonus of the Digimon with the id: computeAttackBonus's, with the record looked up by
 * kind. digimon is only used for an enemy, which has none. */
s32 getAttackBonus(s32 kind, s32 id, struct Digimon *digimon) {
    if (kind == DIGIMON_KIND_OWN) {
        digimon = getDigimon(id);
    } else if (kind == DIGIMON_KIND_LINK) {
        digimon = findLinkPartyDigimon(id);
    }
    return computeAttackBonus(kind, id, digimon);
}

/* The attack bonus of the Digimon's abilities, a percentage of its base attack
 * for some, and of its equipment. */
s32 computeAttackBonus(s32 kind, s32 id, struct Digimon *digimon) {
    s16 abilities[4];
    s16 base;
    s32 bonus;
    s32 digimonId;

    if (kind != DIGIMON_KIND_ENEMY) {
        base = digimon->unk48;
    } else {
        base = ((struct EnemyData *) func_020a14e8(id))->attack;
    }
    copyAbilities(kind, id, digimon, abilities);
    bonus = getAbilityBonus(ABILITY_ATTACK, base, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        digimonId = digimon->id;
        if (digimonId != 0 && digimonId != -1) {
            bonus += getEquipAttack(kind, digimonId);
        }
    }
    return bonus;
}

/* The defense bonus of the Digimon with the id: computeDefenseBonus's, with the record looked up by
 * kind. digimon is only used for an enemy, which has none. */
s32 getDefenseBonus(s32 kind, s32 id, struct Digimon *digimon) {
    if (kind == DIGIMON_KIND_OWN) {
        digimon = getDigimon(id);
    } else if (kind == DIGIMON_KIND_LINK) {
        digimon = findLinkPartyDigimon(id);
    }
    return computeDefenseBonus(kind, id, digimon);
}

/* The defense bonus of the Digimon's abilities, a percentage of its base defense
 * for some, and of its equipment. */
s32 computeDefenseBonus(s32 kind, s32 id, struct Digimon *digimon) {
    s16 abilities[4];
    s16 base;
    s32 bonus;
    s32 digimonId;

    if (kind != DIGIMON_KIND_ENEMY) {
        base = digimon->unk4A;
    } else {
        base = ((struct EnemyData *) func_020a14e8(id))->defense;
    }
    copyAbilities(kind, id, digimon, abilities);
    bonus = getAbilityBonus(ABILITY_DEFENSE, base, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        digimonId = digimon->id;
        if (digimonId != 0 && digimonId != -1) {
            bonus += getEquipDefense(kind, digimonId);
        }
    }
    return bonus;
}

/* The spirit bonus of the Digimon with the id: computeSpiritBonus's, with the record looked up by
 * kind. digimon is only used for an enemy, which has none. */
s32 getSpiritBonus(s32 kind, s32 id, struct Digimon *digimon) {
    if (kind == DIGIMON_KIND_OWN) {
        digimon = getDigimon(id);
    } else if (kind == DIGIMON_KIND_LINK) {
        digimon = findLinkPartyDigimon(id);
    }
    return computeSpiritBonus(kind, id, digimon);
}

/* The spirit bonus of the Digimon's abilities, a percentage of its base spirit
 * for some, and of its equipment. */
s32 computeSpiritBonus(s32 kind, s32 id, struct Digimon *digimon) {
    s16 abilities[4];
    s16 base;
    s32 bonus;
    s32 digimonId;

    if (kind != DIGIMON_KIND_ENEMY) {
        base = digimon->unk4C;
    } else {
        base = ((struct EnemyData *) func_020a14e8(id))->spirit;
    }
    copyAbilities(kind, id, digimon, abilities);
    bonus = getAbilityBonus(ABILITY_SPIRIT, base, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        digimonId = digimon->id;
        if (digimonId != 0 && digimonId != -1) {
            bonus += getEquipSpirit(kind, digimonId);
        }
    }
    return bonus;
}

/* The speed bonus of the Digimon with the id: computeSpeedBonus's, with the record looked up by
 * kind. digimon is only used for an enemy, which has none. */
s32 getSpeedBonus(s32 kind, s32 id, struct Digimon *digimon) {
    if (kind == DIGIMON_KIND_OWN) {
        digimon = getDigimon(id);
    } else if (kind == DIGIMON_KIND_LINK) {
        digimon = findLinkPartyDigimon(id);
    }
    return computeSpeedBonus(kind, id, digimon);
}

/* The speed bonus of the Digimon's abilities, a percentage of its base speed
 * for some, and of its equipment. */
s32 computeSpeedBonus(s32 kind, s32 id, struct Digimon *digimon) {
    s16 abilities[4];
    s16 base;
    s32 bonus;
    s32 digimonId;

    if (kind != DIGIMON_KIND_ENEMY) {
        base = digimon->unk4E;
    } else {
        base = ((struct EnemyData *) func_020a14e8(id))->speed;
    }
    copyAbilities(kind, id, digimon, abilities);
    bonus = getAbilityBonus(ABILITY_SPEED, base, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        digimonId = digimon->id;
        if (digimonId != 0 && digimonId != -1) {
            bonus += getEquipSpeed(kind, digimonId);
        }
    }
    return bonus;
}

/* The hit rate bonus of the Digimon's abilities and equipment. */
s32 getHitRateBonus(s32 kind, s32 id) {
    s16 abilities[4];
    s32 bonus;

    getAbilities(kind, id, abilities);
    bonus = getAbilityBonus(ABILITY_HIT_RATE, 0, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        bonus += getEquipHitRate(kind, id);
    }
    return bonus;
}

/* The flee rate bonus of the Digimon's abilities and equipment. */
s32 getFleeRateBonus(s32 kind, s32 id) {
    s16 abilities[4];
    s32 bonus;

    getAbilities(kind, id, abilities);
    bonus = getAbilityBonus(ABILITY_FLEE_RATE, 0, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        bonus += getEquipFleeRate(kind, id);
    }
    return bonus;
}

/* The skill damage bonus of the Digimon's abilities and equipment. */
s32 getSkillDamageBonus(s32 kind, s32 id) {
    s16 abilities[4];
    s32 bonus;

    getAbilities(kind, id, abilities);
    bonus = getAbilityBonus(ABILITY_SKILL_DAMAGE, 0, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        bonus += getEquipSkillDamage(kind, id);
    }
    return bonus;
}

/* The bits bonus of the Digimon's abilities and equipment. */
s32 getBitsBonus(s32 kind, s32 id) {
    s16 abilities[4];
    s32 bonus;

    getAbilities(kind, id, abilities);
    bonus = getAbilityBonus(ABILITY_BITS, 0, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        bonus += getEquipBitsBonus(kind, id);
    }
    return bonus;
}

/* The experience bonus of the Digimon's abilities and equipment. */
s32 getExpBonus(s32 kind, s32 id) {
    s16 abilities[4];
    s32 bonus;

    getAbilities(kind, id, abilities);
    bonus = getAbilityBonus(ABILITY_EXP, 0, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        bonus += getEquipExpBonus(kind, id);
    }
    return bonus;
}

/* The resistance bonus of the Digimon's abilities and equipment to the status
 * (ABILITY_RESIST_POISON on), the abilities for all of them included. */
s32 getStatusResistBonus(s32 kind, s32 id, s32 status) {
    s16 abilities[4];
    s32 bonus;

    getAbilities(kind, id, abilities);
    bonus = getAbilityBonus((u8) (ABILITY_RESIST_POISON + status), 0, abilities);
    bonus += getAbilityBonus(ABILITY_RESIST_ALL_STATUS, 0, abilities);
    if (kind != DIGIMON_KIND_ENEMY) {
        bonus += getEquipStatusResist(kind, id, status);
    }
    return bonus;
}
