#include "eggs/egg_hatch.h"
#include "eggs/egg_breeding.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "farm/data.h"
#include "farm/farm_queries.h"
#include "farm/goods_panel.h"
#include "link/exchange_data.h"
#include "link/farm_visit.h"

/* Returns the index of the layout of a farm of the other DS. */
s16 func_0209a408(s32 id) {
    return *func_0209a3dc(id);
}

/* Returns the layout of a farm of the other DS, by its kind and its layout
 * level. */
s16 *func_0209a3dc(s32 id) {
    struct Farm *group;

    group = func_0209a628(id);
    return getFarmLayout(getFarmKind(group->kind)->layouts[group->layoutLevel - 1]);
}

/* Returns the id of the other DS's farm at a place of its order, or 0. */
s32 func_0209a38c(s32 place) {
    s8 slot;

    if (place < 0 || place >= 4) {
        return 0;
    }
    slot = data_021da40c->groupOrder.slots[place];
    if (slot == -1) {
        return 0;
    }
    return data_021da40c->groups[slot].id;
}

/* Returns the place of a farm of the other DS in its order, or -1. */
s8 func_0209a31c(s32 id) {
    s32 slot;
    s32 place;

    for (slot = 0; slot < 4; slot++) {
        if (id == data_021da40c->groups[slot].id) {
            for (place = 0; place < 4; place++) {
                if (slot == data_021da40c->groupOrder.slots[place]) {
                    return place;
                }
            }
        }
    }
    return -1;
}

/* Returns how many farms the other DS has. */
s32 func_0209a2d8(void) {
    s32 count;

    for (count = 0; count < 4 && data_021da40c->groupOrder.slots[count] != -1; count++) {
    }
    if (count > 4) {
        count = 0;
    }
    return count;
}

/* Shows the goods of a farm of the other DS through drawFarmStatus, as
 * the farm of id -2. */
void func_0209a1f8(s32 id) {
    /* declared an s32 in farm/data.h */
    TEMP_FARM = (s32) func_0209a628(id);
    drawFarmStatus(-2);
}

/* Shows a farm of the other DS through openFarmStatus, as the farm of id
 * -2. */
void func_0209a1b8(s32 id, s32 gfxSlot) {
    /* declared an s32 in farm/data.h */
    TEMP_FARM = (s32) func_0209a628(id);
    openFarmStatus(0, -2, gfxSlot, 0, 3);
}

/* Returns whether an egg meets the three conditions of its kind to hatch. */
BOOL isEggReadyToHatch(struct Digimon *egg) {
    BOOL ready;
    s32 i;
    struct DigiEgg *kind;

    kind  = getDigiEgg(egg->eggKind);
    ready = TRUE;
    for (i = 0; i < 3; i++) {
        if (func_020995a4(kind->conditions[i], kind->values[i], egg, 0) == 0) {
            ready = FALSE;
            break;
        }
    }
    return ready;
}

/* Rolls the species that an egg of a kind hatches into, or -1. */
s16 rollEggSpecies(s16 kind) {
    s32 roll;
    s32 species = -1;
    struct DigiEgg *egg;
    s32 i;

    roll = getRandom(10000) / 100;
    egg  = getDigiEgg(kind);
    for (i = 0; i < 3; i++) {
        if (roll < egg->chance[i]) {
            species = egg->species[i];
            break;
        }
    }
    return species;
}
