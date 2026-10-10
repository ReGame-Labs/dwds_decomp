#include "menus/digimon/digimon_menu_tabs.h"
#include "engine/data.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"

/* Pauses the buttons of the equipment's rows. */
void pauseEquipSlotRows(struct DigimonMenu *menu) {
    pauseButtonGroup(menu->equipSlotButtons);
}

/* Resumes the buttons of the equipment's rows. */
void resumeEquipSlotRows(struct DigimonMenu *menu) {
    resumeButtonGroup(menu->equipSlotButtons);
}

/* Opens the menu of three by the equipment's row of the cursor, with the
 * cursor on its first choice. */
void openEquipSlotPopup(struct DigimonMenu *menu) {
    s32 i;
    struct Sprite *sprite;

    menu->work->popupSprite = createMainSprite(0x3CF, data_ov006_0229f0c0[menu->equipSlots->cursor * 4],
                                               data_ov006_0229f0c0[menu->equipSlots->cursor * 4 + 1], 7, 0);
    sprite                  = getMainSprite(menu->work->popupSprite);
    menu->popup->prevCursor = 0;
    menu->popup->cursor     = menu->popup->prevCursor;
    menu->popupButtons      = createButtonGroup(0x30, menu->popup->cursor, func_ov006_0228498c);
    for (i = 0; i < 3; i++) {
        addRectButton(sprite->x, (s16) (sprite->y + i * 16 + 0x18), 0x50, 0x10, 0, menu->popupButtons);
    }
}

/* Closes the menu of three by a row. */
void closeEquipSlotPopup(struct DigimonMenu *menu) {
    freeMainSprite(menu->work->popupSprite);
    if (menu->popupButtons != -1) {
        closeButtonGroup(menu->popupButtons);
        menu->popupButtons = -1;
    }
}

/* Shows the three tabs with the cursor on the one picked, and makes their
 * touch buttons. */
void openDigimonMenuTabs(struct DigimonMenu *menu) {
    s32 i;

    menu->work->tabSprite = createMainSprite(0x3D9, 0, 0, 8, 0);
    menu->tabButtons      = createButtonGroup(0x30, menu->tab->cursor, func_ov006_02284744);
    for (i = 0; i < 3; i++) {
        addRectButton(data_ov006_0229f090[i * 4], data_ov006_0229f090[i * 4 + 1], data_ov006_0229f090[i * 4 + 2],
                      data_ov006_0229f090[i * 4 + 3], 0, menu->tabButtons);
    }
    setMainSpriteAnim(menu->work->tabSprite, menu->tab->cursor, -1);
}

/* Removes the three tabs and their touch buttons. */
void closeDigimonMenuTabs(struct DigimonMenu *menu) {
    freeMainSprite(menu->work->tabSprite);
    if (menu->tabButtons != -1) {
        closeButtonGroup(menu->tabButtons);
        menu->tabButtons = -1;
    }
}

/* Pauses the touch buttons of the three tabs. */
void pauseDigimonMenuTabs(struct DigimonMenu *menu) {
    pauseButtonGroup(menu->tabButtons);
}
