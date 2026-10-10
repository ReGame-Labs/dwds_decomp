#include "menus/farm_stats/stats_screen.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "nitro/g2.h"
#include "nitro/mmap.h"

/* Loads the screen's three backgrounds, entries 0xF, 0xF and 4 of
 * data_0213537c. */
void loadStatsScreenBgs(void) {
    const char **files;

    files                     = func_0204871c(0xF);
    data_021f5c8c.paletteFile = loadPaletteFile(&data_021f5c8c.palette, files[0]);
    data_021f5c8c.charFile    = loadCharFile(&data_021f5c8c.chars, files[1]);
    data_021f5c8c.screenFile  = loadScreenFile(&data_021f5c8c.screen, files[2]);
    files                     = func_0204871c(0xF);
    data_021f5cbc.paletteFile = loadPaletteFile(&data_021f5cbc.palette, files[0]);
    data_021f5cbc.charFile    = loadCharFile(&data_021f5cbc.chars, files[1]);
    data_021f5cbc.screenFile  = loadScreenFile(&data_021f5cbc.screen, files[2]);
    files                     = func_0204871c(4);
    data_021f5ca4.paletteFile = loadPaletteFile(&data_021f5ca4.palette, files[0]);
    data_021f5ca4.charFile    = loadCharFile(&data_021f5ca4.chars, files[1]);
    data_021f5ca4.screenFile  = loadScreenFile(&data_021f5ca4.screen, files[2]);
}

/* Frees what the screen holds of func_02083e78/func_02083ea8 and the files of
 * its three backgrounds. */
void freeStatsScreenBgs(struct StatsScreen *screen) {
    void *file;

    stopSubPaletteEffectsButFades(screen->unk40);
    stopMainPaletteEffectsButFades(screen->unk44);
    file = data_021f5c8c.paletteFile;
    if (file != NULL) {
        heapFree(file);
        data_021f5c8c.paletteFile = NULL;
    }
    file = data_021f5c8c.charFile;
    if (file != NULL) {
        heapFree(file);
        data_021f5c8c.charFile = NULL;
    }
    file = data_021f5c8c.screenFile;
    if (file != NULL) {
        heapFree(file);
        data_021f5c8c.screenFile = NULL;
    }
    file = data_021f5cbc.paletteFile;
    if (file != NULL) {
        heapFree(file);
        data_021f5cbc.paletteFile = NULL;
    }
    file = data_021f5cbc.charFile;
    if (file != NULL) {
        heapFree(file);
        data_021f5cbc.charFile = NULL;
    }
    file = data_021f5cbc.screenFile;
    if (file != NULL) {
        heapFree(file);
        data_021f5cbc.screenFile = NULL;
    }
    file = data_021f5ca4.paletteFile;
    if (file != NULL) {
        heapFree(file);
        data_021f5ca4.paletteFile = NULL;
    }
    file = data_021f5ca4.charFile;
    if (file != NULL) {
        heapFree(file);
        data_021f5ca4.charFile = NULL;
    }
    file = data_021f5ca4.screenFile;
    if (file == NULL) {
        return;
    }
    heapFree(file);
    data_021f5ca4.screenFile = NULL;
}

/* Clears both screens' background and object VRAM and OAM, and turns their
 * blending off. */
void func_020cb6fc(void) {
    func_020e233c(0, HW_BG_VRAM, HW_BG_VRAM_SIZE);
    func_020e233c(0, HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    func_020e233c(0, HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    G2_BlendNone();
    func_020e233c(0, HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    func_020e233c(0, HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    func_020e233c(0, HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    G2S_BlendNone();
}

/* Takes entries 1, 2, 4 and 5 of func_020a9c40 and of func_020a9ae0. */
void func_020cb66c(void) {
    func_020a9c40(1, 3, 0xF);
    func_020a9c40(2, 5, 0xF);
    func_020a9c40(4, 7, 0xF);
    func_020a9c40(5, 9, 0xF);
    func_020a9ae0(1, 2, 0xF);
    func_020a9ae0(2, 4, 0xF);
    func_020a9ae0(4, 6, 0xF);
    func_020a9ae0(5, 8, 0xF);
}

/* Lets go of what func_020cb66c took (func_020a98a8, func_020a9844). */
void func_020cb61c(void) {
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a98a8(4);
    func_020a98a8(5);
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(4);
    func_020a9844(5);
}

/* Has the open View Stats screen draw its Digimon's battle model again. */
void func_020cb5ec(void) {
    struct StatsScreen *screen;

    screen = findTask(STATS_SCREEN_TASK_ID);
    if (screen != NULL) {
        screen->flags |= STATS_SHOW_MODEL;
    }
}
