#include "menus/digimon/menu_digivolve.h"
#include "engine/data.h"
#include "menus/digiconvert/convert_scene.h"

/* Whether the scene started from the Digimon menu has ended. */
u8 isMenuDigivolveDone(void) {
    u8 ended;

    if (MENU_DIGIVOLVE_TASK == NULL) {
        ended = TRUE;
    } else {
        ended = FALSE;
    }
    return ended;
}

/* Starts the scene that converts a scanned species into a Digimon (the
 * converter screen's). */
void startConvert(s32 species) {
    startConvertTask(species);
}
