#include "farm/farm_queries.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/farm_screen.h"

/* An entry of FARM_KINDS, a kind of farm. */
struct FarmKind *getFarmKind(s32 kind) {
    return &FARM_KINDS[kind];
}

/* How many farms the order holds. */
s32 countFarms(void) {
    s32 i;

    for (i = 0; i < FARM_COUNT && SAVE->groupOrder[i] != -1; i++) {
    }
    if (i > FARM_COUNT) {
        i = 0;
    }
    return i;
}

/* How many goods the farm with an id has. */
s32 countFarmGoods(s32 id) {
    struct Farm *farm = getGroupById(id);
    s32 i;

    for (i = 0; i < FARM_SLOT_COUNT && farm->goods[i] != 0; i++) {
    }
    return i;
}

/* How many goods the farm with an id can hold at its goodsLevel. */
s16 getFarmGoodsCapacity(s32 id) {
    struct Farm *farm;
    struct FarmKind *kind;

    farm = getGroupById(id);
    kind = getFarmKindById(id);
    return kind->goodsCapacity[farm->goodsLevel - 1];
}

/* Counts the digimon of the farm with an id by their stage (unk1E), leaving
 * out the ones with bit 4 of unk108; stages 3 and 5 count together. */
void countFarmDigimonByStage(s32 id, s32 *counts) {
    struct Farm *farm = getGroupById(id);
    struct Digimon *digimon;
    s32 i;

    for (i = 0; i < 6; i++) {
        counts[i] = 0;
    }
    for (i = 0; i < FARM_SLOT_COUNT && farm->digimon[i] != 0; i++) {
        digimon = getDigimon(farm->digimon[i]);
        if (!(digimon->unk108 & 0x10)) {
            counts[digimon->unk1E]++;
        }
    }
    counts[3] += counts[5];
    counts[5] = counts[3];
}

/* How many digimon of the farm with an id have value in their unk4. */
s32 func_ov005_02294d9c(s32 id, s32 value) {
    struct Farm *farm = getGroupById(id);
    s32 member;
    s32 i;
    s32 count;
    s32 field;

    if (farm == NULL) {
        return 0;
    }
    for (i = 0, count = 0; i < FARM_SLOT_COUNT && (member = farm->digimon[i]) != 0; i++) {
        field = ((struct Digimon *) getDigimon(member))->unk4;
        if (field == value) {
            count++;
        }
    }
    return count;
}

/* How many digimon of the farm with an id have bit 1 of func_020a2ca8. */
s32 func_ov005_02294d4c(s32 id) {
    struct Farm *farm = getGroupById(id);
    s32 member;
    s32 i;
    s32 count;

    if (farm == NULL) {
        return 0;
    }
    for (i = 0, count = 0; i < FARM_SLOT_COUNT && (member = farm->digimon[i]) != 0; i++) {
        if (func_020a2ca8(member) & 2) {
            count++;
        }
    }
    return count;
}

/* The id of the farm a digimon is in, or 0. */
s32 getDigimonFarmId(s32 id) {
    struct Farm *farm;
    s32 member;
    s32 place;
    s32 i;

    if (id == 0) {
        return 0;
    }
    for (place = 0; place < FARM_COUNT; place++) {
        farm = (struct Farm *) getGroupInOrder(place);
        if (farm == NULL) {
            return 0;
        }
        for (i = 0; i < FARM_SLOT_COUNT && (member = farm->digimon[i]) != 0; i++) {
            if (id == member) {
                return farm->id;
            }
        }
    }
    return 0;
}

/* The place in the order of the farm a digimon is in, or -1. */
s32 getDigimonFarmPlace(s32 id) {
    struct Farm *farm;
    s32 member;
    s32 place;
    s32 i;

    if (id == 0) {
        return 0;
    }
    for (place = 0; place < FARM_COUNT; place++) {
        farm = (struct Farm *) getGroupInOrder(place);
        if (farm == NULL) {
            return -1;
        }
        for (i = 0; i < FARM_SLOT_COUNT && (member = farm->digimon[i]) != 0; i++) {
            if (id == member) {
                return place;
            }
        }
    }
    return -1;
}

/* The farm a digimon is in, or NULL. */
struct Farm *findDigimonFarm(s32 id) {
    struct Farm *farm;
    s32 member;
    s32 place;
    s32 i;

    if (id == 0) {
        return NULL;
    }
    for (place = 0; place < FARM_COUNT; place++) {
        farm = (struct Farm *) getGroupInOrder(place);
        if (farm == NULL) {
            return NULL;
        }
        for (i = 0; i < FARM_SLOT_COUNT && (member = farm->digimon[i]) != 0; i++) {
            if (id == member) {
                return farm;
            }
        }
    }
    return NULL;
}

/* The farm the digimon of a record is in, or NULL. */
struct Farm *func_ov005_02294be4(s16 index) {
    return findDigimonFarm(((struct Digimon *) getDigimonAt(index))->id);
}

/* The food the farm with an id gathers in a day (getFarmFoodProduced). */
s32 getFarmFoodProducedById(s32 id) {
    return getFarmFoodProduced(id);
}

/* The layout of the farm in a slot at its level. */
struct FarmLayout *getFarmLayoutBySlot(s32 slot) {
    struct Farm *farm;

    farm = getGroup(slot);
    return getFarmLayout(getFarmKind(farm->kind)->layouts[farm->layoutLevel - 1]);
}

/* The layout of the farm with an id at its level. */
struct FarmLayout *getFarmLayoutById(s32 id) {
    struct Farm *farm;

    farm = getGroupById(id);
    return getFarmLayout(getFarmKind(farm->kind)->layouts[farm->layoutLevel - 1]);
}

/* The kind of the farm with an id (struct FarmKind). */
void *getFarmKindById(s32 id) {
    return getFarmKind(((struct Farm *) getGroupById(id))->kind);
}

/* The index of the layout of the farm in a slot, its map. */
u16 getFarmLayoutIndex(s32 slot) {
    /* match depends on the s16 local: the binary converts the index to s16
     * and back to u16. */
    s16 index = getFarmLayoutBySlot(slot)->index;

    return index;
}

/* An entry of FARM_LAYOUTS (struct FarmLayout). */
void *getFarmLayout(s32 index) {
    return &FARM_LAYOUTS[index];
}

/* Copies a name into the farm with an id. */
void setFarmName(s32 id, u16 *name) {
    struct Farm *farm = getGroupById(id);
    s32 i;

    for (i = 0; name[i] != 0xFFFF; i++) {
        farm->name[i] = name[i];
    }
    farm->name[i] = 0xFFFF;
}

/* The name of the farm at a place in the order. */
u16 *getFarmName(s32 place) {
    return ((struct Farm *) getGroupInOrder(place))->name;
}

/* Makes the farm with id -2 in a buffer of the caller's: getGroupById finds
 * it through TEMP_FARM. */
s32 makeTempFarm(s8 kind, struct Farm *farm) {
    TEMP_FARM = (s32) farm;
    func_02030f18(farm, 0, sizeof(struct Farm));
    farm->id   = -2;
    farm->unk4 = 0;
    setFarmName(-2, getFarmText(0x1F));
    farm->kind          = kind;
    farm->capacityLevel = 1;
    farm->goodsLevel    = 1;
    farm->expLevel      = 1;
    farm->foodLevel     = 1;
    farm->layoutLevel   = 1;
    return -2;
}
