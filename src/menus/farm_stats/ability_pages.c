#include "menus/farm_stats/ability_pages.h"
#include "engine/bg/bg_screen.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/input/touch.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/farm_stats/stats_screen.h"
#include "menus/widgets/skill_displays.h"
#include "nitro/pad.h"

/* Closes the six buttons func_020ca0a8 opens (callback func_020c9de8): dims
 * them back and ends their group. */
void func_020ca070(struct StatsScreen *screen) {
    func_020846bc(MENU_TAB_COLORS, MENU_TAB_COUNT, 0);
    if (screen->buttons == -1) {
        return;
    }
    closeButtonGroup(screen->buttons);
    screen->buttons = -1;
}

/* Opens the ability pages on the first: a button group for the five page tabs,
 * with func_020c9b88 for its callback, and the first tab lit. */
void openAbilityPages(struct StatsScreen *screen) {
    s32 i;

    screen->page    = 0;
    screen->buttons = createButtonGroup(0x30, screen->page, func_020c9b88);
    for (i = 0; i < ABILITY_PAGE_COUNT; i++) {
        addRectButton(data_021283d4[i * 4], data_021283d4[i * 4 + 1], data_021283d4[i * 4 + 2], data_021283d4[i * 4 + 3], 0,
                      screen->buttons);
    }
    findTask(screen->buttons);
    func_020846bc((s16) (screen->page + ABILITY_TAB_COLORS), 1, TAB_LIGHT);
}

/* Closes the ability pages: dims their tabs back and ends their group. */
void closeAbilityPages(struct StatsScreen *screen) {
    func_020846bc(ABILITY_TAB_COLORS, ABILITY_PAGE_COUNT, 0);
    if (screen->buttons == -1) {
        return;
    }
    closeButtonGroup(screen->buttons);
    screen->buttons = -1;
}

/* The ability pages' button group callback: a touched tab turns to its page,
 * which shows one of the Digimon's four abilities (unk22, with its unk2C) or, on the
 * last, its species' (unk28). B or the Back button at (16, 168) closes them. */
void func_020c9b88(s16 touched, s16 cursor, struct ButtonGroup *group) {
    struct StatsScreen *screen;
    s32 changed;
    struct Digimon *digimon;
    struct SpeciesData *species;

    screen = findTask(STATS_SCREEN_TASK_ID);
    getTaskId(group);
    changed = 0;
    getTouchX();
    getTouchY();
    if (touched != -1 && screen->page != touched) {
        screen->page = touched;
        changed      = 1;
    }
    if (changed == 1) {
        func_020846bc(ABILITY_TAB_COLORS, ABILITY_PAGE_COUNT, 0);
        func_020846bc((s16) (screen->page + ABILITY_TAB_COLORS), 1, TAB_LIGHT);
        switch (screen->page) {
            case 0:
                digimon = screen->digimon;
                func_02053868(0, digimon->unk22[0], digimon->unk2C[0]);
                break;
            case 1:
                digimon = screen->digimon;
                func_02053868(0, digimon->unk22[1], digimon->unk2C[1]);
                break;
            case 2:
                digimon = screen->digimon;
                func_02053868(0, digimon->unk22[2], digimon->unk2C[2]);
                break;
            case 3:
                digimon = screen->digimon;
                func_02053868(0, digimon->unk22[3], digimon->unk2C[3]);
                break;
            case 4:
                species = loadSpeciesData(screen->digimon->unk4);
                func_02053868(0, species->unk28, -1);
                break;
        }
    }
    if (!(getPadPressed() & PAD_BUTTON_B) && func_020419c0(16, 168, 48, 16) == 0) {
        return;
    }
    closeAbilityPages(screen);
    screen->state = STATS_STATE_ABILITIES_CLOSED;
}
