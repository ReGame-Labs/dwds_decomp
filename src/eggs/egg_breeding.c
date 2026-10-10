#include "eggs/egg_breeding.h"
#include "eggs/family_tree_sprites.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "engine/palette/palette_fade.h"
#include "engine/save/progress.h"
#include "engine/system/system.h"
#include "engine/ui/gauge.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/panel_pages.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_tasks.h"
#include "link/farm_visit.h"

/* Returns whether a species is one of a Digimon's parents. */
BOOL func_02099578(s32 species, struct Digimon *digimon) {
    if (species == digimon->parents[0].species || species == digimon->parents[1].species) {
        return TRUE;
    }
    return FALSE;
}

/* Returns whether a species is one of a Digimon's grandparents. */
BOOL func_02099534(s32 species, struct Digimon *digimon) {
    if (species == digimon->grandparents[0].species || species == digimon->grandparents[1].species ||
        species == digimon->grandparents[2].species || species == digimon->grandparents[3].species) {
        return TRUE;
    }
    return FALSE;
}

/* Grades a parent for its egg's size, 7 to 21: 1 to 3 points for each of its
 * max HP, max MP, unk48-unk4E and unk70. */
s32 func_020993dc(struct Digimon *digimon) {
    s32 grade = 0;

    if (digimon->maxHp >= 1200) {
        grade += 3;
    } else if (digimon->maxHp >= 300) {
        grade += 2;
    } else {
        grade += 1;
    }
    if (digimon->maxMp >= 1200) {
        grade += 3;
    } else if (digimon->maxMp >= 300) {
        grade += 2;
    } else {
        grade += 1;
    }
    if (digimon->unk48 >= 300) {
        grade += 3;
    } else if (digimon->unk48 >= 90) {
        grade += 2;
    } else {
        grade += 1;
    }
    if (digimon->unk4A >= 300) {
        grade += 3;
    } else if (digimon->unk4A >= 90) {
        grade += 2;
    } else {
        grade += 1;
    }
    if (digimon->unk4C >= 300) {
        grade += 3;
    } else if (digimon->unk4C >= 90) {
        grade += 2;
    } else {
        grade += 1;
    }
    if (digimon->unk4E >= 300) {
        grade += 3;
    } else if (digimon->unk4E >= 90) {
        grade += 2;
    } else {
        grade += 1;
    }
    if (digimon->unk70 >= 90) {
        grade += 3;
    } else if (digimon->unk70 >= 60) {
        grade += 2;
    } else {
        grade += 1;
    }
    return grade;
}

/* Shows a Digimon of the other DS in the farm's panel pages, as the Digimon
 * of id -2. */
void func_020993a4(s32 id, s32 unk2D, s32 unk30) {
    /* declared an s32 in farm/data.h */
    data_ov005_022a1d14 = (s32) func_0209a5d8(id);
    func_ov005_02280d24(-2, unk2D, unk30); /* kept at 0x2D and 0x30 of its task */
}

/* Makes an egg of a kind and size from two parents, and records it in the
 * DigiEgg gallery: one more egg of the kind and, for the biggest yet, its
 * size and its parents' species. Returns the egg's id, or 0 when the 40
 * records are in use. */
s32 createEgg(s8 kind, s16 size, struct Digimon *parentA, u16 *tamerA, struct Digimon *parentB, u16 *tamerB) {
    struct Digimon *egg;
    struct EggRecord *record;

    egg = getDigimonAt(addDigimon(kind + 378));
    if (egg == NULL) {
        return 0;
    }
    egg->eggKind = kind;
    egg->unk1E   = 0;
    egg->eggSize = size;
    func_020a2d34(egg, 0x10);
    func_0209fcb8(egg, parentA, tamerA, parentB, tamerB);
    record = &EGG_GALLERY[kind];
    record->count++;
    if (record->count > 99) {
        record->count = 99;
    }
    if (record->bestSize < size) {
        record->bestSize = size;
        record->parentA  = parentA->unk4;
        record->parentB  = parentB->unk4;
    }
    func_020b4cf8(egg);
    return egg->id;
}

/* Opens the DigiEgg gallery (UI flag 0xF). */
void func_0209928c(void) {
    struct EggGallery *gallery;

    gallery        = createTask(func_02098ea0, 0x113);
    gallery->state = 0;
    gallery->wait  = 0;
    data_021da408  = getTaskId(gallery);
    setUiFlag(0xF);
}

/* Returns whether the DigiEgg gallery is open. */
BOOL func_02098e7c(void) {
    if (getUiFlag(0xF) != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Closes the DigiEgg gallery. */
void func_02098e08(void) {
    struct EggGallery *gallery;

    gallery = findTask(data_021da408);
    func_02097d2c();
    func_0208577c(3, gallery->unk22);
    func_02085710(3, gallery->unk24);
    stopMainPaletteEffects(gallery->unk20);
    stopSubPaletteEffects(gallery->unk21);
    deleteMainActors();
    deleteSubActors();
    endMainActorTask();
    endSubActorTask();
    endTask(gallery);
    data_021da408 = 0;
    clearUiFlag(0xF);
}
