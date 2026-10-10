#include "menus/digimon/guide_list.h"
#include "engine/bg/bg_layers.h"
#include "engine/bg/bg_screen.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/digimon/guide.h"
#include "menus/digimon/guide_orders.h"
#include "menus/digimon/guide_tabs.h"
#include "menus/widgets/scroll_bar.h"
#include "menus/widgets/text_list.h"
#include "nitro/pad.h"

/* Frees the rows of the list and their sprites. */
void func_ov006_0229b29c(struct DigimonGuide *guide) {
    s32 i;

    func_020a9610(2);
    closeTextList(guide->list);
    for (i = 0; i < 8; i++) {
        freeMainSprite(data_ov006_0229f610[i]);
        data_ov006_0229f610[i] = -1;
    }
    guide->list = -1;
}

/* Makes the two page buttons (data_ov006_0229f2ec), run by
 * func_ov006_0229afb4. */
void func_ov006_0229b1f0(struct DigimonGuide *guide) {
    s32 i;
    struct ButtonGroup *group;

    guide->pageButtons = createButtonGroup(0x32, 0, func_ov006_0229afb4);
    for (i = 0; i < 2; i++) {
        addRectButton(data_ov006_0229f2ec[i * 4], data_ov006_0229f2ec[i * 4 + 1], data_ov006_0229f2ec[i * 4 + 2],
                      data_ov006_0229f2ec[i * 4 + 3], 0, guide->pageButtons);
    }
    group          = findTask(guide->pageButtons);
    group->work[0] = 32;
    group->work[1] = 32;
}

/* Closes the page buttons. */
void func_ov006_0229b1c8(struct DigimonGuide *guide) {
    if (guide->pageButtons != -1) {
        closeButtonGroup(guide->pageButtons);
        guide->pageButtons = -1;
    }
}

/* The page buttons' callback: while one is held, scrolls the list by seven
 * rows after 32 frames, then 8 frames sooner each time, down to every 4 frames
 * (work[0] counts the frames, work[1] is the wait). While neither is touched,
 * left and right scroll by seven rows at the pad's repeat, unless the screen
 * is touched. */
void func_ov006_0229afb4(s16 button, s16 cursor, struct ButtonGroup *group) {
    struct DigimonGuide *guide = DIGIMON_GUIDE;

    if (func_ov006_02299b64(data_ov006_0229f2ec, 2) == 0) {
        if (getTouchHeld() != 0) {
            return;
        }
        if (!(getPadRepeat() & PAD_KEY_LEFT) && !(getPadRepeat() & PAD_KEY_RIGHT)) {
            return;
        }
        if (getPadRepeat() & PAD_KEY_LEFT) {
            if (guide->scroll > 0) {
                guide->scroll -= 7;
                if (guide->scroll < 0) {
                    guide->scroll = 0;
                }
                setScrollBarPos(guide->scrollBar, guide->scroll);
                func_ov006_0229ccc0();
                playSound(0);
            }
        } else if (getPadRepeat() & PAD_KEY_RIGHT) {
            if (guide->scroll < guide->maxScroll) {
                guide->scroll += 7;
                if (guide->scroll > guide->maxScroll) {
                    guide->scroll = guide->maxScroll;
                }
                setScrollBarPos(guide->scrollBar, guide->scroll);
                func_ov006_0229ccc0();
                playSound(0);
            }
        }
        return;
    }
    if (button == -1) {
        group->work[0] = 32;
        group->work[1] = 32;
    }
    switch (button) {
        case 0:
            if (guide->scroll > 0) {
                group->work[0]++;
                if (group->work[0] >= group->work[1]) {
                    guide->scroll -= 7;
                    if (guide->scroll < 0) {
                        guide->scroll = 0;
                    }
                    setScrollBarPos(guide->scrollBar, guide->scroll);
                    func_ov006_0229ccc0();
                    group->work[0] = 0;
                    group->work[1] -= 8;
                    if (group->work[1] < 4) {
                        group->work[1] = 4;
                    }
                }
            }
            break;
        case 1:
            if (guide->scroll < guide->maxScroll) {
                group->work[0]++;
                if (group->work[0] >= group->work[1]) {
                    guide->scroll += 7;
                    if (guide->scroll > guide->maxScroll) {
                        guide->scroll = guide->maxScroll;
                    }
                    setScrollBarPos(guide->scrollBar, guide->scroll);
                    func_ov006_0229ccc0();
                    group->work[0] = 0;
                    group->work[1] -= 8;
                    if (group->work[1] < 4) {
                        group->work[1] = 4;
                    }
                }
            }
            break;
    }
}

/* Makes the arrows' touch buttons, and the arrows as sprites 3 and 4. */
void func_ov006_0229aec4(struct DigimonGuide *guide) {
    s32 i;
    struct ButtonGroup *group;

    guide->arrowButtons = createButtonGroup(0x32, 0, func_ov006_0229ad58);
    for (i = 0; i < 2; i++) {
        addRectButton(data_ov006_0229f2fc[i * 4], data_ov006_0229f2fc[i * 4 + 1], data_ov006_0229f2fc[i * 4 + 2],
                      data_ov006_0229f2fc[i * 4 + 3], 0, guide->arrowButtons);
    }
    group          = findTask(guide->arrowButtons);
    group->work[0] = 32;
    group->work[1] = 32;
    createMainSpriteAt(0x3A7, 0xA8, 0, 4, 0, 3);
    createMainSpriteAt(0x3A8, 0xA8, 0x90, 4, 0, 4);
}

/* Closes the arrows' buttons and frees their sprites. */
void func_ov006_0229ae8c(struct DigimonGuide *guide) {
    if (guide->arrowButtons != -1) {
        closeButtonGroup(guide->arrowButtons);
        guide->arrowButtons = -1;
    }
    freeMainSprite(3);
    freeMainSprite(4);
}

/* The arrows' callback: as the page buttons', by one row. */
void func_ov006_0229ad58(s16 button, s16 cursor, struct ButtonGroup *group) {
    struct DigimonGuide *guide = DIGIMON_GUIDE;

    if (func_ov006_02299b64(data_ov006_0229f2fc, 2) == 0) {
        return;
    }
    if (button == -1) {
        group->work[0] = 32;
        group->work[1] = 32;
    }
    switch (button) {
        case 0:
            if (guide->scroll > 0) {
                group->work[0]++;
                if (group->work[0] >= group->work[1]) {
                    guide->scroll--;
                    setScrollBarPos(guide->scrollBar, guide->scroll);
                    func_ov006_0229ccc0();
                    group->work[0] = 0;
                    group->work[1] -= 8;
                    if (group->work[1] < 4) {
                        group->work[1] = 4;
                    }
                }
            }
            break;
        case 1:
            if (guide->scroll < guide->maxScroll) {
                group->work[0]++;
                if (group->work[0] >= group->work[1]) {
                    guide->scroll++;
                    setScrollBarPos(guide->scrollBar, guide->scroll);
                    func_ov006_0229ccc0();
                    group->work[0] = 0;
                    group->work[1] -= 8;
                    if (group->work[1] < 4) {
                        group->work[1] = 4;
                    }
                }
            }
            break;
    }
}

/* Makes the touch buttons of the eight rows, with the cursor on its row. */
void func_ov006_0229ac94(struct DigimonGuide *guide) {
    s32 i;
    struct ButtonGroup *group;

    guide->rowButtons = createButtonGroup(0x32, guide->cursor, func_ov006_0229a6d4);
    for (i = 0; i < 8; i++) {
        addRectButton(data_ov006_0229f3ac[i * 4], data_ov006_0229f3ac[i * 4 + 1], data_ov006_0229f3ac[i * 4 + 2],
                      data_ov006_0229f3ac[i * 4 + 3], 0, guide->rowButtons);
    }
    group          = findTask(guide->rowButtons);
    group->work[0] = 32;
    group->work[1] = 32;
    group->work[5] = 0x40;
    group->work[6] = -4;
    group->work[7] = 0;
}

/* Closes the rows' buttons. */
void func_ov006_0229ac6c(struct DigimonGuide *guide) {
    if (guide->rowButtons != -1) {
        closeButtonGroup(guide->rowButtons);
        guide->rowButtons = -1;
    }
}
