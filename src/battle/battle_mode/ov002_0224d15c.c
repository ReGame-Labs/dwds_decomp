#include "battle/battle_mode/ov002_0224d15c.h"
#include "battle/ability_bonus.h"
#include "battle/battle_mode/data.h"
#include "engine/digimon/game_data.h"

/* Adds up the Bits the enemies beaten give, raised by the best Bits bonus of
 * the party's abilities. */
void addEnemyBits(struct Battle *battle) {
    s32 i;
    s32 max;
    s32 rate;
    s16 bonus;
    struct BattleUnit *unit;
    struct EnemyData *enemy;

    max  = 0;
    rate = 100;
    for (i = 0; i <= LAST_ALLY_UNIT; i++) {
        unit = &battle->units[i];
        if (unit->unk00 != -1) {
            bonus = getBitsBonus(0, unit->unk04);
            if (max < bonus) {
                max = bonus;
            }
        }
    }
    rate += max;
    unit = &battle->units[FIRST_ENEMY_UNIT];
    for (i = 0; i < UNITS_PER_SIDE; i++, unit++) {
        if (unit->unk00 != -1 && unit->stats.hp <= 0) {
            enemy = (struct EnemyData *) func_020a14e8(unit->stats.id);
            battle->bits += enemy->bits * rate / 100;
        }
    }
}

/* Adds up the EXP the enemies beaten give. */
void addEnemyExp(struct Battle *battle) {
    s32 i;
    struct BattleUnit *unit;

    unit = &battle->units[FIRST_ENEMY_UNIT];
    for (i = 0; i < UNITS_PER_SIDE; i++, unit++) {
        if (unit->unk00 != -1 && unit->stats.hp <= 0) {
            battle->exp += ((struct EnemyData *) func_020a14e8(unit->stats.id))->exp * 100 / 100;
        }
    }
}
