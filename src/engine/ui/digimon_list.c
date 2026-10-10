#include "engine/ui/digimon_list.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/window_text.h"
#include "engine/ui/buttons.h"
#include "engine/ui/gauge.h"
#include "engine/window/message_box.h"
#include "engine/window/popup.h"
#include "engine/window/window.h"
#include "farm/farm_groups.h"
#include "farm/panel_digimon.h"
#include "farm/stats_window.h"
#include "nitro/gx.h"
#include "nitro/pad.h"

/* Empty; closeDigimonList calls it as it closes the list. */
void func_020afc1c(void) {}

/* Moves one frame along the curve; once there, puts it at the end and returns
 * FALSE. */
BOOL stepCurve(struct Curve *curve) {
    if (curve->frame >= curve->frames) {
        curve->x = curve->endX;
        curve->y = curve->endY;
        return FALSE;
    }
    curve->velX += curve->accelX;
    curve->x = (curve->velX * curve->frame + curve->startX) / 4096;
    curve->velY += curve->accelY;
    curve->y = (curve->velY * curve->frame + curve->startY) / 4096;
    curve->frame++;
    return TRUE;
}

/* Whether the touch screen was tapped on the sprite, of the engine that draws
 * the touch screen: the sub one when the main one is on top. */
BOOL isSpriteTapped(s32 sprite) {
    enum GXDispSelect mode = GX_GetDispSelect();
    s16 x;
    s16 y;

    if (getTouchTap() == 0) {
        return FALSE;
    }
    x = getTouchX();
    y = getTouchY();
    if (mode == GX_DISP_SELECT_MAIN_SUB) {
        return isPointOnSubSprite(sprite, x, y);
    }
    return isPointOnMainSprite(sprite, x, y);
}

/* Whether the touch screen was tapped inside the rectangle. */
BOOL isRectTapped(s16 x, s16 y, s16 width, s16 height) {
    s16 touchX;
    s16 touchY;

    if (getTouchTap() == 0) {
        return FALSE;
    }
    touchX = getTouchX();
    touchY = getTouchY();
    if (touchX >= x && touchX < x + width && touchY >= y && touchY < y + height) {
        return TRUE;
    }
    return FALSE;
}

/* Tests a tap on the window, but drops the result. */
void func_020b0a78(u32 index) {
    struct Window *window = getWindow(index);

    isRectTapped(window->x * 8, window->y * 8, window->width * 8, window->height * 8);
}

/* isSpriteTapped for the touch screen's fastRepeat. */
BOOL isSpriteFastRepeatTapped(s32 sprite) {
    enum GXDispSelect mode = GX_GetDispSelect();
    s16 x;
    s16 y;

    if (getTouchFastRepeat() == 0) {
        return FALSE;
    }
    x = getTouchX();
    y = getTouchY();
    if (mode == GX_DISP_SELECT_MAIN_SUB) {
        return isPointOnSubSprite(sprite, x, y);
    }
    return isPointOnMainSprite(sprite, x, y);
}

/* isSpriteTapped for the touch screen's repeat. */
BOOL isSpriteRepeatTapped(s32 sprite) {
    enum GXDispSelect mode = GX_GetDispSelect();
    s16 x;
    s16 y;

    if (getTouchRepeat() == 0) {
        return FALSE;
    }
    x = getTouchX();
    y = getTouchY();
    if (mode == GX_DISP_SELECT_MAIN_SUB) {
        return isPointOnSubSprite(sprite, x, y);
    }
    return isPointOnMainSprite(sprite, x, y);
}

/* Whether the point is on the main screen sprite. */
BOOL isPointOnMainSprite(s32 sprite, s32 x, s32 y) {
    return isPointOnSprite(getMainSprite(sprite), x, y);
}

/* Whether the point is on the sub screen sprite. */
BOOL isPointOnSubSprite(s32 sprite, s32 x, s32 y) {
    return isPointOnSprite(getSubSprite(sprite), x, y);
}

/* Whether the point is on one of the OAM entries of the sprite's cell. */
BOOL isPointOnSprite(struct Sprite *sprite, s32 px, s32 py) {
    struct CellOamAttr *oam;
    struct CellData *cell;
    u16 attr0;
    s32 x;
    s32 y;
    s32 left;
    s32 top;
    u16 attr1;
    s32 shape;
    s32 size;
    u16 width;
    u16 height;
    s32 i;

    if (sprite == NULL) {
        return FALSE;
    }
    cell = sprite->cellAnim->cell;
    for (i = 0; i < cell->numOAMAttrs; i++) {
        oam   = &cell->oamAttrs[i];
        attr0 = oam->attr0;
        attr1 = oam->attr1;
        y     = attr0 & 0xFF;
        if (y & 0xFF80) {
            y |= ~0x7F;
        }
        top = y + sprite->y;
        x   = attr1 & 0x1FF;
        if (x & 0xFF00) {
            x |= ~0xFF;
        }
        left   = x + sprite->x;
        shape  = attr0 >> 14;
        size   = attr1 >> 14;
        width  = data_021271f4[shape][size];
        height = data_0212720c[shape][size];
        if (px >= left && py >= top && px < left + width && py < top + height) {
            break;
        }
    }
    return i != cell->numOAMAttrs;
}

/* Hands the Digimon's id to whichever of UI kinds 0 and 7 is open. */
void func_020afbdc(s32 id) {
    if (getUiFlag(0) != 0) {
        func_ov005_0227fe6c(id);
        return;
    }
    if (getUiFlag(7) != 0) {
        showStatsCompare(id);
    }
}

/* Makes the colors of the cursor's row blink in both palettes after the
 * list's, stopping the old blink first. */
void blinkDigimonListCursor(struct DigimonList *list) {
    if (list->cursorBlink[0] != -1) {
        restoreSubPalette((s16) ((list->palette + 1) * 16), 16);
        restoreSubPalette((s16) ((list->palette + 2) * 16), 16);
        stopSubPaletteEffects(list->cursorBlink[0]);
        stopSubPaletteEffects(list->cursorBlink[1]);
        list->cursorBlink[0] = -1;
        list->cursorBlink[1] = -1;
    }
    if (list->count == 0) {
        return;
    }
    list->cursorBlink[0] = func_020839c8((s16) (list->cursor + (list->palette + 1) * 16 + 10), 1, 0x7FFF, 0x50, 1, 2, 10000);
    list->cursorBlink[1] = func_020839c8((s16) (list->cursor + (list->palette + 2) * 16 + 10), 1, 0x7FFF, 0x50, 1, 2, 10000);
}

/* Goes on to the next of the 4 orders. */
void nextDigimonListSort(struct DigimonList *list) {
    if (list == NULL) {
        return;
    }
    list->sort++;
    if (list->sort > 3) {
        list->sort = 0;
    }
}

/* Makes a sprite of the sub screen that plays anim for ever. */
u32 createLoopingSubSprite(s32 kind, s32 x, s32 y, s32 unk3, u16 unk4, s16 unk1D, u16 unk1C, s16 anim) {
    u32 sprite;

    if (unk1D < 0) {
        unk1D = 0;
    }
    sprite = createMainSprite(kind, x, y, unk3, unk4);
    setMainSpriteBgPriority(sprite, unk1C);
    func_0203e878(sprite, (u16) unk1D);
    setMainSpriteAnim(sprite, anim, -1);
    return sprite;
}

/* createLoopingSubSprite for the main screen. */
s32 createLoopingMainSprite(s32 kind, s32 x, s32 y, s32 unk3, u16 unk4, s16 unk1D, u16 unk1C, s16 anim) {
    s32 sprite;

    if (unk1D < 0) {
        unk1D = 0;
    }
    sprite = createSubSprite(kind, x, y, unk3, unk4);
    setSubSpriteBgPriority(sprite, unk1C);
    func_0203e848(sprite, (u16) unk1D);
    setSubSpriteAnim(sprite, anim, -1);
    return sprite;
}

/* The row of the cursor, or -1. */
s16 getDigimonListCursor(void) {
    struct DigimonList *list;

    if (getUiFlag(2) == 0) {
        return -1;
    }
    list = findTask(DIGIMON_LIST_TASK_ID);
    if (list == NULL || list->count == 0) {
        return -1;
    }
    return list->cursor;
}

/* The index of ids in the list's first row, or -1. */
s16 getDigimonListScroll(void) {
    struct DigimonList *list;

    if (getUiFlag(2) == 0) {
        return -1;
    }
    list = findTask(DIGIMON_LIST_TASK_ID);
    if (list == NULL || list->count == 0) {
        return -1;
    }
    return list->scroll;
}

/* The id of the Digimon chosen, 0 for none, or -1 when cancelled. */
s32 getChosenDigimon(void) {
    struct DigimonList *list;

    if (getUiFlag(2) == 0) {
        return -1;
    }
    list = findTask(DIGIMON_LIST_TASK_ID);
    if (list->result == MENU_RESULT_CANCELLED) {
        return -1;
    }
    return list->chosen;
}

/* The list's order, or -1. */
s16 getDigimonListSort(void) {
    if (getUiFlag(2) == 0) {
        return -1;
    }
    return ((struct DigimonList *) findTask(DIGIMON_LIST_TASK_ID))->sort;
}

/* The list's tabPages entry for its page, plus one, or -1 when no list is
 * open. */
s16 func_020adb8c(void) {
    struct DigimonList *list;

    if (getUiFlag(2) == 0) {
        return -1;
    }
    list = findTask(DIGIMON_LIST_TASK_ID);
    return list->tabPages[list->page] + 1;
}

/* Shows another page of the list from its top, switching off the buttons of
 * the rows left empty. */
void setDigimonListPage(s16 page) {
    struct DigimonList *list;
    struct Window *window;
    s32 i;

    if (getUiFlag(2) == 0) {
        return;
    }
    list       = findTask(DIGIMON_LIST_TASK_ID);
    window     = getWindow(list->window);
    list->page = page;
    if (list->page == 0) {
        list->maxCount = 40;
    } else {
        list->maxCount = 8;
    }
    list->count      = getDigimonListIds(list->page, list->ids);
    list->scroll     = 0;
    list->cursor     = 0;
    list->scrollBarY = window->y * 8;
    list->flags |= 0x2000;
    for (i = 0; i < 6 && i < list->count; i++) {
        enableButton(list->rowButtons[i], data_021e5cac);
    }
    for (; i < 6; i++) {
        disableButton(list->rowButtons[i], data_021e5cac);
    }
    refreshDigimonList();
}

/* Lets the list be used again, to choose anew. */
void restartDigimonList(void) {
    struct DigimonList *list;

    if (getUiFlag(2) == 0) {
        return;
    }
    list = findTask(DIGIMON_LIST_TASK_ID);
    resumeButtonGroup(data_021e5cac);
    list->state  = 300;
    list->chosen = 0;
    list->result = MENU_RESULT_CHOOSING;
}

/* Opens the menu of MENU_LAYOUTS[index]. */
void openMenu(s32 index, s32 cursor, s32 palette, s32 unk3D, u16 flags) {
    struct MenuLayout *layout = &MENU_LAYOUTS[index];

    startMenuTask(layout->unk4, layout->unk5, index, cursor, palette, unk3D, flags);
}

/* The menu's button group callback: a choice made with A or a tap, the last
 * one or B to cancel, and the cursor sprite put on the cursor's row. */
void updateMenuChoice(s16 touched, s16 cursor, struct ButtonGroup *group) {
    u16 pressed;
    struct Menu *menu;
    struct Window *window;
    s32 choice;

    pressed = getPadPressed();
    menu    = findTask(MENU_TASK_ID);
    if (menu == NULL) {
        return;
    }
    window = getWindow(menu->window);
    choice = getChosenButton(group->task.id);
    if (choice >= 0) {
        if (choice == menu->count - 1) {
            playSound(3);
            menu->result = MENU_RESULT_CANCELLED;
        } else {
            playSound(1);
            menu->result = choice;
        }
    } else if (pressed & PAD_BUTTON_B) {
        playSound(3);
        menu->result = MENU_RESULT_CANCELLED;
    }
    menu->cursor = cursor;
    setSubSpritePos(window->sprites[0], (window->x + 2) * 8, (window->y + 1 + menu->cursor * 2) * 8);
}

/* The choice made in the menu, or a MenuResult; closed counts as cancelled. */
s16 getMenuResult(void) {
    if (getUiFlag(3) == 0) {
        return MENU_RESULT_CANCELLED;
    }
    return ((struct Menu *) findTask(MENU_TASK_ID))->result;
}

/* Shows the choices of MENU_LAYOUTS[index] in the open menu, with the
 * cursor on the given one, unless it is -1. */
void setMenuChoices(s32 index, s32 cursor) {
    struct Menu *menu;
    struct Window *window;
    struct MenuLayout *layout;
    s32 last;

    if (getUiFlag(3) == 0) {
        return;
    }
    menu         = findTask(MENU_TASK_ID);
    window       = getWindow(menu->window);
    menu->result = MENU_RESULT_CHOOSING;
    layout       = &MENU_LAYOUTS[index];
    menu->count  = layout->count;
    if (cursor > -1) {
        menu->cursor = cursor;
    }
    last = menu->count - 1;
    if (cursor > last) {
        menu->cursor = last;
    }
    func_020a68cc(menu->window, 2, 1, (s16) (window->width - 3), (s16) (window->height - 2), getFarmText(layout->text), 0,
                  (u8) menu->palette, 3, 2, 0);
}

/* Closes the menu. */
void closeMenu(void) {
    struct Menu *menu;

    if (getUiFlag(3) == 0) {
        return;
    }
    menu = findTask(MENU_TASK_ID);
    closeButtonGroup(menu->buttons);
    closeWindowAndClear(&menu->window);
    func_020a9610((s8) menu->gfxSlot);
    func_020a9844(2);
    endTask(menu);
    clearUiFlag(3);
}

/* openFarmMessage with no cursor, and flag 0x100. */
void func_020ad1bc(u16 textId, s8 palette, s8 unk3D, u16 flags) {
    openFarmMessage(textId, 0, 0, palette, unk3D, (u16) (flags | 0x100));
}

/* Opens a message window with the text, or shows it in the one open. */
void openMessage(void *text, s16 cursor, s8 palette, s8 unk3D, u16 flags) {
    struct Menu *menu;

    if (getUiFlag(1) != 0) {
        func_020ac2ec(text, cursor, flags);
        return;
    }
    menu          = createTask(func_020ac884, 0x10A);
    menu->state   = 0;
    menu->wait    = 0;
    menu->unk20   = 0xFFFF;
    menu->unk24   = 0xFFFF;
    menu->text    = text;
    menu->cursor  = cursor;
    menu->palette = palette;
    menu->unk3D   = unk3D;
    menu->flags   = flags;
    menu->result  = MENU_RESULT_CHOOSING;
    menu->buttons = 0xFFFF;
    MENU_TASK_ID  = getTaskId(menu);
    setUiFlag(1);
}
