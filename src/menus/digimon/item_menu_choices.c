#include "menus/digimon/item_menu_choices.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/libs.h"
#include "engine/sprite/sprite.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/widgets/item_displays.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"
#include "nitro/pad.h"

/* Clears the VRAM of both screens' backgrounds and sprites, their OAM and
 * their blending: the same as func_ov006_0227c088. */
void func_ov006_0227fd6c(void) {
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

/* Loads the fonts the item menu writes with on both screens: font_dg, font00,
 * font_s and font_s2 (1, 2, 4 and 5 of data_02127184). */
void loadItemMenuFonts(void) {
    func_020a9c40(1, 3, 0xF);
    func_020a9c40(2, 5, 0xF);
    func_020a9c40(4, 0xA, 0x10);
    func_020a9c40(5, 0xB, 0x10);
    func_020a9ae0(1, 2, 0xF);
    func_020a9ae0(2, 4, 0xF);
    func_020a9ae0(4, 6, 0xF);
    func_020a9ae0(5, 8, 0xF);
}

/* Unloads the fonts of loadItemMenuFonts. */
void unloadItemMenuFonts(void) {
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a98a8(4);
    func_020a98a8(5);
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(4);
    func_020a9844(5);
}

/* Closes the display that func_ov006_0227fc08 opens. */
void func_ov006_0227fbe8(void) {
    freeItemRecordDisplaySprites(0);
    closeItemRecordDisplay(0);
}

/* Closes the displays that func_ov006_0227fb2c opens. */
void func_ov006_0227fb0c(void) {
    freeBagDisplaySprites(0);
    closeBagDisplay(0);
}

/* Closes the display that func_ov006_0227fa90 opens. */
void func_ov006_0227fa70(void) {
    freeItemNameDisplaySprite(0);
    closeItemNameDisplay(0);
}

/* Closes the displays that func_ov006_0227f9d8 opens. */
void func_ov006_0227f9b8(void) {
    freeKeyItemDisplaySprites(0);
    closeKeyItemDisplay(0);
}

/* Makes the touch buttons of the two choices and shows the cursor on the one
 * chosen. */
void func_ov006_0227f904(struct ItemMenu *menu) {
    s32 i;

    menu->choiceButtons = createButtonGroup(0x30, menu->choice, func_ov006_0227f7e4);
    for (i = 0; i < 2; i++) {
        addRectButton(data_ov006_0229ef88[i * 4], data_ov006_0229ef88[i * 4 + 1], data_ov006_0229ef88[i * 4 + 2],
                      data_ov006_0229ef88[i * 4 + 3], 0, menu->choiceButtons);
    }
    setMainSpriteAnim(menu->choiceSprite, menu->choice + 1, -1);
}

/* Removes the touch buttons of the two choices. */
void func_ov006_0227f8dc(struct ItemMenu *menu) {
    if (menu->choiceButtons != -1) {
        closeButtonGroup(menu->choiceButtons);
        menu->choiceButtons = -1;
    }
}

/* The two choices' callback: a touch moves the cursor, and A or a touch
 * released on a button goes on to the list of the choice, the menu's state
 * 0x3F2 for the first and 0x7DA for the second. */
void func_ov006_0227f7e4(s16 button, s16 cursor, struct ButtonGroup *group) {
    s32 changed;
    struct ItemMenu *menu = ITEM_MENU;
    s32 id                = getTaskId(group);

    changed = FALSE;
    getTouchX();
    getTouchY();
    switch (button) {
        case 0:
            if (menu->choice != button) {
                menu->prevChoice = menu->choice;
                menu->choice     = button;
                changed          = TRUE;
            }
            break;
        case 1:
            if (menu->choice != button) {
                menu->prevChoice = menu->choice;
                menu->choice     = button;
                changed          = TRUE;
            }
            break;
    }
    if ((getPadPressed() & PAD_BUTTON_A) || takeButtonGroupTap(id) != 0) {
        playSound(1);
        switch (menu->choice) {
            case 0:
                changed     = TRUE;
                menu->state = 0x3F2;
                break;
            case 1:
                changed     = TRUE;
                menu->state = 0x7DA;
                break;
        }
    }
    if (changed == TRUE) {
        setMainSpriteAnim(menu->choiceSprite, menu->choice + 1, -1);
    }
}
