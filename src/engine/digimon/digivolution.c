#include "engine/digimon/digivolution.h"
#include "engine/data.h"

/* Adds an id of data_0210c11c to one of a Digimon's 4 slots: the slot that
 * has it or the first free one, recording the Digimon's species with it.
 * Returns FALSE when all 4 are taken. */
BOOL func_020a1c1c(struct Digimon *digimon, s16 id) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (id == digimon->unk22[i] || digimon->unk22[i] == -1) {
            digimon->unk22[i] = id;
            digimon->unk2C[i] = digimon->unk4;
            break;
        }
    }
    if (i == 4) {
        return FALSE;
    }
    return TRUE;
}
