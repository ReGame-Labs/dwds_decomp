#include "menus/digimon/ov006_0228b1f8.h"
#include "engine/digimon/digimon_records.h"
#include "engine/input/touch.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"

/* Opens a button for each entry of the Digimon's unk54 list, up to seven, the
 * first one chosen: its color, one of the six from 0x31, is brightened. */
void openStatusTechniqueButtons(struct StatusScreen *screen) {
    s32 count;
    s32 i;

    func_020a29c4(screen->species, &screen->work->digimon);
    for (count = 0; count < 7; count++) {
        if (screen->work->digimon.unk54[count] == 0xFFFF) {
            break;
        }
    }
    screen->cursor  = 0;
    screen->buttons = createButtonGroup(0x30, screen->cursor, func_ov006_0228b468);
    for (i = 0; i < count; i++) {
        addRectButton(data_ov006_0229f210[i * 4], data_ov006_0229f210[i * 4 + 1], data_ov006_0229f210[i * 4 + 2],
                      data_ov006_0229f210[i * 4 + 3], 0, screen->buttons);
    }
    findTask(screen->buttons);
    func_020846bc((s16) (screen->cursor + 0x31), 1, 8);
}

/* Closes the buttons of openStatusTechniqueButtons and gives the six colors back. */
void closeStatusTechniqueButtons(struct StatusScreen *screen) {
    func_020846bc(0x31, 6, 0);
    if (screen->buttons == -1) {
        return;
    }
    closeButtonGroup(screen->buttons);
    screen->buttons = -1;
}

/* Whether the touch screen was tapped in the rectangle, its edges included. */
BOOL isRectTappedInclusive(s32 x, s32 y, s32 width, s32 height) {
    s16 touchX;
    s16 touchY;

    if (getTouchTap() == 0) {
        return FALSE;
    }
    touchX = getTouchX();
    touchY = getTouchY();
    if (x <= touchX && x + width >= touchX && y <= touchY && y + height >= touchY) {
        return TRUE;
    }
    return FALSE;
}

/* Whether the Digimon menu has closed: its task clears DIGIMON_MENU
 * when it ends. */
u8 isDigimonMenuClosed(void) {
    return DIGIMON_MENU == NULL;
}
