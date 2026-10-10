#include "menus/digimon/digivolve_screen_open.h"
#include "engine/bg/bg_affine.h"
#include "engine/bg/bg_layers.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/ui/buttons.h"
#include "engine/window/window.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_tasks.h"
#include "menus/digimon/data.h"
#include "menus/digimon/digivolve_texts.h"
#include "menus/digimon/digivolve_tree.h"
#include "menus/digimon/learn_trait_menu_open.h"
#include "menus/widgets/menu_displays.h"
#include "nitro/g2.h"
#include "nitro/gx.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"
#include "title/title_menu.h"

/* The digivolution screen's onEnd: closeDigivolveScreen frees it instead. */
void onDigivolveScreenEnd(void) {}

/* Tears the digivolution screen down. Its four blocks are freed without
 * clearing the fields: the task ends with them. */
void closeDigivolveScreen(struct DigivolveScreen *screen) {
    void *block;

    closeBackButton();
    func_ov006_02291d78(screen);
    func_ov006_022938f0(screen);
    freeMainSprites();
    freeSubSprites();
    deleteMainActors();
    deleteSubActors();
    endMainActorTask();
    endSubActorTask();
    freeDigivolveScreenBgs(screen);
    unloadDigivolveScreenFonts();
    if (screen->treeButtons != -1) {
        closeButtonGroup(screen->treeButtons);
        screen->treeButtons = -1;
    }
    if (screen->menuButtons != -1) {
        closeButtonGroup(screen->menuButtons);
        screen->menuButtons = -1;
    }
    if (screen->statusWindow != 0xFF) {
        closeWindow(screen->statusWindow);
        screen->statusWindow = 0xFF;
    }
    if (screen->previewWindow != 0xFF) {
        closeWindow(screen->previewWindow);
        screen->previewWindow = 0xFF;
    }
    if (screen->unk56 != 0xFF) {
        closeWindow(screen->unk56);
        screen->unk56 = 0xFF;
    }
    if (screen->menuWindow != 0xFF) {
        closeWindow(screen->menuWindow);
        screen->menuWindow = 0xFF;
    }
    if (screen->unk58 != 0xFF) {
        closeWindow(screen->unk58);
        screen->unk58 = 0xFF;
    }
    block = screen->work;
    heapFree(block);
    block = screen->scroll;
    heapFree(block);
    block = screen->tree;
    heapFree(block);
    block = screen->menu;
    heapFree(block);
    func_ov006_02296e1c();
    freeTextBank();
}

/* The lighter teardown of closeDigivolveScreen, which keeps the tree. */
void func_ov006_022974fc(struct DigivolveScreen *screen) {
    closeBackButton();
    freeMainSprites();
    deleteMainActors();
    func_ov006_02296fbc(screen);
    if (screen->treeButtons != -1) {
        closeButtonGroup(screen->treeButtons);
        screen->treeButtons = -1;
    }
    if (screen->menuButtons != -1) {
        closeButtonGroup(screen->menuButtons);
        screen->menuButtons = -1;
    }
    if (screen->menuWindow != 0xFF) {
        closeWindow(screen->menuWindow);
        screen->menuWindow = 0xFF;
    }
    if (screen->unk58 != 0xFF) {
        closeWindow(screen->unk58);
        screen->unk58 = 0xFF;
    }
    func_ov006_02296dbc();
    freeTextBank();
}

/* Whether the digivolution screen has ended. */
u8 isDigivolveScreenClosed(void) {
    return DIGIVOLVE_SCREEN == NULL;
}

/* Loads the graphics of the screen's three backgrounds, entries 3, 3 and 4 of
 * data_0213537c (/dat/bg/m_bg01 twice and md_flame00), and the m_win00 window
 * frames. */
void loadDigivolveScreenBgs(struct DigivolveScreen *screen) {
    const char **files;

    files                           = func_0204871c(3);
    screen->work->bg[0].paletteFile = loadPaletteFile(&screen->work->bg[0].palette, files[0]);
    screen->work->bg[0].charFile    = loadCharFile(&screen->work->bg[0].chars, files[1]);
    screen->work->bg[0].screenFile  = loadScreenFile(&screen->work->bg[0].screen, files[2]);
    screen->work->bg[1].paletteFile = loadPaletteFile(&screen->work->bg[1].palette, files[0]);
    screen->work->bg[1].charFile    = loadCharFile(&screen->work->bg[1].chars, files[1]);
    screen->work->bg[1].screenFile  = loadScreenFile(&screen->work->bg[1].screen, files[2]);
    files                           = func_0204871c(4);
    screen->work->bg[2].paletteFile = loadPaletteFile(&screen->work->bg[2].palette, files[0]);
    screen->work->bg[2].charFile    = loadCharFile(&screen->work->bg[2].chars, files[1]);
    screen->work->bg[2].screenFile  = loadScreenFile(&screen->work->bg[2].screen, files[2]);
    func_020aa308(0, 1);
    func_020aa340(0, 1);
    loadSubWindowFrame00InSlot(1, 2);
    loadMainWindowFrame00InSlot(0, 2);
}

/* Stops the screen's palette effects, frees the backgrounds' graphics and the
 * window frames, and puts the main screen back on the top LCD. */
void freeDigivolveScreenBgs(struct DigivolveScreen *screen) {
    void *file;

    if (screen->subPaletteEffect != -1) {
        stopSubPaletteEffectsButFades(screen->subPaletteEffect);
    }
    if (screen->mainPaletteEffect != -1) {
        stopMainPaletteEffectsButFades(screen->mainPaletteEffect);
    }
    screen->subPaletteEffect  = -1;
    screen->mainPaletteEffect = -1;
    file                      = screen->work->bg[0].paletteFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[0].paletteFile = NULL;
    }
    file = screen->work->bg[0].charFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[0].charFile = NULL;
    }
    file = screen->work->bg[0].screenFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[0].screenFile = NULL;
    }
    file = screen->work->bg[1].paletteFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[1].paletteFile = NULL;
    }
    file = screen->work->bg[1].charFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[1].charFile = NULL;
    }
    file = screen->work->bg[1].screenFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[1].screenFile = NULL;
    }
    file = screen->work->bg[2].paletteFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[2].paletteFile = NULL;
    }
    file = screen->work->bg[2].charFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[2].charFile = NULL;
    }
    file = screen->work->bg[2].screenFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[2].screenFile = NULL;
    }
    unloadSubWindowFrame00();
    unloadMainWindowFrame00();
    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
}

/* The part of freeDigivolveScreenBgs that func_ov006_022974fc needs: the main
 * screen's palette effect, backgrounds 0 and 2 and the main window frame. */
void func_ov006_02296fbc(struct DigivolveScreen *screen) {
    void *file;

    if (screen->mainPaletteEffect != -1) {
        stopMainPaletteEffectsButFades(screen->mainPaletteEffect);
    }
    screen->mainPaletteEffect = -1;
    file                      = screen->work->bg[0].paletteFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[0].paletteFile = NULL;
    }
    file = screen->work->bg[0].charFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[0].charFile = NULL;
    }
    file = screen->work->bg[0].screenFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[0].screenFile = NULL;
    }
    file = screen->work->bg[2].paletteFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[2].paletteFile = NULL;
    }
    file = screen->work->bg[2].charFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[2].charFile = NULL;
    }
    file = screen->work->bg[2].screenFile;
    if (file != NULL) {
        heapFree(file);
        screen->work->bg[2].screenFile = NULL;
    }
    unloadMainWindowFrame00();
}

/* Loads the fonts the screen writes with (data_02127184's): font_dg, font00,
 * font_dg with palette 24 and font_b01 on the main screen, font_dg, font00,
 * font_s2, font_n and font_s on the sub screen. */
void loadDigivolveScreenFonts(void) {
    func_020a9c40(1, 2, 15);
    func_020a9c40(2, 3, 15);
    func_020a9c40(1, 9, 24);
    func_020a9c40(6, 10, 25);
    func_020a9ae0(1, 4, 15);
    func_020a9ae0(2, 5, 15);
    func_020a9ae0(5, 6, 15);
    func_020a9ae0(3, 7, 15);
    func_020a9ae0(4, 8, 15);
}

/* Unloads the fonts of loadDigivolveScreenFonts. */
void unloadDigivolveScreenFonts(void) {
    func_020a98a8(2);
    func_020a98a8(1);
    func_020a98a8(6);
    func_020a9844(1);
    func_020a9844(5);
    func_020a9844(2);
    func_020a9844(3);
    func_020a9844(4);
}

/* Clears both screens' backgrounds and sprites and switches their blending
 * off, as clearScreens does with the blending in another order. */
void func_ov006_02296e1c(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    G2_BlendNone();
    G2S_BlendNone();
}

/* The main screen's half of func_ov006_02296e1c. */
void func_ov006_02296dbc(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    G2_BlendNone();
}

/* Puts the backgrounds' graphics on the screens, starts a palette effect on
 * each screen and sets every background's offset to 0. */
void func_ov006_02296c3c(struct DigivolveScreen *screen) {
    func_0204252c(&screen->work->bg[0], 3, 0, 0, 0, 0, 0, 32, 32, 32, 32);
    screen->mainPaletteEffect = func_02083ea8(6, 10, 4, 1, 10000);
    func_020423f0(&screen->work->bg[0], 3, 0, 0, 0, 0, 0, 32, 32, 32, 32);
    screen->subPaletteEffect = func_02083e78(6, 10, 4, 1, 10000);
    func_020422ac(&screen->work->bg[2], 0, 5, 0, 0, 0, 0, 32, 32, 32, 32, 0x380);
    setMainBgOffset(0, 0, 0);
    setMainBgOffset(1, 0, 0);
    setMainBgOffset(2, 0, 0);
    setMainBgOffset(3, 0, 0);
    setSubBgOffset(0, 0, 0);
    setSubBgOffset(1, 0, 0);
    setSubBgOffset(2, 0, 0);
    setSubBgOffset(3, 0, 0);
}
