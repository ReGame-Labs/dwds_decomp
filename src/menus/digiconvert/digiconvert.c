#include "menus/digiconvert/digiconvert.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "menus/digiconvert/digiconvert_data.h"
#include "menus/widgets/window_anim.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Loads the screen's backgrounds: m_bg02 twice and m_kaiten. */
void loadDigiconvertBgs(struct Digiconvert *digiconvert) {
    const char **files;

    files                                  = func_0204871c(0xF);
    digiconvert->work->bg02[1].paletteFile = loadPaletteFile(&digiconvert->work->bg02[1].palette, files[0]);
    digiconvert->work->bg02[1].charFile    = loadCharFile(&digiconvert->work->bg02[1].chars, files[1]);
    digiconvert->work->bg02[1].screenFile  = loadScreenFile(&digiconvert->work->bg02[1].screen, files[2]);
    files                                  = func_0204871c(0xF);
    digiconvert->work->bg02[0].paletteFile = loadPaletteFile(&digiconvert->work->bg02[0].palette, files[0]);
    digiconvert->work->bg02[0].charFile    = loadCharFile(&digiconvert->work->bg02[0].chars, files[1]);
    digiconvert->work->bg02[0].screenFile  = loadScreenFile(&digiconvert->work->bg02[0].screen, files[2]);
    files                                  = func_0204871c(0xE);
    digiconvert->work->kaiten.paletteFile  = loadPaletteFile(&digiconvert->work->kaiten.palette, files[0]);
    digiconvert->work->kaiten.charFile     = loadCharFile(&digiconvert->work->kaiten.chars, files[1]);
    digiconvert->work->kaiten.screenFile   = loadScreenFile(&digiconvert->work->kaiten.screen, files[2]);
}

/* Frees the backgrounds' files. */
void freeDigiconvertBgs(struct Digiconvert *digiconvert) {
    void *file;

    stopSubPaletteEffectsButFades(digiconvert->unkA0);
    stopMainPaletteEffectsButFades(digiconvert->unkA4);
    file = digiconvert->work->bg02[1].paletteFile;
    if (file != NULL) {
        heapFree(file);
        digiconvert->work->bg02[1].paletteFile = NULL;
    }
    file = digiconvert->work->bg02[1].charFile;
    if (file != NULL) {
        heapFree(file);
        digiconvert->work->bg02[1].charFile = NULL;
    }
    file = digiconvert->work->bg02[1].screenFile;
    if (file != NULL) {
        heapFree(file);
        digiconvert->work->bg02[1].screenFile = NULL;
    }
    file = digiconvert->work->bg02[0].paletteFile;
    if (file != NULL) {
        heapFree(file);
        digiconvert->work->bg02[0].paletteFile = NULL;
    }
    file = digiconvert->work->bg02[0].charFile;
    if (file != NULL) {
        heapFree(file);
        digiconvert->work->bg02[0].charFile = NULL;
    }
    file = digiconvert->work->bg02[0].screenFile;
    if (file != NULL) {
        heapFree(file);
        digiconvert->work->bg02[0].screenFile = NULL;
    }
    file = digiconvert->work->kaiten.paletteFile;
    if (file != NULL) {
        heapFree(file);
        digiconvert->work->kaiten.paletteFile = NULL;
    }
    file = digiconvert->work->kaiten.charFile;
    if (file != NULL) {
        heapFree(file);
        digiconvert->work->kaiten.charFile = NULL;
    }
    file = digiconvert->work->kaiten.screenFile;
    if (file == NULL) {
        return;
    }
    heapFree(file);
    digiconvert->work->kaiten.screenFile = NULL;
}

/* Clears both screens' backgrounds, sprites and blending. */
void clearDigiconvertScreens(void) {
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

/* Loads the window frame and m_listbg00 (bg file 0xD). */
void func_0205f6cc(void) {
    loadSubWindowFrameInSlot(1, 2);
    func_020aa2c0(func_0204871c(0xD), 0, -1, 2);
}

/* Unloads the window frame and m_listbg00. */
void func_0205f6b0(void) {
    unloadSubWindowFrame();
    func_020a9610(0);
}
