#include "menus/digimon/guide_graphics.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/window/window.h"
#include "field/actors/actor_commands.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_facing.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_walk.h"
#include "field/actors/route_run.h"
#include "menus/digimon/data.h"
#include "menus/digimon/guide_windows.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Walks the cursor's Digimon in from the left as sub screen actor 0 (made by
 * func_020c7520), or walks it back out and deletes it, waiting for each walk.
 * The cast is that of func_020c7520's u16 id, which its header doesn't give
 * yet. */
void func_ov006_0229c7bc(struct DigimonGuide *guide) {
    struct Actor *actor;

    switch (guide->actorState) {
        case 0:
            break;
        case 1:
            if (data_ov006_0229f548[guide->scroll + guide->cursor] == 0xFFFE ||
                data_ov006_0229f548[guide->scroll + guide->cursor] == 0xFFFF) {
                guide->actorState = 0;
                return;
            }
            guide->actorState++;
            func_020c7520((u16) func_020a3224(data_ov006_0229f548[guide->scroll + guide->cursor]), -0x20, 0x38, 0x10, 0);
            setSubActorPriority(0, 0);
            walkSubActorTo(0, 0, 0xE0, 0x38, 2);
            break;
        case 2:
            if (getSubActor(0) == NULL) {
                guide->actorState = 0;
                return;
            }
            if (isSubActorWalkDone(0) != 0) {
                guide->actorState++;
            }
            break;
        case 3:
            actor = getSubActor(0);
            if (actor == NULL) {
                guide->actorState = 0;
                return;
            }
            fixSubActorFacing(0);
            setActorAnimation(actor, 0x11);
            guide->actorState = 0;
            break;
        case 1001:
            stopSubActorWalk(0);
            freeSubActorFacing(0);
            walkSubActorTo(0, 0, -0x20, 0x38, 3);
            guide->actorState++;
            break;
        case 1002:
            if (getSubActor(0) == NULL) {
                guide->actorState = 0;
                return;
            }
            if (isSubActorWalkDone(0) != 0) {
                guide->actorState++;
            }
            break;
        case 1003:
            func_020c6fb8(0);
            guide->actorState = 0;
            break;
    }
}

/* Places sprite 0 of each screen by the scroll, and the rows' sprites at the
 * left of the rows. */
void func_ov006_0229c6f4(struct DigimonGuide *guide) {
    s32 i;
    struct Sprite *subSprite;
    struct Sprite *mainSprite;
    struct Window *window;
    s32 row;

    subSprite  = getSubSprite(0);
    mainSprite = getMainSprite(0);
    if (subSprite != NULL && mainSprite != NULL) {
        subSprite->x  = data_ov006_0229f528;
        subSprite->y  = data_ov006_0229f538 + 0x120;
        mainSprite->x = data_ov006_0229f528;
        mainSprite->y = data_ov006_0229f538;
    }
    window = getWindow(guide->listWindow);
    if (window == NULL) {
        return;
    }
    for (i = 0, row = 1; i < 8; i++, row += 2) {
        mainSprite    = getMainSprite(data_ov006_0229f610[i]);
        mainSprite->x = window->x * 8 + 8;
        mainSprite->y = (window->y + row) * 8;
    }
}

/* Loads the window frames (func_ov006_0229bdd4) and the graphics of two
 * backgrounds, entries 0xF and 4 of data_0213537c (/dat/bg/m_bg02 and
 * md_flame00). */
void func_ov006_0229c638(void) {
    const char **files;

    func_ov006_0229bdd4();
    files                           = func_0204871c(0xF);
    data_ov006_0229f5a0.paletteFile = loadPaletteFile(&data_ov006_0229f5a0.palette, files[0]);
    data_ov006_0229f5a0.charFile    = loadCharFile(&data_ov006_0229f5a0.chars, files[1]);
    data_ov006_0229f5a0.screenFile  = loadScreenFile(&data_ov006_0229f5a0.screen, files[2]);
    files                           = func_0204871c(4);
    data_ov006_0229f5b8.paletteFile = loadPaletteFile(&data_ov006_0229f5b8.palette, files[0]);
    data_ov006_0229f5b8.charFile    = loadCharFile(&data_ov006_0229f5b8.chars, files[1]);
    data_ov006_0229f5b8.screenFile  = loadScreenFile(&data_ov006_0229f5b8.screen, files[2]);
}

/* Frees the files func_ov006_0229c638 loaded. */
void func_ov006_0229c4d4(void) {
    void *file;

    file = data_ov006_0229f5a0.paletteFile;
    if (file != NULL) {
        heapFree(file);
        data_ov006_0229f5a0.paletteFile = NULL;
    }
    file = data_ov006_0229f5a0.charFile;
    if (file != NULL) {
        heapFree(file);
        data_ov006_0229f5a0.charFile = NULL;
    }
    file = data_ov006_0229f5a0.screenFile;
    if (file != NULL) {
        heapFree(file);
        data_ov006_0229f5a0.screenFile = NULL;
    }
    file = data_ov006_0229f5b8.paletteFile;
    if (file != NULL) {
        heapFree(file);
        data_ov006_0229f5b8.paletteFile = NULL;
    }
    file = data_ov006_0229f5b8.charFile;
    if (file != NULL) {
        heapFree(file);
        data_ov006_0229f5b8.charFile = NULL;
    }
    file = data_ov006_0229f5b8.screenFile;
    if (file != NULL) {
        heapFree(file);
        data_ov006_0229f5b8.screenFile = NULL;
    }
}

/* Clears both screens' backgrounds and sprites and switches their blending
 * off, as clearScreens does. */
void func_ov006_0229c164(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    G2_BlendNone();
    MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    G2S_BlendNone();
}

/* Loads the graphics of entry 0xE of data_0213537c, /dat/bg/m_kaiten
 * (probably the order dial's: "kaiten" is Japanese for turning). */
void func_ov006_0229c104(void) {
    const char **files;

    files                           = func_0204871c(0xE);
    data_ov006_0229f588.paletteFile = loadPaletteFile(&data_ov006_0229f588.palette, files[0]);
    data_ov006_0229f588.charFile    = loadCharFile(&data_ov006_0229f588.chars, files[1]);
    data_ov006_0229f588.screenFile  = loadScreenFile(&data_ov006_0229f588.screen, files[2]);
}

/* Frees the graphics func_ov006_0229c104 loaded. */
void func_ov006_0229c04c(void) {
    void *file;

    file = data_ov006_0229f588.paletteFile;
    if (file != NULL) {
        heapFree(file);
        data_ov006_0229f588.paletteFile = NULL;
    }
    file = data_ov006_0229f588.charFile;
    if (file != NULL) {
        heapFree(file);
        data_ov006_0229f588.charFile = NULL;
    }
    file = data_ov006_0229f588.screenFile;
    if (file != NULL) {
        heapFree(file);
        data_ov006_0229f588.screenFile = NULL;
    }
}
