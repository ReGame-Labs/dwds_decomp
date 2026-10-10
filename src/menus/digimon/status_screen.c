#include "menus/digimon/status_screen.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "menus/digimon/data.h"
#include "menus/widgets/digimon_detail.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Loads the graphics of the status screen's three backgrounds: entries 0xF,
 * 0xF and 4 of data_0213537c (/dat/bg/m_bg02 twice and md_flame00). */
void loadStatusScreenBgs(void) {
    const char **files;

    files                           = func_0204871c(0xF);
    data_ov006_0229f4cc.paletteFile = loadPaletteFile(&data_ov006_0229f4cc.palette, files[0]);
    data_ov006_0229f4cc.charFile    = loadCharFile(&data_ov006_0229f4cc.chars, files[1]);
    data_ov006_0229f4cc.screenFile  = loadScreenFile(&data_ov006_0229f4cc.screen, files[2]);

    files                           = func_0204871c(0xF);
    data_ov006_0229f4fc.paletteFile = loadPaletteFile(&data_ov006_0229f4fc.palette, files[0]);
    data_ov006_0229f4fc.charFile    = loadCharFile(&data_ov006_0229f4fc.chars, files[1]);
    data_ov006_0229f4fc.screenFile  = loadScreenFile(&data_ov006_0229f4fc.screen, files[2]);

    files                           = func_0204871c(4);
    data_ov006_0229f4e4.paletteFile = loadPaletteFile(&data_ov006_0229f4e4.palette, files[0]);
    data_ov006_0229f4e4.charFile    = loadCharFile(&data_ov006_0229f4e4.chars, files[1]);
    data_ov006_0229f4e4.screenFile  = loadScreenFile(&data_ov006_0229f4e4.screen, files[2]);
}

/* Stops the screen's palette effects and frees the backgrounds' graphics. */
void freeStatusScreenBgs(struct StatusScreen *screen) {
    stopSubPaletteEffectsButFades(screen->subPaletteEffect);
    stopMainPaletteEffectsButFades(screen->mainPaletteEffect);
    if (data_ov006_0229f4cc.paletteFile != NULL) {
        heapFree(data_ov006_0229f4cc.paletteFile);
        data_ov006_0229f4cc.paletteFile = NULL;
    }
    if (data_ov006_0229f4cc.charFile != NULL) {
        heapFree(data_ov006_0229f4cc.charFile);
        data_ov006_0229f4cc.charFile = NULL;
    }
    if (data_ov006_0229f4cc.screenFile != NULL) {
        heapFree(data_ov006_0229f4cc.screenFile);
        data_ov006_0229f4cc.screenFile = NULL;
    }
    if (data_ov006_0229f4fc.paletteFile != NULL) {
        heapFree(data_ov006_0229f4fc.paletteFile);
        data_ov006_0229f4fc.paletteFile = NULL;
    }
    if (data_ov006_0229f4fc.charFile != NULL) {
        heapFree(data_ov006_0229f4fc.charFile);
        data_ov006_0229f4fc.charFile = NULL;
    }
    if (data_ov006_0229f4fc.screenFile != NULL) {
        heapFree(data_ov006_0229f4fc.screenFile);
        data_ov006_0229f4fc.screenFile = NULL;
    }
    if (data_ov006_0229f4e4.paletteFile != NULL) {
        heapFree(data_ov006_0229f4e4.paletteFile);
        data_ov006_0229f4e4.paletteFile = NULL;
    }
    if (data_ov006_0229f4e4.charFile != NULL) {
        heapFree(data_ov006_0229f4e4.charFile);
        data_ov006_0229f4e4.charFile = NULL;
    }
    if (data_ov006_0229f4e4.screenFile != NULL) {
        heapFree(data_ov006_0229f4e4.screenFile);
        data_ov006_0229f4e4.screenFile = NULL;
    }
}

/* Clears both screens' backgrounds and sprites and switches their blending
 * off, as main's clearScreens does. */
void func_ov006_0228cd80(void) {
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

/* Loads the fonts the status screen writes with (data_02127184's): font_dg,
 * font00, font_s and font_s2 on each screen. */
void loadStatusScreenFonts(void) {
    func_020a9c40(1, 3, 0xF);
    func_020a9c40(2, 5, 0xF);
    func_020a9c40(4, 7, 0xF);
    func_020a9c40(5, 9, 0xF);
    func_020a9ae0(1, 2, 0xF);
    func_020a9ae0(2, 4, 0xF);
    func_020a9ae0(4, 6, 0xF);
    func_020a9ae0(5, 8, 0xF);
}

/* Unloads the fonts of loadStatusScreenFonts. */
void unloadStatusScreenFonts(void) {
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a98a8(4);
    func_020a98a8(5);
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(4);
    func_020a9844(5);
}

/* Has func_ov006_0228cbc0 draw again, if the status screen is up. */
void func_ov006_0228cc70(void) {
    struct StatusScreen *screen = findTask(STATUS_SCREEN_TASK_ID);

    if (screen != NULL) {
        screen->flags |= 1;
    }
}

/* Closes the Digimon's details that func_ov006_0228cb14 draws. */
void func_ov006_0228caf4(void) {
    freeDigimonDetailSprites(0);
    func_02059c50(0);
}
