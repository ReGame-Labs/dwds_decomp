#include "menus/digimon/item_menu_open.h"
#include "battle/battle_mode/battle_bg.h"
#include "battle/characters/fade_sprite_slot.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/text_object.h"
#include "engine/window/window.h"
#include "menus/digimon/data.h"
#include "menus/digimon/item_menu.h"
#include "menus/digimon/item_menu_choices.h"
#include "menus/widgets/window_anim.h"

/* Draws, on background 3, the icons of 6 by 8 tiles whose flag is set and
 * clears the others: five of them in mode 0, else only flag1 to flag3 at the
 * three places after those five. The same as func_ov006_0227d600, for the
 * Digimon menu. */
void func_ov006_02281dd8(u8 flag0, u8 flag1, u8 flag2, u8 flag3, u8 flag4, u8 mode) {
    struct DigimonMenu *menu = findTask(DIGIMON_MENU_TASK_ID);
    u8 flags[5]              = {flag0, flag1, flag2, flag3, flag4};
    struct ScreenCopy copy   = {0};
    struct ScreenData *screen;
    s32 i;

    screen         = menu->work->bg[3].screen;
    copy.bg        = 3;
    copy.unk2      = 0x180;
    copy.unk4      = 6;
    copy.srcWidth  = 32;
    copy.srcHeight = 32;
    if (mode == 0) {
        for (i = 0; i < 5; i++) {
            copy.srcX   = 0;
            copy.x      = data_ov006_0229f0d8[i * 2];
            copy.srcY   = 0;
            copy.width  = 6;
            copy.height = 8;
            copy.y      = data_ov006_0229f0d8[i * 2 + 1];
            if (flags[i] != 0) {
                copy.src = screen->data;
            } else {
                copy.src = NULL;
            }
            copyMainBgScreenAndFlush((u8 *) &copy);
        }
        return;
    }
    for (i = 1; i < 4; i++) {
        copy.srcX   = 0;
        copy.x      = data_ov006_0229f0d8[(i - 1) * 2 + 10];
        copy.srcY   = 0;
        copy.width  = 6;
        copy.height = 8;
        copy.y      = data_ov006_0229f0d8[(i - 1) * 2 + 11];
        if (flags[i] != 0) {
            copy.src = screen->data;
        } else {
            copy.src = NULL;
        }
        copyMainBgScreenAndFlush((u8 *) &copy);
    }
}

/* Makes the Digimon menu redraw what func_ov006_02281cd8 draws, if it is
 * open. */
void func_ov006_02281c98(void) {
    struct DigimonMenu *menu;

    if (DIGIMON_MENU == NULL) {
        return;
    }
    menu         = findTask(DIGIMON_MENU_TASK_ID);
    menu->redraw = TRUE;
}

/* Hides what func_ov006_02281cd8 draws, if the Digimon menu is open. */
void func_ov006_02281c58(void) {
    struct DigimonMenu *menu;

    if (DIGIMON_MENU == NULL) {
        return;
    }
    menu         = findTask(DIGIMON_MENU_TASK_ID);
    menu->hidden = TRUE;
}

/* Shows again what func_ov006_02281cd8 draws, if the Digimon menu is open. */
void func_ov006_02281c18(void) {
    struct DigimonMenu *menu;

    if (DIGIMON_MENU == NULL) {
        return;
    }
    menu         = findTask(DIGIMON_MENU_TASK_ID);
    menu->hidden = FALSE;
}

/* Leaves the item menu: frees its text, its fonts, every sprite, its
 * backgrounds, its windows and their frames (/dat/bg/m_win_2), and stops the
 * main screen's background effects. */
void func_ov006_02281b38(struct ItemMenu *menu) {
    if (menu->graphics->text.width != 0 && menu->graphics->text.height != 0) {
        freeWindowImage(&menu->graphics->text);
        func_02030f18(&menu->graphics->text, 0, sizeof(menu->graphics->text));
    }
    unloadItemMenuFonts();
    freeMainSprites();
    freeSubSprites();
    freeItemMenuBgs(menu);
    func_ov006_0227fd6c();
    if (menu->windows[0] != 0xFF) {
        closeWindow(menu->windows[0]);
        menu->windows[0] = 0xFF;
    }
    if (menu->windows[1] != 0xFF) {
        closeWindow(menu->windows[1]);
        menu->windows[1] = 0xFF;
    }
    if (menu->windows[2] != 0xFF) {
        closeWindow(menu->windows[2]);
        menu->windows[2] = 0xFF;
    }
    if (menu->windows[3] != 0xFF) {
        closeWindow(menu->windows[3]);
        menu->windows[3] = 0xFF;
    }
    if (menu->windows[4] != 0xFF) {
        closeWindow(menu->windows[4]);
        menu->windows[4] = 0xFF;
    }
    unloadMainWindowFrame();
    unloadSubWindowFrame();
    stopMainBgEffectTask();
}

/* Whether the item menu is gone: its task clears ITEM_MENU when it
 * ends (onItemMenuEnd). */
u8 isItemMenuClosed(void) {
    return ITEM_MENU == NULL;
}

/* The item menu task's destructor. */
void onItemMenuEnd(void) {
    struct ItemMenu *menu = (struct ItemMenu *) getCurrentTask();

    func_ov002_0224b800();
    heapFree(menu->graphics);
    heapFree(menu->list0);
    heapFree(menu->list1);
    heapFree(menu->popup);
    heapFree(menu->unk38);
    ITEM_MENU = NULL;
}
