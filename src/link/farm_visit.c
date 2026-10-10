#include "link/farm_visit.h"
#include "eggs/family_tree_sprites.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "farm/data.h"
#include "farm/goods_panel.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_tasks.h"
#include "field/map/map.h"
#include "link/exchange_data.h"

/* Checks a Digimon: -12 when the 40 records are in use, -10 for an egg (flag
 * 0x10), else 1. */
s32 func_0209ae68(struct Digimon *digimon) {
    u16 flags;

    flags = func_020a2c9c(digimon);
    if (func_020a3418() == 40) {
        return -12;
    }
    if (flags & 0x10) {
        return -10;
    }
    return 1;
}

/* Checks a Digimon: -10 for an egg (flag 0x10), -11 with flag 0x4, else 1. */
s32 func_0209ae38(struct Digimon *digimon) {
    u16 flags;

    flags = func_020a2c9c(digimon);
    if (flags & 0x10) {
        return -10;
    }
    if (flags & 4) {
        return -11;
    }
    return 1;
}

/* Frees the farm screen of the visit, keeping its task. */
void func_0209adfc(void) {
    struct FarmVisit *visit;

    visit = findTask(data_021da408);
    func_ov005_022890f0();
    func_0209abf8();
    func_ov005_0228a8b8();
    releaseGfxSlot(visit->gfxSlot);
    func_02097d2c();
    deleteMainActors();
    deleteSubActors();
}

/* Ends the visit of the other DS's farm: frees its screen and its map. */
void func_0209ad9c(void) {
    struct FarmVisit *visit;

    visit = findTask(data_021da408);
    func_ov005_022890f0();
    func_0209abf8();
    func_ov005_0228a8b8();
    func_ov005_02289a34();
    releaseGfxSlot(visit->gfxSlot);
    deleteMainActors();
    deleteSubActors();
    endMainActorTask();
    endSubActorTask();
    stopSubMapTask();
    func_02097d2c();
    endTask(visit);
    data_021da408 = 0;
}

/* Returns whether a farm visit runs. */
BOOL isFarmVisitRunning(void) {
    if (data_021da408 != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Returns the DigiEgg of a kind. */
struct DigiEgg *getDigiEgg(s16 kind) {
    return &DIGI_EGGS[kind];
}

/* Frees the 8 goods sprites of the farm screen (func_ov005_0228ac88). */
void func_0209abf8(void) {
    func_ov005_0228ac88();
}

/* Starts func_0209a694's task. */
void func_0209aa2c(s16 unk20, s32 unk24) {
    struct Task0209a694 *task;

    task          = createTask(func_0209a694, 0x113);
    data_021da3fc = getTaskId(task);
    task->state   = 0;
    task->wait    = 0;
    task->unk20   = unk20;
    task->unk24   = unk24;
}

/* Returns a farm of the other DS by its id, or NULL; -2 is the farm being
 * made (TEMP_FARM). */
struct Farm *func_0209a628(s32 id) {
    s32 i;

    if (id == -2) {
        /* declared an s32 in farm/data.h */
        return (struct Farm *) TEMP_FARM;
    }
    for (i = 0; i < 4; i++) {
        if (id == data_021da40c->groups[i].id) {
            break;
        }
    }
    if (i == 4) {
        return NULL;
    }
    return &data_021da40c->groups[i];
}

/* Returns a Digimon of the other DS by its id, or NULL. */
struct Digimon *func_0209a5d8(s32 id) {
    s32 i;

    if (id == 0) {
        return NULL;
    }
    for (i = 0; i < 40; i++) {
        if (id == data_021da40c->digimon[i].id) {
            return &data_021da40c->digimon[i];
        }
    }
    return NULL;
}

/* Returns one of the 50 farm goods of the other DS, or NULL. */
struct FarmGoods *func_0209a524(s32 index) {
    if (index >= 0 && index < 50) {
        return &data_021da40c->items[index];
    }
    return NULL;
}
