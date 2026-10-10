#include "menus/digimon/equip_rows.h"
#include "engine/bg/bg_layers.h"
#include "engine/bg/bg_screen.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/input/touch.h"
#include "engine/palette/palette_fade.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/widgets/skill_displays.h"
#include "nitro/pad.h"

/* Makes the touch buttons of the traits' five rows with the cursor on the
 * first, lights the row of the cursor and shows the sprite 0x3C8. */
void openTraitRows(struct DigimonMenu *menu) {
    s32 i;

    menu->traits->cursor = 0;
    menu->rowButtons     = createButtonGroup(0x30, menu->traits->cursor, func_ov006_02285154);
    for (i = 0; i < 5; i++) {
        addRectButton(data_ov006_0229f120[i * 4], data_ov006_0229f120[i * 4 + 1], data_ov006_0229f120[i * 4 + 2],
                      data_ov006_0229f120[i * 4 + 3], 0, menu->rowButtons);
    }
    findTask(menu->rowButtons);
    func_020846bc((s16) (menu->traits->cursor + 0x37), 1, 8);
    menu->work->unk368 = createMainSprite(0x3C8, 0xC8, 0x70, 4, 0);
    setMainSpriteAnim(menu->work->unk368, 2, -1);
}

/* Removes the traits' rows: their light, their buttons and the sprite. */
void closeTraitRows(struct DigimonMenu *menu) {
    func_020846bc(0x37, 5, 0);
    if (menu->rowButtons != -1) {
        closeButtonGroup(menu->rowButtons);
        menu->rowButtons = -1;
    }
    freeMainSprite(menu->work->unk368);
}

/* The callback of the traits' rows: a touch moves the cursor and shows the
 * row's trait, one of the four the Digimon has learned (unk22) or, last, its
 * species' (unk28). B or a touch of the rect at (16, 168) leaves for state
 * 0x23FA. */
void func_ov006_02285154(s16 button, s16 cursor, struct ButtonGroup *group) {
    struct DigimonMenu *menu;
    struct Digimon *digimon;
    struct SpeciesData *species;
    s32 changed;

    menu = findTask(DIGIMON_MENU_TASK_ID);
    getTaskId(group);
    changed = FALSE;
    getTouchX();
    getTouchY();
    if (button != -1 && menu->traits->cursor != button) {
        menu->traits->cursor = button;
        changed              = TRUE;
    }
    if (changed == TRUE) {
        func_020846bc(0x37, 5, 0);
        func_020846bc((s16) (menu->traits->cursor + 0x37), 1, 8);
        switch (menu->traits->cursor) {
            case 0:
                digimon = menu->work->digimon;
                func_02053868(0, digimon->unk22[0], digimon->unk2C[0]);
                break;
            case 1:
                digimon = menu->work->digimon;
                func_02053868(0, digimon->unk22[1], digimon->unk2C[1]);
                break;
            case 2:
                digimon = menu->work->digimon;
                func_02053868(0, digimon->unk22[2], digimon->unk2C[2]);
                break;
            case 3:
                digimon = menu->work->digimon;
                func_02053868(0, digimon->unk22[3], digimon->unk2C[3]);
                break;
            case 4:
                species = loadSpeciesData(menu->work->digimon->unk4);
                func_02053868(0, species->unk28, -1);
                break;
        }
    }
    if ((getPadPressed() & PAD_BUTTON_B) || func_020419c0(0x10, 0xA8, 0x30, 0x10) != 0) {
        playSound(3);
        menu->state = 0x23FA;
    }
}

/* Removes the equipment's rows: their light and their buttons. */
void closeEquipSlotRows(struct DigimonMenu *menu) {
    func_020846bc(0x37, 4, 0);
    if (menu->equipSlotButtons != -1) {
        closeButtonGroup(menu->equipSlotButtons);
        menu->equipSlotButtons = -1;
    }
}
