#include "engine/save/game_state.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/digimon/species_flags.h"
#include "engine/save/progress.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/ui/gauge.h"
#include "farm/farm_groups.h"
#include "farm/farm_queries.h"
#include "farm/farm_screen.h"
#include "farm/farms.h"

#define MAX_AMOUNT 999999
#define MAX_COUNT 999
#define MAX_COUNT_TOTAL 99999
#define MAX_UNK4444 9999
#define MAX_UNK72 100
#define SPECIES_COUNT 426
#define GROUP_ITEMS 50
#define FLAG_UNK68 0x68
#define FLAGS_UNK12D 301   /* 60 flags, func_020a020c */
#define FLAGS_UNK1C9 0x1C9 /* 60 flags, func_020a02b0 */
#define FLAGS_UNK2BC 0x2BC
#define DIGIMON_FLAGS_CLEARED 0x1780 /* by func_020a0764 */

/* Takes amount from a Digimon's unk72, kept within 0 to 100. */
s16 func_020a0980(s32 id, s32 amount) {
    struct Digimon *digimon = getDigimon(id);

    digimon->unk72 -= amount;
    if (digimon->unk72 > MAX_UNK72) {
        digimon->unk72 = MAX_UNK72;
    }
    if (digimon->unk72 < 0) {
        digimon->unk72 = 0;
    }
    return digimon->unk72;
}

/* Adds to the farms' food, kept within 0 to 999999, and returns it. */
s32 addFood(s32 amount) {
    struct SaveData *save = SAVE;
    s32 food;

    food       = save->food + amount;
    save->food = food;
    if (food > MAX_AMOUNT) {
        save->food = MAX_AMOUNT;
    }
    if (save->food < 0) {
        save->food = 0;
    }
    return save->food;
}

/* Returns whether the food, with what the groups bring in
 * (getFoodProduced), covers what they cost (getFoodConsumed). */
BOOL func_020a0894(void) {
    s32 food;
    s32 income;

    food   = SAVE->food;
    income = getFoodProduced();
    if (income + food >= getFoodConsumed()) {
        return TRUE;
    }
    return FALSE;
}

/* Adds to the save's unk3E38, up to 999999, and returns it. */
s32 func_020a0864(s32 amount) {
    s32 value;

    value         = SAVE->unk3E38 + amount;
    SAVE->unk3E38 = value;
    if (value > MAX_AMOUNT) {
        SAVE->unk3E38 = MAX_AMOUNT;
    }
    return SAVE->unk3E38;
}

/* Returns the save's unk3E34. */
u8 func_020a0854(void) {
    return SAVE->unk3E34;
}

/* Adds to the money, up to 999999, and returns it. */
u32 addMoney(s32 amount) {
    u32 money;

    money       = SAVE->money + amount;
    SAVE->money = money;
    if (money > MAX_AMOUNT) {
        SAVE->money = MAX_AMOUNT;
    }
    return SAVE->money;
}

/* Sets the save's day, kept within 0 to 999. */
s16 func_020a07e8(s16 value) {
    SAVE->day = value;
    if (SAVE->day < 0) {
        SAVE->day = 0;
    } else if (SAVE->day > MAX_COUNT) {
        SAVE->day = MAX_COUNT;
    }
    return SAVE->day;
}

/* Adds to the save's day, kept within 0 to 999, then clears the "grew"
 * flag of every group item and flags 0x1780 of every Digimon. A script
 * command adds 1 with it. */
s32 func_020a0764(s32 delta) {
    s32 i;
    struct FarmGoods *item;

    SAVE->day = SAVE->day + delta;
    if (SAVE->day < 0) {
        SAVE->day = 0;
    } else if (SAVE->day > MAX_COUNT) {
        SAVE->day = MAX_COUNT;
    }
    for (i = 0; i < GROUP_ITEMS; i++) {
        item = getFarmGoodsAt((s8) i);
        if (item->id == 0) {
            break;
        }
        item->flags &= ~1;
    }
    clearAllDigimonFlags(DIGIMON_FLAGS_CLEARED);
    return SAVE->day;
}

/* Returns the save's day. */
s16 func_020a0754(void) {
    return SAVE->day;
}

/* Sets or clears flag 0x68. */
void func_020a0724(BOOL set) {
    if (set) {
        setGameFlag(FLAG_UNK68);
        return;
    }
    clearGameFlag(FLAG_UNK68);
}

/* Adds to the first count of a species, kept within 0 to 999. A form with
 * listed 0 counts as the first species with its func_020a3224 key. */
u32 func_020a0684(s32 id, s32 delta) {
    s16 count;
    struct SpeciesRecord *record;
    struct SpeciesData *species;

    species = loadSpeciesData(id);
    if (species->listed == 0) {
        id = func_020a31e8(func_020a3224(id));
    }
    record = func_020a0470(id);
    count  = delta + record->count0;
    if (count > MAX_COUNT) {
        count = MAX_COUNT;
    } else if (count < 0) {
        count = 0;
    }
    record->count0 = count;
    return record->count0;
}

/* The same as func_020a0684, for the second count. */
u32 func_020a05e4(s32 id, s32 delta) {
    s16 count;
    struct SpeciesRecord *record;
    struct SpeciesData *species;

    species = loadSpeciesData(id);
    if (species->listed == 0) {
        id = func_020a31e8(func_020a3224(id));
    }
    record = func_020a0470(id);
    count  = delta + record->count1;
    if (count > MAX_COUNT) {
        count = MAX_COUNT;
    } else if (count < 0) {
        count = 0;
    }
    record->count1 = count;
    return record->count1;
}

/* Sums the second counts of the species listed, up to 99999. */
s32 func_020a0570(void) {
    s32 i;
    s32 total;
    struct SpeciesData *species;

    total = 0;
    for (i = 0; i < SPECIES_COUNT; i++) {
        species = loadSpeciesData(i);
        if (species->listed != 0) {
            total += func_020a05e4(i, 0);
        }
    }
    if (total > MAX_COUNT_TOTAL) {
        total = MAX_COUNT_TOTAL;
    } else if (total < 0) {
        total = 0;
    }
    return total;
}

/* The same as func_020a0684, for the third count; from 100 on, the species'
 * flags are set (func_020a0fd8). */
u32 func_020a04c0(s32 id, s32 delta) {
    s16 count;
    struct SpeciesRecord *record;
    struct SpeciesData *species;

    species = loadSpeciesData(id);
    if (species->listed == 0) {
        id = func_020a31e8(func_020a3224(id));
    }
    record = func_020a0470(id);
    count  = delta + record->count2;
    if (count > MAX_COUNT) {
        count = MAX_COUNT;
    } else if (count < 0) {
        count = 0;
    }
    if (count >= 100) {
        func_020a0fd8(id);
    }
    record->count2 = count;
    func_0209fa00();
    return record->count2;
}

/* Returns the third count of a species. */
u32 func_020a04a0(s32 id) {
    struct SpeciesRecord *record = func_020a0470(id);

    return record->count2;
}

/* Returns the record of a species, or NULL for an id out of range. */
void *func_020a0470(s32 id) {
    if (id < 0 || id >= SPECIES_COUNT) {
        return NULL;
    }
    return &SPECIES_RECORDS[id];
}

/* Raises the save's unk4444 to value, kept within 0 to 9999. */
s16 func_020a0428(s32 value) {
    if (SAVE->unk4444 < value) {
        SAVE->unk4444 = value;
    }
    if (SAVE->unk4444 > MAX_UNK4444) {
        SAVE->unk4444 = MAX_UNK4444;
    } else if (SAVE->unk4444 < 0) {
        SAVE->unk4444 = 0;
    }
    return SAVE->unk4444;
}

/* Heals a Digimon fully: its HP and MP back to their maximum. */
void healDigimon(s32 id) {
    struct Digimon *digimon;

    if (id == 0) {
        return;
    }
    if (id == -1) {
        return;
    }
    digimon = getDigimon(id);
    if (digimon != NULL) {
        digimon->hp = digimon->maxHp;
        digimon->mp = digimon->maxMp;
    }
}

/* Records the highest level of the Digimon kept, but those with status bit
 * 2 (func_020a2c9c). */
void recordHighestLevel(void) {
    s16 level;
    s32 i;
    struct Digimon *digimon;

    i = 0;
    do {
        digimon = getDigimonAt(i);
        if (digimon->id != 0 && !(digimon->unk108 & 2)) {
            level = digimon->level;
            if (SAVE->highestLevel < level) {
                SAVE->highestLevel = level;
            }
        }
        i++;
    } while (i < 40);
}

/* Returns the highest level the Digimon kept reached. */
s16 getHighestLevel(void) {
    return SAVE->highestLevel;
}

/* Counts the set flags of the 60 from 0x1C9. */
s16 func_020a02b0(void) {
    s16 total = 0;
    s16 i;

    for (i = 0; i < 60; i++) {
        total += getGameFlag(i + FLAGS_UNK1C9);
    }
    return total;
}

/* Returns one of the 60 flags from 0x1C9. */
s16 func_020a0288(s32 index) {
    return getGameFlag(index + FLAGS_UNK1C9);
}

/* Sets one of the flags from 0x2BC. */
void func_020a0278(s32 index) {
    setGameFlag(index + FLAGS_UNK2BC);
}

/* Returns one of the flags from 0x2BC. */
s32 func_020a0268(s32 index) {
    return getGameFlag(index + FLAGS_UNK2BC);
}

/* Returns one of the 32-byte entries of data_02127678. */
void *func_020a0258(s32 index) {
    return data_02127678 + (index << 5);
}

/* Returns the first set flag of the 60 from 301, or -1. */
s32 func_020a020c(void) {
    s16 i;

    for (i = 0; i < 60; i++) {
        if (getGameFlag(i + FLAGS_UNK12D) != 0) {
            break;
        }
    }
    if (i == 60) {
        return -1;
    }
    return i;
}

/* Returns whether the Digimon in the save's unk443C is in a group. */
BOOL func_020a01d8(s32 group) {
    if (SAVE->unk443C == 0) {
        return FALSE;
    }
    if (group == getDigimonFarmId(SAVE->unk443C)) {
        return TRUE;
    }
    return FALSE;
}

/* Starts the task that counts the play time (func_020a0130), up to 100
 * hours. */
s32 startPlayTimeClock(void) {
    struct PlayTimeTask *task;
    s32 id;

    task          = createTask(func_020a0130, 0x125);
    task->state   = 0;
    task->wait    = 0;
    id            = getTaskId(task);
    data_021da78c = id;
    return id;
}
