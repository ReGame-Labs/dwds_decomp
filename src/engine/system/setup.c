#include "engine/system/setup.h"
#include "engine/bg/bg_affine.h"
#include "engine/bg/bg_load.h"
#include "engine/bg/bg_screen.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/palette/palette_fade.h"
#include "engine/save/save_data.h"
#include "engine/system/display.h"
#include "engine/ui/buttons.h"
#include "engine/ui/captions.h"
#include "engine/ui/digimon_list.h"
#include "field/actors/actor_tasks.h"
#include "link/exchange_start.h"
#include "link/wifi_connect.h"
#include "menus/digiconvert/digiconvert_open.h"
#include "menus/widgets/menu_displays.h"
#include "menus/widgets/scroll_bar.h"
#include "menus/widgets/text_list.h"
#include "nitro/g2d.h"
#include "nitro/mmap.h"

/* Copies the main screen's shadow OAM, with its affine parameters, to the
 * OAM by the copy queue. */
void flushMainOam(void) {
    s32 i;
    s32 j;

    for (j = 0, i = 0; i < OAM_AFFINE_COUNT; i++, j += 4) {
        MAIN_OAM[j].attr[3]     = MAIN_OAM_AFFINE[i][0];
        MAIN_OAM[j + 1].attr[3] = MAIN_OAM_AFFINE[i][1];
        MAIN_OAM[j + 2].attr[3] = MAIN_OAM_AFFINE[i][2];
        MAIN_OAM[j + 3].attr[3] = MAIN_OAM_AFFINE[i][3];
    }
    {
        struct VramCopy copy = {0};

        copy.src  = MAIN_OAM;
        copy.dest = (void *) HW_OAM;
        copy.size = sizeof(MAIN_OAM);
        queueVramTransfer(&copy);
    }
}

/* The same for the sub screen's. */
void flushSubOam(void) {
    s32 i;
    s32 j;

    for (j = 0, i = 0; i < OAM_AFFINE_COUNT; i++, j += 4) {
        SUB_OAM[j].attr[3]     = SUB_OAM_AFFINE[i][0];
        SUB_OAM[j + 1].attr[3] = SUB_OAM_AFFINE[i][1];
        SUB_OAM[j + 2].attr[3] = SUB_OAM_AFFINE[i][2];
        SUB_OAM[j + 3].attr[3] = SUB_OAM_AFFINE[i][3];
    }
    {
        struct VramCopy copy = {0};

        copy.src  = SUB_OAM;
        copy.dest = (void *) HW_DB_OAM;
        copy.size = sizeof(MAIN_OAM);
        queueVramTransfer(&copy);
    }
}

/* One pass of a bubble sort of the main screen's shadow OAM by the entries'
 * keys, after its affine entries. */
void sortMainOam(void) {
    s16 i;

    for (i = data_021b3d74 + 1; i < OAM_COUNT - 1; i++) {
        if (MAIN_OAM_KEYS[i] > MAIN_OAM_KEYS[i + 1]) {
            u16 key = MAIN_OAM_KEYS[i];
            union OamAttr entry;

            MAIN_OAM_KEYS[i]     = MAIN_OAM_KEYS[i + 1];
            MAIN_OAM_KEYS[i + 1] = key;
            entry                = MAIN_OAM[i];
            MAIN_OAM[i]          = MAIN_OAM[i + 1];
            MAIN_OAM[i + 1]      = entry;
        }
    }
}

/* The same for the sub screen's. */
void sortSubOam(void) {
    s16 i;

    for (i = data_021b3d6c + 1; i < OAM_COUNT - 1; i++) {
        if (SUB_OAM_KEYS[i] > SUB_OAM_KEYS[i + 1]) {
            u16 key = SUB_OAM_KEYS[i];
            union OamAttr entry;

            SUB_OAM_KEYS[i]     = SUB_OAM_KEYS[i + 1];
            SUB_OAM_KEYS[i + 1] = key;
            entry               = SUB_OAM[i];
            SUB_OAM[i]          = SUB_OAM[i + 1];
            SUB_OAM[i + 1]      = entry;
        }
    }
}

/* Sets the main screen's affine parameters of an index to a rotation, in
 * 256ths of a turn. */
void setMainOamRotation(s32 index, s32 angle) {
    MAIN_OAM_AFFINE[index][3] = COSINE_TABLE[angle];
    MAIN_OAM_AFFINE[index][0] = MAIN_OAM_AFFINE[index][3];
    MAIN_OAM_AFFINE[index][2] = SINE_TABLE[angle];
    MAIN_OAM_AFFINE[index][1] = -SINE_TABLE[angle];
}

/* The same for the sub screen. */
void setSubOamRotation(s32 index, s32 angle) {
    SUB_OAM_AFFINE[index][3] = COSINE_TABLE[angle];
    SUB_OAM_AFFINE[index][0] = SUB_OAM_AFFINE[index][3];
    SUB_OAM_AFFINE[index][2] = SINE_TABLE[angle];
    SUB_OAM_AFFINE[index][1] = -SINE_TABLE[angle];
}

/* Takes the main screen's next affine parameters for a cell's scale and
 * rotation, and returns their index. The indices are taken from the last. */
s8 allocMainOamAffine(struct CellTransform *transform) {
    s8 index = MAIN_OAM_AFFINE_NEXT;

    setMainOamAffine(index, transform->scaleX >> 4, transform->scaleY >> 4, transform->angle >> 8);
    MAIN_OAM_AFFINE_NEXT--;
    if (MAIN_OAM_AFFINE_NEXT < 0) {
        MAIN_OAM_AFFINE_NEXT = 0;
    }
    return index;
}

/* The same for the sub screen. */
s8 allocSubOamAffine(struct CellTransform *transform) {
    s8 index = SUB_OAM_AFFINE_NEXT;

    setSubOamAffine(index, transform->scaleX >> 4, transform->scaleY >> 4, transform->angle >> 8);
    SUB_OAM_AFFINE_NEXT--;
    if (SUB_OAM_AFFINE_NEXT < 0) {
        SUB_OAM_AFFINE_NEXT = 0;
    }
    return index;
}

/* Takes the main screen's next affine parameters for a cell's rotation alone. */
s8 allocMainOamRotation(struct CellTransform *transform) {
    s8 index;

    index = MAIN_OAM_AFFINE_NEXT;
    setMainOamRotation((u8) index, (u8) ((s32) transform->angle >> 8));
    MAIN_OAM_AFFINE_NEXT -= 1;
    if ((s32) MAIN_OAM_AFFINE_NEXT < 0) {
        MAIN_OAM_AFFINE_NEXT = 0;
    }
    return index;
}

/* The same for the sub screen. */
s8 allocSubOamRotation(struct CellTransform *transform) {
    s8 index;

    index = SUB_OAM_AFFINE_NEXT;
    setSubOamRotation((u8) index, (u8) ((s32) transform->angle >> 8));
    SUB_OAM_AFFINE_NEXT -= 1;
    if ((s32) SUB_OAM_AFFINE_NEXT < 0) {
        SUB_OAM_AFFINE_NEXT = 0;
    }
    return index;
}

/* Loads ov001 and opens the converter. */
void func_02044654(void) {
    loadOverlay(3);
    openDigiconvert();
}

/* Marks a system set up. */
void setSystemSetUp(s32 flag) {
    setBit(flag, SYSTEM_FLAGS);
}

/* Marks a system no longer set up. */
void clearSystemSetUp(s32 flag) {
    clearBit(flag, SYSTEM_FLAGS);
}

/* Whether a system is set up. */
s32 isSystemSetUp(s32 flag) {
    return (s32) (u8) testBit(flag, SYSTEM_FLAGS);
}

/* Sets up the game's systems once, when the game starts: empties the species
 * data's caches, counts the species that count as their own, and inits the
 * sprites, the dials, the backgrounds' tables, the menus and the save. */
void initSystems(void) {
    s32 i;
    s32 count;
    u8 *flags;

    count         = 0;
    i             = 0;
    data_021da780 = 0xFFFF;
    data_021da784 = 0xFFFF;
    data_021da77c = 0xFFFF;
    data_021da778 = 0xFFFF;
    data_021da788 = 0xFFFF;
    do {
        if (((struct SpeciesData *) loadSpeciesData(i++))->listed != 0) {
            count++;
        }
    } while (i < SPECIES_COUNT);
    data_021da774 = count;
    func_02042f44();
    func_02043c40();
    func_0204514c();
    initBgAffine();
    initSprites();
    resetExchangeGlobals();
    resetMenuDisplays();
    resetWifiMenuGlobals();
    /* The system flags, cleared a byte at a time. */
    flags    = (u8 *) SYSTEM_FLAGS;
    flags[0] = 0;
    flags[1] = 0;
    func_020c8b6c();
    initScrollBars();
    initTextLists();
    resetSaveWriter();
}

/* Loads a background's palette into the main screen's palettes for a BG of the
 * main screen (0-3), the sub screen's for the others. */
void loadBgPalette(s32 bg, struct NNSG2dPaletteData *palette) {
    if (bg <= 3) {
        loadMainPalette(0x100, (u32) (palette->szByte << 0xF) >> 0x10, (s32) palette->pRawData);
        return;
    }
    loadSubPalette(0x100, (u32) (palette->szByte << 0xF) >> 0x10, (s32) palette->pRawData);
}
