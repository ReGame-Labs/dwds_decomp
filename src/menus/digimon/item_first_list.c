#include "menus/digimon/item_first_list.h"
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

/* Closes list0: its scroll bar and arrows, the light of its rows (colors 0x31
 * to 0x36), the text of window 2 and two parts of window 1, and its buttons. */
void func_ov006_0227f508(struct ItemMenu *menu) {
    struct Window *window;

    if (menu->scrollBar != -1) {
        closeScrollBar(menu->scrollBar);
        menu->scrollBar = -1;
        freeMainSprite(menu->scrollBarSprite);
        menu->scrollBarSprite = -1;
        func_ov006_0227ef34(menu);
    }
    func_020846bc(0x31, 6, 0);
    window = getWindow(menu->windows[2]);
    func_020a8a98(menu->windows[2], 0, 0, window->width, window->height, 0);
    redrawWindow(menu->windows[2]);
    func_020a8a98(menu->windows[1], 3, 1, 9, 2, 0);
    func_020a8a98(menu->windows[1], 1, 7, 13, 8, 0);
    redrawWindow(menu->windows[1]);
    if (menu->list0Buttons != -1) {
        closeButtonGroup(menu->list0Buttons);
        menu->list0Buttons = -1;
    }
}

/* Makes the arrows that scroll list0, and their touch buttons: hidden until
 * their callback shows them. */
void func_ov006_0227ef78(struct ItemMenu *menu) {
    s32 i;
    struct ButtonGroup *group;

    menu->upArrow = createMainSprite(0x3A7, 0x78, 0x20, 0xD, 0);
    addMainSpriteFlags(menu->upArrow, 0x10);
    func_0203e878(menu->upArrow, 0x3F);
    menu->downArrow = createMainSprite(0x3A8, 0x78, 0x88, 0xD, 0);
    addMainSpriteFlags(menu->downArrow, 0x10);
    func_0203e878(menu->downArrow, 0x3F);
    menu->arrowButtons = createButtonGroup(0x30, 0, func_ov006_0227ed84);
    for (i = 0; i < 2; i++) {
        addRectButton(data_ov006_0229efa8[i * 4], data_ov006_0229efa8[i * 4 + 1], data_ov006_0229efa8[i * 4 + 2],
                      data_ov006_0229efa8[i * 4 + 3], 0, menu->arrowButtons);
    }
    group          = findTask(menu->arrowButtons);
    group->work[0] = 32;
    group->work[1] = 32;
}

/* Removes list0's arrows and their buttons. */
void func_ov006_0227ef34(struct ItemMenu *menu) {
    freeMainSprite(menu->upArrow);
    menu->upArrow = -1;
    freeMainSprite(menu->downArrow);
    menu->downArrow = -1;
    if (menu->arrowButtons != -1) {
        closeButtonGroup(menu->arrowButtons);
        menu->arrowButtons = -1;
    }
}

/* The arrows' callback: while one is held, scrolls list0 by an entry after 32
 * frames, then 8 frames sooner each time, down to every 4 frames (the group's
 * work[0] counts the frames, work[1] is the wait). An arrow is hidden while the
 * list can't scroll its way. */
void func_ov006_0227ed84(s16 button, s16 cursor, struct ButtonGroup *group) {
    struct ItemMenu *menu = ITEM_MENU;

    if (func_0204d8fc(data_ov006_0229efa8, 2) == 0) {
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
            if (menu->list0->scroll > 0) {
                group->work[0]++;
                if (group->work[0] >= group->work[1]) {
                    menu->list0->scroll--;
                    setScrollBarPos(menu->scrollBar, menu->list0->scroll);
                    group->work[0] = 0;
                    group->work[1] -= 8;
                    if (group->work[1] < 4) {
                        group->work[1] = 4;
                    }
                }
            }
            break;
        case 1:
            if (menu->list0->scroll < menu->list0->maxScroll) {
                group->work[0]++;
                if (group->work[0] >= group->work[1]) {
                    menu->list0->scroll++;
                    setScrollBarPos(menu->scrollBar, menu->list0->scroll);
                    group->work[0] = 0;
                    group->work[1] -= 8;
                    if (group->work[1] < 4) {
                        group->work[1] = 4;
                    }
                }
            }
            break;
    }
    if (menu->list0->scroll <= 0) {
        addMainSpriteFlags(menu->upArrow, 0x10);
    } else {
        clearMainSpriteFlags(menu->upArrow, 0x10);
    }
    if (menu->list0->scroll >= menu->list0->maxScroll) {
        addMainSpriteFlags(menu->downArrow, 0x10);
    } else {
        clearMainSpriteFlags(menu->downArrow, 0x10);
    }
}
