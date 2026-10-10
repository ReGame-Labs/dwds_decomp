#include "eggs/egg_list.h"
#include "eggs/egg_panel.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "engine/ui/digimon_list.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "field/actors/actor_files.h"
#include "nitro/pad.h"

#define UI_FLAG_EGG_LIST 0xD
#define RESULT_CANCEL -4
#define SPRITE_UP 0
#define SPRITE_DOWN 1
#define SPRITE_CANCEL 2
#define PAGE 2

/* Moves the list's cursor by the keys and the window's sprites, or to row
 * when it is not -1; B or the cancel sprite cancels the list. */
void func_020975e4(s8 row) {
    u16 held;
    u16 pressed;
    struct EggList *list;
    struct Window *window;
    s8 oldTop;
    s8 oldCursor;

    held    = getPadPressed();
    pressed = getPadRepeat();
    getPadHeld();
    list      = findTask(data_021da404);
    window    = getWindow(list->window);
    oldTop    = list->top;
    oldCursor = list->cursor;
    if ((held & PAD_BUTTON_B) || isSpriteTapped(window->sprites[SPRITE_CANCEL]) != 0) {
        list->result = RESULT_CANCEL;
        return;
    }
    if (pressed & PAD_KEY_UP) {
        list->cursor--;
        if (list->cursor < 0) {
            list->cursor = 0;
            list->top--;
            if (list->top < 0) {
                list->top = 0;
            }
        }
    } else if (pressed & PAD_KEY_LEFT) {
        list->top -= PAGE;
        if (list->top < 0) {
            list->top = 0;
        }
    } else if (pressed & PAD_KEY_DOWN) {
        list->cursor++;
        if (list->cursor > EGG_LIST_ROWS - 1) {
            list->cursor = EGG_LIST_ROWS - 1;
            list->top++;
            if (list->top > EGG_LIST_MAX_TOP) {
                list->top = EGG_LIST_MAX_TOP;
            }
        }
    } else if (pressed & PAD_KEY_RIGHT) {
        list->top += PAGE;
        if (list->top > EGG_LIST_MAX_TOP) {
            list->top = EGG_LIST_MAX_TOP;
        }
    } else if (isSpriteTapped(window->sprites[SPRITE_UP]) != 0) {
        list->top--;
        if (list->top < 0) {
            list->top = 0;
        }
    } else if (isSpriteTapped(window->sprites[SPRITE_DOWN]) != 0) {
        list->top++;
        if (list->top > EGG_LIST_MAX_TOP) {
            list->top = EGG_LIST_MAX_TOP;
        }
    } else if (row != -1) {
        list->cursor = row;
    }
    if (list->top != oldTop) {
        func_02096ef4(list->top, list->window, list->rowWindows, list->eggs, list->rowSprites);
    }
    if (list->cursor != oldCursor) {
        func_02096e34(list->cursor, list->rowWindows, list->gfxSlot);
    }
    if (list->top != oldTop || list->cursor != oldCursor) {
        showEggOnPanel(list->eggs[list->top + list->cursor]);
    }
}

/* Returns whether the list of DigiEggs is open. */
BOOL isEggListOpen(void) {
    if (getUiFlag(UI_FLAG_EGG_LIST) != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Closes the list of DigiEggs. */
void closeEggList(void) {
    struct EggList *list;
    s32 i;
    s32 j;

    if (getUiFlag(UI_FLAG_EGG_LIST) == 0) {
        return;
    }
    list = findTask(data_021da404);
    closeButtonGroup(list->buttons);
    for (i = 0; i < EGG_LIST_ROWS; i++) {
        for (j = 0; j < 3; j++) {
            if (list->rowSprites[i][j] != -1) {
                func_020c6fb8(list->rowSprites[i][j]);
            }
        }
    }
    closeWindow(list->window);
    closeWindow(list->rowWindows[0]);
    closeWindow(list->rowWindows[1]);
    closeWindow(list->rowWindows[2]);
    releaseGfxSlot(list->gfxSlot);
    func_020a9844(6);
    stopSubPaletteEffects(list->unk62);
    endTask(list);
    data_021da404 = 0;
    clearUiFlag(UI_FLAG_EGG_LIST);
}
