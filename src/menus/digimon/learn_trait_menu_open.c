#include "menus/digimon/learn_trait_menu_open.h"
#include "battle/characters/chr.h"
#include "battle/characters/chr_system.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/print_text.h"
#include "engine/text/text_banks.h"
#include "engine/text/text_object.h"
#include "engine/ui/buttons.h"
#include "engine/window/window.h"
#include "menus/digimon/data.h"
#include "menus/digimon/learn_trait_menu.h"
#include "menus/widgets/menu_displays.h"

/* The trait learning menu's onEnd: closeLearnTraitMenu frees it instead. */
void onLearnTraitMenuEnd(void) {}

/* Marks both screens' m_win00 window frames as not loaded. */
void func_ov006_022905bc(void) {
    MAIN_WINDOW_FRAME00_SLOT = -1;
    SUB_WINDOW_FRAME00_SLOT  = -1;
}

/* Loads the window frame of /dat/bg/m_win00 (entry 6 of data_0213537c) into
 * the given graphics slot of the main screen, unloading the one loaded
 * before, as main's loadMainWindowFrameInSlot loads m_win (entry 0x60). */
s32 loadMainWindowFrame00InSlot(s8 slot, s32 palette) {
    s32 *files = func_0204871c(6);

    if (MAIN_WINDOW_FRAME00_SLOT != -1) {
        unloadMainWindowFrame00();
    }
    MAIN_WINDOW_FRAME00_SLOT = slot;
    return func_020aa2c0(files, slot, -1, palette);
}

/* The same for the sub screen, as main's loadSubWindowFrameInSlot. */
s32 loadSubWindowFrame00InSlot(s8 slot, s32 palette) {
    s32 *files = func_0204871c(6);

    if (SUB_WINDOW_FRAME00_SLOT != -1) {
        unloadSubWindowFrame00();
    }
    SUB_WINDOW_FRAME00_SLOT = slot;
    return func_020aa29c(files, slot, -1, palette);
}

/* Unloads the main screen's m_win00 window frame, if one is loaded. */
void unloadMainWindowFrame00(void) {
    if (MAIN_WINDOW_FRAME00_SLOT == -1) {
        return;
    }
    func_020a9610(MAIN_WINDOW_FRAME00_SLOT);
    MAIN_WINDOW_FRAME00_SLOT = -1;
}

/* Unloads the sub screen's m_win00 window frame, if one is loaded. */
void unloadSubWindowFrame00(void) {
    if (SUB_WINDOW_FRAME00_SLOT == -1) {
        return;
    }
    func_020a9610(SUB_WINDOW_FRAME00_SLOT);
    SUB_WINDOW_FRAME00_SLOT = -1;
}

/* Sets the text drawing flag of a mode in data_021e33cc: 0x80 for 0 and any
 * other, 0x20 for 1, 0x400 for 2. func_ov006_02290300 clears it. */
void func_ov006_02290354(s32 mode) {
    switch (mode) {
        case 0:
            func_020a5848();
            break;
        case 1:
            func_020a58a8();
            break;
        case 2:
            func_020a5818();
            break;
        default:
            func_020a5848();
            break;
    }
}

/* Clears the flag func_ov006_02290354 sets for the mode. */
void func_ov006_02290300(s32 mode) {
    switch (mode) {
        case 0:
            func_020a5830();
            break;
        case 1:
            func_020a5890();
            break;
        case 2:
            func_020a5800();
            break;
        default:
            func_020a5830();
            break;
    }
}

/* Opens the menu where the Digimon learns trait id in place of one of the
 * four of its unk22, or gives it up. */
void openLearnTraitMenu(struct Digimon *digimon, s16 id) {
    struct LearnTraitMenu *menu;

    func_020a3454(9);
    initSubBattleChrs(0x200);
    menu             = createTask(tickLearnTraitMenu, 0x11A);
    LEARN_TRAIT_MENU = menu;
    menu->task.onEnd = onLearnTraitMenuEnd;
    menu->digimon    = digimon;
    menu->id         = id;
    menu->state      = 0;

    menu->graphics = heapAlloc(sizeof(struct LearnTraitGraphics), 4);
    func_02030f18(menu->graphics, 0, sizeof(struct LearnTraitGraphics));
    menu->list = heapAlloc(sizeof(struct ScrollList), 4);
    CLEAR(menu->list, sizeof(struct ScrollList));

    menu->windows[0] = 0xFF;
    menu->windows[1] = 0xFF;
    menu->windows[2] = 0xFF;
    menu->windows[3] = 0xFF;
    menu->windows[4] = 0xFF;
    menu->windows[5] = 0xFF;
    menu->unk40      = 0;
    loadLearnTraitMenuBgs(menu);
    loadLearnTraitMenuFonts();
}

/* Closes the trait learning menu, once its task is done. */
void closeLearnTraitMenu(struct LearnTraitMenu *menu) {
    closeBackButton();
    func_ov006_0228eb90(menu);
    func_ov006_0228ea88(menu);
    removeAllSubBattleChrs();
    endBattleChrs();
    freeMainSprites();
    freeSubSprites();
    if (menu->windows[0] != 0xFF) {
        closeWindow();
        menu->windows[0] = 0xFF;
    }
    if (menu->windows[1] != 0xFF) {
        closeWindow();
        menu->windows[1] = 0xFF;
    }
    if (menu->windows[3] != 0xFF) {
        closeWindow();
        menu->windows[3] = 0xFF;
    }
    if (menu->windows[4] != 0xFF) {
        closeWindow();
        menu->windows[4] = 0xFF;
    }
    if (menu->windows[5] != 0xFF) {
        closeWindow();
        menu->windows[5] = 0xFF;
    }
    freeLearnTraitMenuBgs(menu);
    unloadLearnTraitMenuFonts();
    heapFree(menu->graphics);
    heapFree(menu->list);
    func_ov006_0228eda0();
    freeTextBank();
}

/* Whether the trait learning menu has closed. */
u8 isLearnTraitMenuClosed(void) {
    return LEARN_TRAIT_MENU == NULL;
}
