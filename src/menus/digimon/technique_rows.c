#include "menus/digimon/technique_rows.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/digimon/equip_rows.h"

/* Makes the touch buttons of the techniques' rows, one for each of the
 * Digimon's techniques (unk54, which an id from SKILL_COUNT on ends), with the
 * cursor on the first, and lights the row of the cursor. */
void openTechniqueRows(struct DigimonMenu *menu) {
    s32 i;
    s32 count;
    struct Digimon *digimon;

    digimon = menu->work->digimon;
    for (i = 0, count = 0; i < 7; i++, count++) {
        if (digimon->unk54[count] >= SKILL_COUNT) {
            break;
        }
    }
    menu->techniques->cursor = 0;
    menu->rowButtons         = createButtonGroup(0x30, menu->techniques->cursor, func_ov006_02285424);
    for (i = 0; i < count; i++) {
        addRectButton(data_ov006_0229f178[i * 4], data_ov006_0229f178[i * 4 + 1], data_ov006_0229f178[i * 4 + 2],
                      data_ov006_0229f178[i * 4 + 3], 0, menu->rowButtons);
    }
    findTask(menu->rowButtons);
    func_020846bc((s16) (menu->techniques->cursor + 0x31), 1, 8);
}

/* Removes the buttons of the techniques' rows and their light. */
void closeTechniqueRows(struct DigimonMenu *menu) {
    func_020846bc(0x31, 6, 0);
    if (menu->rowButtons != -1) {
        closeButtonGroup(menu->rowButtons);
        menu->rowButtons = -1;
    }
}
