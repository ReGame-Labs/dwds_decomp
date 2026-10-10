#include "battle/battle_mode/start_battle.h"
#include "battle/ability_bonus.h"
#include "battle/battle_mode/battle.h"
#include "battle/battle_mode/data.h"
#include "battle/battle_state.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/window/message_box.h"

/* A skill of the pairs from 0xE6 on (Positron Laser, Mega Tornado, ...): the
 * pair is the unit's unk05, and the second of it is taken once the Digimon's
 * stage (getSpeciesStage) is above 1. */
u16 func_ov002_0224cff8(struct Battle *battle, s32 index) {
    struct BattleUnit *unit;
    struct BattleStats *stats;
    u32 grown;

    unit  = &battle->units[index];
    stats = &unit->stats;
    if ((u32) getSpeciesStage(stats->id) > 1) {
        grown = 1;
    } else {
        grown = 0;
    }
    return grown + (stats->unk05 * 2 + 0xE6);
}

/* Whether one of the unit's abilities has the given effect. */
s32 hasAbilityEffect(struct Battle *battle, s32 unit, s32 effect) {
    s32 i;
    s16 id;

    for (i = 0; i < 4; i++) {
        id = battle->units[unit].stats.abilities[i];
        if (id != -1 && effect == getAbilityEffect(id)) {
            return 1;
        }
    }
    return 0;
}

/* The MP a skill costs the unit, less what its abilities take off (effect
 * 0x1B, "Reduces the MP required to use skills"). */
s16 getMpCost(struct Battle *battle, s32 unit, s16 cost) {
    cost -= getAbilityBonus(0x1B, cost, battle->units[unit].stats.abilities);
    if (cost < 0) {
        cost = 0;
    }
    return cost;
}

/* A skill's effect length for the unit, more what its abilities add (effect
 * 0x1C, "increases the length of time of a skill's effect"). */
u8 getEffectLength(struct Battle *battle, s32 unit, s32 length) {
    return length + getAbilityBonus(0x1C, length, battle->units[unit].stats.abilities);
}

/* Copies a unit's stats into a Digimon record, for the damage formulas. */
void func_ov002_0224cda4(struct BattleStats *stats, struct Digimon *digimon) {
    s32 i;

    digimon->hp    = stats->hp;
    digimon->maxHp = stats->maxHp;
    digimon->mp    = stats->mp;
    digimon->maxMp = stats->maxMp;
    digimon->unk48 = stats->statParts[0][0] + stats->statParts[0][1] + stats->statParts[0][2];
    digimon->unk4A = stats->statParts[1][0] + stats->statParts[1][1] + stats->statParts[1][2];
    digimon->unk4C = stats->statParts[2][0] + stats->statParts[2][1] + stats->statParts[2][2];
    digimon->unk4E = stats->statParts[3][0] + stats->statParts[3][1] + stats->statParts[3][2];
    if (stats->unk58 == 0xFF) {
        digimon->unk100 = 0xFFFF;
    } else {
        digimon->unk100 = stats->unk58;
    }
    digimon->unk72 = stats->unkBC;
    for (i = 0; i < 4; i++) {
        digimon->unk22[i] = stats->abilities[i];
    }
}

/* Copies back what func_ov002_0224cda4 copied and a damage formula changed. */
void func_ov002_0224cd48(struct BattleStats *stats, struct Digimon *digimon) {
    u16 unk100;

    stats->hp    = digimon->hp;
    stats->maxHp = digimon->maxHp;
    stats->mp    = digimon->mp;
    stats->maxMp = digimon->maxMp;
    unk100       = digimon->unk100;
    if (unk100 == 0xFFFF) {
        stats->unk58 = 0xFF;
        stats->unk59 = 0;
        stats->unk5A = 0;
    } else {
        stats->unk58 = unk100;
    }
    stats->unkBC = digimon->unk72;
}

/* Starts the battle's task; the game passes 0. */
void startBattleTask(s8 value) {
    struct BattleTask *task;

    func_020ac11c();
    func_020ac068();
    task        = createTask(&tickBattleTask, 0x117);
    task->unk44 = value;
    task->phase = 0;
    task->step  = 0;
}
