#include "menus/experience/experience_screen.h"
#include "battle/characters/chr.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/palette/palette_buffers.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/window/window.h"
#include "menus/widgets/menu_displays.h"
#include "menus/widgets/status_window.h"

/* Returns whether the experience screen is open. */
BOOL func_0209ed64(void) {
    if (data_021da770 != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Closes the experience screen: frees its battle characters, windows and
 * graphics. */
void func_0209ec80(void) {
    struct ExpScreen *screen;

    screen = findTask(data_021da770);
    removeAllMainBattleChrs();
    endBattleChrs();
    freeStatusWindowSprites(0);
    func_020587fc(0);
    releaseMenuDisplays();
    stopMainPaletteEffectsButFades(screen->unk31);
    stopSubPaletteEffectsButFades(screen->unk32);
    func_0208577c(3, screen->unk28);
    func_02085710(3, screen->unk2A);
    closeWindow(screen->windows[0]);
    closeWindow(screen->windows[1]);
    closeWindow(screen->windows[2]);
    closeWindow(screen->windows[3]);
    closeWindow(screen->windows[4]);
    func_020a9610(screen->gfxSlots[0]);
    func_020a9610(screen->gfxSlots[1]);
    func_020a9610(screen->gfxSlots[2]);
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a98a8(5);
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(5);
    endTask(screen);
    data_021da770 = 0;
}

/* Returns one of the system texts of data_02119350 ("Save complete.",
 * "Money", "Food", ...). */
void *func_0209ec68(s16 index) {
    return func_0209d470(data_02119350, index);
}
