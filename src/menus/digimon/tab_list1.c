#include "menus/digimon/tab_list1.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/sprite/sprite_create.h"
#include "engine/ui/buttons.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "menus/digimon/data.h"
#include "menus/widgets/scroll_bar.h"
#include "menus/widgets/text_list.h"

/* Closes the list of the first tab: its rows' sprites, the scroll bar, the
 * buttons, and clears its window. */
void closeFirstTabList(struct DigimonMenu *menu) {
    s32 i;
    struct Window *window;

    for (i = 0; i < 6; i++) {
        if (menu->work->rowSprites[i] != -1) {
            freeMainSprite(menu->work->rowSprites[i]);
            menu->work->rowSprites[i] = -1;
        }
    }
    if (menu->scrollBar != -1) {
        closeScrollBar(menu->scrollBar);
        menu->scrollBar = -1;
        freeMainSprite(menu->work->scrollBarSprite);
        menu->work->scrollBarSprite = -1;
    }
    closeTextList(menu->unk70);
    menu->unk70 = -1;
    if (menu->list0Buttons != -1) {
        closeButtonGroup(menu->list0Buttons);
        menu->list0Buttons = -1;
    }
    func_020846bc(0x31, 6, 0);
    window = getWindow(menu->windows[4]);
    func_020a8a98(menu->windows[4], 0, 0, window->width, window->height, 0);
    redrawWindow(menu->windows[4]);
}

/* Pauses the buttons of the first tab's list. */
void pauseFirstTabList(struct DigimonMenu *menu) {
    pauseButtonGroup(menu->list0Buttons);
}

/* Resumes the buttons of the first tab's list. */
void resumeFirstTabList(struct DigimonMenu *menu) {
    resumeButtonGroup(menu->list0Buttons);
}
