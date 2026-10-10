#include "engine/digimon/digimon_records.h"
#include "battle/exp_level_up.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/digimon/species_flags.h"
#include "engine/libs.h"
#include "engine/save/game_state.h"
#include "engine/save/progress.h"
#include "engine/system/system.h"
#include "engine/ui/gauge.h"
#include "items/inventory.h"

/* Picks one of the bits set in mask at random and returns its number. */
u8 func_020a2f3c(s32 mask) {
    u8 bits[8];
    u16 count;
    s32 i;

    count = 0;
    for (i = 0; i < 8; i++) {
        if (mask & (1 << i)) {
            bits[count] = i;
            count++;
        }
    }
    return bits[(u8) (getRandom(0xFFFF) % count)];
}

/* Empties the 10 party slots. */
void func_020a2f14(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        SAVE->party[i] = 0;
    }
}

/* Puts a Digimon in a party slot. */
void func_020a2f04(s32 slot, s32 id) {
    data_021db804[slot] = id;
}

/* Takes a Digimon out of the party and frees what it has equipped
 * (unequipWeapon, unequipArmor, unequipAccessory). Returns its slot, or -1. */
s32 func_020a2da8(s32 id) {
    s32 *party;
    s32 i;

    party = data_021db804;
    for (i = 0; i < 10; i++) {
        if (id == party[i]) {
            party[i] = 0;
            break;
        }
    }
    if (i == 10) {
        return -1;
    }
    unequipWeapon(id);
    unequipArmor(id);
    unequipAccessory(id);
    return i;
}

/* Returns the id of the Digimon in a party slot. */
s32 func_020a2d98(s32 slot) {
    return data_021db804[slot];
}

/* Returns the party slot of a Digimon, or -1. */
s32 func_020a2d60(s32 id) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (id == SAVE->party[i]) {
            break;
        }
    }
    if (i == 10) {
        i = -1;
    }
    return i;
}

/* Sets status bits (unk108) of a Digimon by its id. */
void func_020a2d48(s32 id, u16 bits) {
    func_020a2d34(getDigimon(id), bits);
}

/* Sets status bits (unk108) of a Digimon. record is a void * for the callers
 * that still hold a Digimon as an s32 *. */
void func_020a2d34(void *record, u16 bits) {
    struct Digimon *digimon = record;

    digimon->unk108 |= bits;
}

/* Clears status bits (unk108) of a Digimon by its id. */
void func_020a2d1c(s32 id, u16 bits) {
    func_020a2cc0(getDigimon(id), bits);
}

/* Returns the status bits (unk108) of a Digimon by its id. */
u16 func_020a2ca8(s32 id) {
    return func_020a2c9c(getDigimon(id));
}

/* Returns the status bits (unk108) of a Digimon: 0x10 for an egg, 0x20 for
 * one of the other DS's. */
u16 func_020a2c9c(struct Digimon *digimon) {
    return digimon->unk108;
}

/* Counts the Digimon in the party. */
s32 func_020a2c6c(void) {
    s32 i;
    s32 count;

    i     = 0;
    count = 0;
    do {
        if (SAVE->party[i] != 0) {
            count++;
        }
        i++;
    } while (i < 10);
    return count;
}

/* Adds a Digimon of a species in the first free record, with a new id, and
 * returns its index, or -1 when the 40 are in use. */
s32 addDigimon(s32 species) {
    s32 i;
    struct Digimon *records = data_021db82c;
    struct Digimon *digimon;

    for (i = 0; i < 40; i++) {
        if (records[i].id == 0) {
            digimon = &records[i];
            func_020e23c0(digimon, 0, sizeof(struct Digimon));
            digimon->id = takeNextId();
            func_020a29c4(species, digimon);
            records[i].expToNext = getLevelUpExpById(records[i].id, records[i].level);
            func_020a0fd8(species);
            func_0209fdf0(digimon->parents);
            func_020a02f4();
            return i;
        }
    }
    return -1;
}
