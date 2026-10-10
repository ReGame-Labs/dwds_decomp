#include "battle/battle_mode/enemy_ai.h"
#include "battle/battle_mode/data.h"
#include "battle/battle_mode/ov002_0224f520.h"
#include "battle/battle_state.h"
#include "engine/digimon/game_data.h"
#include "engine/system/system.h"

/* Chooses what an enemy does: its recovery skill when func_ov002_022509bc
 * uses it, else what func_ov002_02250934 does when the enemy's unk68 is 1,
 * else one of its skills, by the kind of the skill. */
void chooseEnemyAction(struct Battle *battle, s32 unit) {
    struct EnemyData *enemy;
    s32 index;

    /* func_020a14e8 returns the record as bytes. */
    enemy = (struct EnemyData *) func_020a14e8(battle->units[unit].unk04);
    index = findRecoverySkill(enemy);
    if (index > 0 && func_ov002_022509bc(battle, unit, enemy->skills[index]) == 1) {
        return;
    }
    if (enemy->unk68 == 1 && func_ov002_02250934(battle, unit) == 1) {
        return;
    }
    index = func_ov002_02250718(battle, unit);
    switch (((struct SkillData *) func_020a1268(enemy->skills[index]))->kind) {
        case SKILL_ATTACK:
            func_ov002_0225018c(battle, unit, enemy->skills[index]);
            break;
        case SKILL_SUPPORT:
            func_ov002_0224f82c(battle, unit, enemy->skills[index]);
            break;
        case SKILL_RECOVERY:
            break;
    }
}

/* Rolls a number from 1 to range1, and if it reaches min1 one from 1 to
 * range2: 1 if that one reaches min2 too. */
s32 func_ov002_02250de4(s32 min1, s32 range1, s32 min2, s32 range2) {
    if ((s32) (getRandom(range1) + 1) < min1) {
        return 0;
    }
    if ((s32) (getRandom(range2) + 1) >= min2) {
        return 1;
    }
    return 0;
}

/* Picks one of the count (1 to 3) units in slots at random, with the same
 * odds, and returns its unk01. */
u8 func_ov002_02250cf0(struct Battle *battle, s32 count, s8 *slots) {
    u16 roll;
    struct BattleUnit *unit;

    roll = getRandom(0x62) + 1;
    if (count == 1) {
        unit = &battle->units[slots[0]];
    } else if (count == 2) {
        if (roll <= 50) {
            unit = &battle->units[slots[0]];
        } else {
            unit = &battle->units[slots[1]];
        }
    } else {
        roll = getRandom(0x62) + 1;
        if (roll <= 33) {
            unit = &battle->units[slots[0]];
        } else if (roll <= 66) {
            unit = &battle->units[slots[1]];
        } else {
            unit = &battle->units[slots[2]];
        }
    }
    return unit->unk01;
}

/* The slot of the enemy's fifth skill when it has one and it is a recovery
 * skill, else -1. */
s32 findRecoverySkill(struct EnemyData *enemy) {
    u16 id;

    id = enemy->skills[4];
    if (id != 0xFFFF && id != -1U && func_02080de8(id) == SKILL_RECOVERY) {
        return 4;
    }
    return -1;
}
