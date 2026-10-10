#ifndef BATTLE_ABILITY_BONUS_H
#define BATTLE_ABILITY_BONUS_H

#include "types.h"

/* What a Digimon's abilities and equipment add to its stats in battle. */

struct Digimon;

/* What an ability does, from abi_help.sdb's text of the first ability of each:
 * the stats getAbilityBonus sums the Digimon's abilities for. */
enum AbilityEffect {
    ABILITY_ATTACK = 1,
    ABILITY_DEFENSE,
    ABILITY_SPIRIT,
    ABILITY_SPEED,
    ABILITY_RESIST_DARK, /* resistances to the skills of an element */
    ABILITY_RESIST_HOLY,
    ABILITY_RESIST_ENERGY,
    ABILITY_RESIST_FIRE,
    ABILITY_RESIST_LIGHTNING,
    ABILITY_RESIST_WATER,
    ABILITY_RESIST_WIND,
    ABILITY_RESIST_ALL_SKILLS,
    ABILITY_RESIST_POISON, /* resistances to the status disorders */
    ABILITY_RESIST_CONFUSION,
    ABILITY_RESIST_DEATH,
    ABILITY_RESIST_PARALYSIS,
    ABILITY_RESIST_SLEEP,
    ABILITY_RESIST_ALL_STATUS,
    ABILITY_HIT_RATE,
    ABILITY_DODGE_RATE,
    ABILITY_CRITICAL_RATE,
    ABILITY_FLEE_RATE,
    ABILITY_SKILL_DAMAGE,
    ABILITY_BITS,
    ABILITY_EXP,
    ABILITY_DROP_RATE,
    ABILITY_MP_COST,
    ABILITY_EFFECT_TIME
};

/* An ability of the table that func_020a1250 indexes by id, 177 of them, in
 * the order of abi_help.sdb's texts. */
struct Ability {
    /* 0x0 */ u16 id;
    /* 0x2 */ u16 stacks;  /* 0: only the best of the Digimon's abilities with the effect counts */
    /* 0x4 */ u8 effect;   /* enum AbilityEffect */
    /* 0x5 */ u8 percent;  /* value is a percentage */
    /* 0x6 */ s16 value;
};

s32 getExpBonus(s32 kind, s32 id);
s32 getBitsBonus(s32 kind, s32 id);
s32 getSkillDamageBonus(s32 kind, s32 id);
s32 getFleeRateBonus(s32 kind, s32 id);
s32 getHitRateBonus(s32 kind, s32 id);
s32 getSpeedBonus(s32 kind, s32 id, struct Digimon *digimon);
s32 getSpiritBonus(s32 kind, s32 id, struct Digimon *digimon);
s32 getDefenseBonus(s32 kind, s32 id, struct Digimon *digimon);
s32 getAttackBonus(s32 kind, s32 id, struct Digimon *digimon);
s32 getAbilityBonus(s32 effect, s32 amount, const s16 *abilities);
s32 getStatusResistBonus(s32 kind, s32 id, s32 status);
s32 computeSpeedBonus(s32 kind, s32 id, struct Digimon *digimon);
s32 computeSpiritBonus(s32 kind, s32 id, struct Digimon *digimon);
s32 computeDefenseBonus(s32 kind, s32 id, struct Digimon *digimon);
s32 computeAttackBonus(s32 kind, s32 id, struct Digimon *digimon);
void copyAbilities(s32 kind, s32 id, struct Digimon *digimon, s16 *abilities);
void getAbilities(s32 kind, s32 id, s16 *abilities);
void clearItemCache(void);
s32 getAbilityValue(s32 id, s32 amount);

#endif /* BATTLE_ABILITY_BONUS_H */
