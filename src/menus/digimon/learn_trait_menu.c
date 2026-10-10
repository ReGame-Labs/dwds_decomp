#include "menus/digimon/learn_trait_menu.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "menus/digimon/data.h"
#include "menus/digimon/status_screen_open.h"
#include "menus/widgets/skill_displays.h"
#include "menus/widgets/window_anim.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"
#include "title/title_menu.h"

/* Loads the graphics of the menu's two backgrounds, entries 0xF and 4 of
 * data_0213537c (/dat/bg/m_bg02 and md_flame00), and the window frames. */
void loadLearnTraitMenuBgs(struct LearnTraitMenu *menu) {
    const char **files;

    files                             = func_0204871c(0xF);
    menu->graphics->bg[0].paletteFile = loadPaletteFile(&menu->graphics->bg[0].palette, files[0]);
    menu->graphics->bg[0].charFile    = loadCharFile(&menu->graphics->bg[0].chars, files[1]);
    menu->graphics->bg[0].screenFile  = loadScreenFile(&menu->graphics->bg[0].screen, files[2]);

    files                             = func_0204871c(4);
    menu->graphics->bg[1].paletteFile = loadPaletteFile(&menu->graphics->bg[1].palette, files[0]);
    menu->graphics->bg[1].charFile    = loadCharFile(&menu->graphics->bg[1].chars, files[1]);
    menu->graphics->bg[1].screenFile  = loadScreenFile(&menu->graphics->bg[1].screen, files[2]);

    func_020aa340(2, 1);
    func_020aa308(2, 1);
    loadMainWindowFrameInSlot(0, 2);
    loadSubWindowFrameInSlot(1, 2);
}

/* Frees what loadLearnTraitMenuBgs loads. */
void freeLearnTraitMenuBgs(struct LearnTraitMenu *menu) {
    stopSubPaletteEffectsButFades(menu->subPaletteEffect);
    stopMainPaletteEffectsButFades(menu->mainPaletteEffect);
    if (menu->graphics->bg[0].paletteFile != NULL) {
        heapFree(menu->graphics->bg[0].paletteFile);
        menu->graphics->bg[0].paletteFile = NULL;
    }
    if (menu->graphics->bg[0].charFile != NULL) {
        heapFree(menu->graphics->bg[0].charFile);
        menu->graphics->bg[0].charFile = NULL;
    }
    if (menu->graphics->bg[0].screenFile != NULL) {
        heapFree(menu->graphics->bg[0].screenFile);
        menu->graphics->bg[0].screenFile = NULL;
    }
    if (menu->graphics->bg[1].paletteFile != NULL) {
        heapFree(menu->graphics->bg[1].paletteFile);
        menu->graphics->bg[1].paletteFile = NULL;
    }
    if (menu->graphics->bg[1].charFile != NULL) {
        heapFree(menu->graphics->bg[1].charFile);
        menu->graphics->bg[1].charFile = NULL;
    }
    if (menu->graphics->bg[1].screenFile != NULL) {
        heapFree(menu->graphics->bg[1].screenFile);
        menu->graphics->bg[1].screenFile = NULL;
    }
    unloadMainWindowFrame();
    unloadSubWindowFrame();
}

/* Loads the fonts the menu writes with (data_02127184's): font_dg and font00
 * on the main screen, those and font_s and font_s2 on the sub screen. */
void loadLearnTraitMenuFonts(void) {
    func_020a9c40(1, 2, 0xF);
    func_020a9c40(2, 3, 0xF);
    func_020a9ae0(1, 4, 0xF);
    func_020a9ae0(2, 5, 0xF);
    func_020a9ae0(4, 6, 0xF);
    func_020a9ae0(5, 7, 0xF);
}

/* Unloads the fonts of loadLearnTraitMenuFonts. */
void unloadLearnTraitMenuFonts(void) {
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(4);
    func_020a9844(5);
}

/* Clears both screens' backgrounds and sprites and switches their blending
 * off, as main's clearScreens does. */
void func_ov006_0228eda0(void) {
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

/* Closes the buttons and gives back the five colors that show the cursor. */
void func_ov006_0228ea88(struct LearnTraitMenu *menu) {
    func_020846bc(0x37, 5, 0);
    if (menu->buttons == -1) {
        return;
    }
    closeButtonGroup(menu->buttons);
    menu->buttons = -1;
}

/* Leaves the choice for a message: clears windows 3 (but for its first four
 * rows of tiles), 4 and 5, gives back the cursor's color and pauses the
 * buttons. */
void func_ov006_0228e9bc(struct LearnTraitMenu *menu) {
    struct Window *window;

    window = getWindow(menu->windows[3]);
    func_020a8a98(menu->windows[3], 0, 4, window->width, (s16) (window->height - 4), 0);
    redrawWindow(menu->windows[3]);
    window = getWindow(menu->windows[4]);
    func_020a8a98(menu->windows[4], 0, 0, window->width, window->height, 0);
    redrawWindow(menu->windows[4]);
    window = getWindow(menu->windows[5]);
    func_020a8a98(menu->windows[5], 0, 0, window->width, window->height, 0);
    redrawWindow(menu->windows[5]);
    func_020846bc(0x37, 5, 0);
    pauseButtonGroup(menu->buttons);
}

/* Goes back to the choice: shows the trait of the slot the cursor is on, or
 * the one offered for the fifth button, brightens the cursor's color and
 * resumes the buttons. */
void func_ov006_0228e900(struct LearnTraitMenu *menu) {
    s16 slot = menu->list->cursor;

    if (slot < 4) {
        func_02053868(0, menu->digimon->unk22[slot], menu->digimon->unk2C[slot]);
    } else {
        func_02053868(0, menu->id, -1);
    }
    func_020530ec(0, menu->digimon);
    func_ov006_0228e418(&menu->graphics->text, menu->id, menu->windows[5], 1, 1, 0x25C, 2, 0);
    func_020846bc((s16) (menu->list->cursor + 0x37), 1, 8);
    resumeButtonGroup(menu->buttons);
}
