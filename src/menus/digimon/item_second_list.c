#include "menus/digimon/item_second_list.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/palette/palette_fade.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "menus/digimon/data.h"
#include "menus/widgets/compare_colors.h"
#include "menus/widgets/scroll_bar.h"

/* Closes list1: its scroll bar and arrows, the light of its rows (colors 0x31
 * to 0x36), the text of windows 1 and 2, and its buttons. */
void func_ov006_0227d344(struct ItemMenu *menu) {
    struct Window *window;

    if (menu->scrollBar != -1) {
        closeScrollBar(menu->scrollBar);
        menu->scrollBar = -1;
        freeMainSprite(menu->scrollBarSprite);
        menu->scrollBarSprite = -1;
        func_ov006_0227cd80(menu);
    }
    func_020846bc(0x31, 6, 0);
    window = getWindow(menu->windows[2]);
    func_020a8a98(menu->windows[2], 0, 0, window->width, window->height, 0);
    redrawWindow(menu->windows[2]);
    window = getWindow(menu->windows[1]);
    func_020a8a98(menu->windows[1], 0, 0, window->width, window->height, 0);
    redrawWindow(menu->windows[1]);
    if (menu->list1Buttons != -1) {
        closeButtonGroup(menu->list1Buttons);
        menu->list1Buttons = -1;
    }
}

/* Makes the arrows that scroll list1, and their touch buttons: hidden until
 * their callback shows them. */
void func_ov006_0227cdc4(struct ItemMenu *menu) {
    s32 i;
    struct ButtonGroup *group;

    menu->upArrow = createMainSprite(0x3A7, 0x78, 0x20, 0xD, 0);
    addMainSpriteFlags(menu->upArrow, 0x10);
    func_0203e878(menu->upArrow, 0x3F);
    menu->downArrow = createMainSprite(0x3A8, 0x78, 0x88, 0xD, 0);
    addMainSpriteFlags(menu->downArrow, 0x10);
    func_0203e878(menu->downArrow, 0x3F);
    menu->arrowButtons = createButtonGroup(0x30, 0, func_ov006_0227cbd0);
    for (i = 0; i < 2; i++) {
        addRectButton(data_ov006_0229ef98[i * 4], data_ov006_0229ef98[i * 4 + 1], data_ov006_0229ef98[i * 4 + 2],
                      data_ov006_0229ef98[i * 4 + 3], 0, menu->arrowButtons);
    }
    group          = findTask(menu->arrowButtons);
    group->work[0] = 32;
    group->work[1] = 32;
}

/* Removes list1's arrows and their buttons. */
void func_ov006_0227cd80(struct ItemMenu *menu) {
    freeMainSprite(menu->upArrow);
    menu->upArrow = -1;
    freeMainSprite(menu->downArrow);
    menu->downArrow = -1;
    if (menu->arrowButtons != -1) {
        closeButtonGroup(menu->arrowButtons);
        menu->arrowButtons = -1;
    }
}

/* The arrows' callback: while one is held, scrolls list1 by an entry after 32
 * frames, then 8 frames sooner each time, down to every 4 frames (the group's
 * work[0] counts the frames, work[1] is the wait). An arrow is hidden while the
 * list can't scroll its way. */
void func_ov006_0227cbd0(s16 button, s16 cursor, struct ButtonGroup *group) {
    struct ItemMenu *menu = ITEM_MENU;

    if (func_0204d8fc(data_ov006_0229ef98, 2) == 0) {
        return;
    }
    getTaskId(group);
    getTouchX();
    getTouchY();
    if (button == -1) {
        group->work[0] = 32;
        group->work[1] = 32;
    }
    switch (button) {
        case 0:
            if (menu->list1->scroll > 0) {
                group->work[0]++;
                if (group->work[0] >= group->work[1]) {
                    menu->list1->scroll--;
                    setScrollBarPos(menu->scrollBar, menu->list1->scroll);
                    group->work[0] = 0;
                    group->work[1] -= 8;
                    if (group->work[1] < 4) {
                        group->work[1] = 4;
                    }
                }
            }
            break;
        case 1:
            if (menu->list1->scroll < menu->list1->maxScroll) {
                group->work[0]++;
                if (group->work[0] >= group->work[1]) {
                    menu->list1->scroll++;
                    setScrollBarPos(menu->scrollBar, menu->list1->scroll);
                    group->work[0] = 0;
                    group->work[1] -= 8;
                    if (group->work[1] < 4) {
                        group->work[1] = 4;
                    }
                }
            }
            break;
    }
    if (menu->list1->scroll <= 0) {
        addMainSpriteFlags(menu->upArrow, 0x10);
    } else {
        clearMainSpriteFlags(menu->upArrow, 0x10);
    }
    if (menu->list1->scroll >= menu->list1->maxScroll) {
        addMainSpriteFlags(menu->downArrow, 0x10);
    } else {
        clearMainSpriteFlags(menu->downArrow, 0x10);
    }
}
