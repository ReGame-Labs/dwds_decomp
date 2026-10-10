#include "engine/system/display_modes.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "farm/farm_queries.h"

#define PLACE_NONE 99
#define ORDER_NONE 9999
#define ORDER_IN_GROUP 100 /* plus the place of the group */
#define ORDER_ELSE 200

/* Returns where a Digimon is: PLACE_PARTY, PLACE_GROUP, PLACE_ELSEWHERE, or
 * 99 when there is no such Digimon. */
s32 getDigimonPlace(s32 id) {
    s32 slot;
    s32 group;

    if (getDigimon(id) == NULL) {
        return PLACE_NONE;
    }
    slot  = func_020a2d60(id);
    group = getDigimonFarmId(id);
    if (slot != -1) {
        return PLACE_PARTY;
    }
    if (group != 0) {
        return PLACE_GROUP;
    }
    return PLACE_ELSEWHERE;
}

/* Returns where a Digimon sorts: its party slot, 100 plus the place of its
 * group, 200 elsewhere, or 9999 when there is no such Digimon. */
s32 func_020a3360(s32 id) {
    s32 order;
    s32 place;

    if (getDigimon(id) == NULL) {
        return ORDER_NONE;
    }
    order = func_020a2d60(id);
    place = getDigimonFarmPlace(id);
    if (order == -1) {
        if (place != -1) {
            order = place + ORDER_IN_GROUP;
        } else {
            order = ORDER_ELSE;
        }
    }
    return order;
}

/* Counts the Digimon kept with a value of unk1D. */
s32 func_020a32d8(s32 value) {
    s32 i;
    s32 count = 0;
    struct Digimon *digimon;

    for (i = 0; i < 40; i++) {
        digimon = getDigimonAt(i);
        if (digimon->id != 0 && digimon->unk1D == value) {
            count++;
        }
    }
    return count;
}

/* Counts the Digimon kept with a value of unk1A. */
s32 func_020a3294(s32 value) {
    s32 i;
    s32 count = 0;
    struct Digimon *digimon;

    for (i = 0; i < 40; i++) {
        digimon = getDigimonAt(i);
        if (digimon->id != 0 && digimon->unk1A == value) {
            count++;
        }
    }
    return count;
}

/* Counts the Digimon kept at a stage, Armor counting as Ultimate. */
s32 countDigimonAtStage(u8 stage) {
    s32 i;
    s32 count;
    struct Digimon *digimon;
    u8 digimonStage;

    if (stage == STAGE_ARMOR) {
        stage = STAGE_ULTIMATE;
    }
    for (count = 0, i = 0; i < 40; i++) {
        digimon      = getDigimonAt(i);
        digimonStage = digimon->unk1E;
        if (digimonStage == STAGE_ARMOR) {
            digimonStage = STAGE_ULTIMATE;
        }
        if (digimon->id != 0 && digimonStage == stage) {
            count++;
        }
    }
    return count;
}

/* Returns the key of a species (data_02111bf8): the forms of a species share
 * it, and func_020a31e8 finds the first species with a key. */
s32 func_020a3224(s32 species) {
    return data_02111bfc[species][0];
}

/* Returns the number of a species in data_02111bf8, 0 for a second form. */
s32 func_020a31d8(s32 species) {
    return data_02111c00[species][0];
}

/* Returns data_02111bf8's unkC of a species. */
s32 func_020a31c4(s32 species) {
    return data_02111c04[species * 8];
}

/* Returns data_02111bf8's unkE of a species. */
u16 func_020a31b0(s32 species) {
    return data_02111c06[species * 8];
}

/* Returns the stage of a species, by the ranges of the species ids. */
s32 getSpeciesStage(s32 species) {
    if (species >= 0 && species < 12) {
        return STAGE_IN_TRAINING;
    }
    if (species >= 12 && species < 66) {
        return STAGE_ROOKIE;
    }
    if (species >= 66 && species < 130) {
        return STAGE_CHAMPION;
    }
    if (species >= 130 && species < 144) {
        return STAGE_ARMOR;
    }
    if (species >= 144 && species < 228) {
        return STAGE_ULTIMATE;
    }
    if (species >= 228 && species < 426) {
        return STAGE_MEGA;
    }
    return STAGE_IN_TRAINING;
}

/* Returns byte 3 of a species' record, or -1 for an id out of range. */
s32 func_020a3098(s32 species) {
    struct SpeciesData *record;

    if (species < 0 || species >= 426) {
        return -1;
    }
    record = loadSpeciesData(species);
    return record->unk3;
}
