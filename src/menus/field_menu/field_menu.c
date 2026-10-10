#include "menus/field_menu/field_menu.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Loads the menu's two backgrounds, 0xF ("m_bg02") and 4. */
void loadFieldMenuBgs(struct FieldMenuTask *task) {
    const char **paths;
    const char **paths2;

    paths                       = func_0204871c(0xF);
    task->work->bg.paletteFile  = loadPaletteFile(&task->work->bg.palette, paths[0]);
    task->work->bg.charFile     = loadCharFile(&task->work->bg.chars, paths[1]);
    task->work->bg.screenFile   = loadScreenFile(&task->work->bg.screen, paths[2]);
    paths2                      = func_0204871c(4);
    task->work->bg2.paletteFile = loadPaletteFile(&task->work->bg2.palette, paths2[0]);
    task->work->bg2.charFile    = loadCharFile(&task->work->bg2.chars, paths2[1]);
    task->work->bg2.screenFile  = loadScreenFile(&task->work->bg2.screen, paths2[2]);
}

/* Frees what loadFieldMenuBgs loaded, and unk30 and unk34. */
void freeFieldMenuBgs(struct FieldMenuTask *task) {
    void *file;

    stopSubPaletteEffectsButFades(task->unk30);
    stopMainPaletteEffectsButFades(task->unk34);
    file = task->work->bg.paletteFile;
    if (file != NULL) {
        heapFree(file);
        task->work->bg.paletteFile = NULL;
    }
    file = task->work->bg.charFile;
    if (file != NULL) {
        heapFree(file);
        task->work->bg.charFile = NULL;
    }
    file = task->work->bg.screenFile;
    if (file != NULL) {
        heapFree(file);
        task->work->bg.screenFile = NULL;
    }
    file = task->work->bg2.paletteFile;
    if (file != NULL) {
        heapFree(file);
        task->work->bg2.paletteFile = NULL;
    }
    file = task->work->bg2.charFile;
    if (file != NULL) {
        heapFree(file);
        task->work->bg2.charFile = NULL;
    }
    file = task->work->bg2.screenFile;
    if (file == NULL) {
        return;
    }
    heapFree(file);
    task->work->bg2.screenFile = NULL;
}

/* Clears both screens' background and sprite VRAM and their sprites, takes
 * their VRAM banks away (GX_DisableBankFor*) and turns their blending off. */
void clearBgAndSpriteVram(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    REG_BLDCNT = 0;
    MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    REG_DB_BLDCNT = 0;
}

/* Sets up the menu's text slots: 1, 2, 4 and 5 of the main screen and 2 of
 * the sub screen (func_020a9ae0, func_020a9c40). */
void initFieldMenuText(struct FieldMenuTask *task) {
    func_020a9ae0(1, 2, 0xF);
    func_020a9ae0(2, 3, 0xF);
    func_020a9ae0(4, 4, 0xF);
    func_020a9ae0(5, 5, 0xF);
    func_020a9c40(2, 6, 0xF);
}

/* Frees them. */
void freeFieldMenuText(void) {
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(4);
    func_020a9844(5);
    func_020a98a8(2);
}
