#include "battle/battle_mode/ov002_0224f520.h"
#include "battle/battle_mode/data.h"
#include "engine/digimon/species_flags.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"

/* The command 0xFFFE in place of the unit's, one time in three, when its
 * Digimon's stage is above what func_020a0eb0's value (0 to 5) allows; 0
 * otherwise. */
s32 func_ov002_0224f570(struct Battle *battle, s32 unit) {
    s32 stage;

    stage = getSpeciesStage(battle->units[unit].stats.id);
    switch (func_020a0eb0()) {
        case 0:
            if (stage <= 1) {
                return 0;
            }
            break;
        case 1:
            if (stage <= 2) {
                return 0;
            }
            break;
        case 2:
            if (stage <= 3 || stage == 5) {
                return 0;
            }
            break;
        case 3:
        case 4:
        case 5:
            return 0;
    }
    if (getRandom(3) != 0) {
        return 0;
    }
    return 0xFFFE;
}

/* The command 0xFFFD in place of an ally's, one time in four, while its
 * unkBA is below 33; 0 otherwise. */
s32 func_ov002_0224f520(struct Battle *battle, s32 unit) {
    s32 value;

    value = battle->units[unit].stats.unkBA;
    if (unit <= LAST_ALLY_UNIT && value < 0x21 && getRandom(4) == 0) {
        return 0xFFFD;
    }
    return 0;
}
