#include "eggs/egg_panel.h"
#include "engine/data.h"
#include "engine/script/interpreter.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "field/actors/actor_files.h"

#define UI_FLAG_EGG_PANEL 0xC
#define UI_FLAG_EGG_MENU 0xE
#define STATE_SHOW_NEXT 600 /* func_02096a9c shows nextEgg */

/* Opens the DigiEgg panel on an egg, or only shows that egg when the panel
 * is open. */
void openEggPanel(s8 egg, s8 palette, s8 unk21, s16 unk24) {
    struct EggPanel *panel;

    if (getUiFlag(UI_FLAG_EGG_PANEL) != 0) {
        showEggOnPanel(egg);
        return;
    }
    panel          = createTask(func_02096a9c, 0x113);
    panel->state   = 0;
    panel->wait    = 0;
    panel->palette = palette;
    panel->unk21   = unk21;
    panel->egg     = egg;
    panel->unk24   = unk24;
    data_021da3fc  = getTaskId(panel);
    setUiFlag(UI_FLAG_EGG_PANEL);
}

/* Shows another egg on the open DigiEgg panel. */
void showEggOnPanel(s8 egg) {
    struct EggPanel *panel;

    if (getUiFlag(UI_FLAG_EGG_PANEL) == 0) {
        return;
    }
    panel = findTask(data_021da3fc);
    if (panel->egg != egg) {
        panel->state   = STATE_SHOW_NEXT;
        panel->nextEgg = egg;
    }
}

/* Closes the DigiEgg panel. */
void closeEggPanel(void) {
    struct EggPanel *panel;

    if (getUiFlag(UI_FLAG_EGG_PANEL) == 0) {
        return;
    }
    panel = findTask(data_021da3fc);
    if (panel->unk28 != -1) {
        func_020c7060(panel->unk28);
    }
    closeWindow(panel->window);
    releaseGfxSlot(panel->gfxSlot);
    endTask(panel);
    data_021da3fc = 0;
    clearUiFlag(UI_FLAG_EGG_PANEL);
}

/* Starts the menu around the DigiEgg panel (func_02095c4c) on an egg,
 * unless it runs. */
void func_020964ec(s8 unk20, s8 palette, s8 unk22, s8 unk23, u16 egg) {
    struct EggMenu *menu;

    if (getUiFlag(UI_FLAG_EGG_MENU) != 0) {
        return;
    }
    menu          = createTask(func_02095c4c, 0x113);
    menu->state   = 0;
    menu->wait    = 0;
    menu->unk20   = unk20;
    menu->palette = palette;
    menu->unk22   = unk22;
    menu->unk23   = unk23;
    menu->egg     = egg;
    data_021da400 = getTaskId(menu);
    setUiFlag(UI_FLAG_EGG_MENU);
}
