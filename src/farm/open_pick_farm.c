#include "farm/open_pick_farm.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/text/text_labels.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "farm/data.h"
#include "farm/panel_pick_farm.h"

/* Frees the name window's sprites, text, window and graphics slot. */
void func_ov005_0228463c(struct DigimonNameWindow *task) {
    if (task->icon != 0xFFFF) {
        freeSubSprite(task->icon);
    }
    if (task->unk34 != 0xFFFF) {
        freeSubSprite(task->unk34);
    }
    if (task->unk32 != 0xFFFF) {
        freeSubSprite(task->unk32);
    }
    if (task->nameText != 0) {
        func_0209d900(task->nameText);
    }
    if (task->window != 0xFF) {
        closeWindow(task->window);
    }
    if (task->gfxSlot != -1) {
        releaseGfxSlot(task->gfxSlot);
    }
}

/* Puts the icon of the digimon's species at the window's top left. */
void func_ov005_022844c8(struct DigimonNameWindow *task) {
    struct Window *window;
    struct Digimon *digimon;

    window  = getWindow(task->window);
    digimon = getDigimon(task->digimon);
    task->icon =
        createSubSprite(func_020a31c4(digimon->unk4), (s16) ((window->x + 1) * 8), (s16) ((window->y + 2) * 8), 0xC, 0);
    setSubSpriteBgPriority(task->icon, 0);
}

/* Writes the digimon's name in the window, after sprite 0x21D. */
void func_ov005_022843e4(struct DigimonNameWindow *task) {
    struct Window *window;
    struct Digimon *digimon;

    window         = getWindow(task->window);
    digimon        = getDigimon(task->digimon);
    task->nameText = func_0209dbc8(digimon->name, (s16) ((window->x + 3) * 8 - 8), (s16) (window->y * 8), 0xD, 0, 0, 1, 0);
    task->unk34    = createSubSprite(0x21D, (s16) ((window->x + 2) * 8 - 8), (s16) (window->y * 8 - 2), 0xB, 0);
    setSubSpriteAnim(task->unk34, 2, -1);
    setSubSpriteBgPriority(task->unk34, 0);
    func_0203e848(task->unk34, 0x7E);
}

/* Opens panel 5 to pick a farm for the digimon. */
void openFarmChoice(s32 digimon, s16 flags) {
    struct FarmChoice *choice;

    if (getUiFlag(FARM_PANEL_PICK_FARM) != 0) {
        return;
    }
    choice          = createTask(func_ov005_022833e4, 0x109);
    data_021e5cc4   = getTaskId(choice);
    choice->state   = 0;
    choice->wait    = 0;
    choice->digimon = digimon;
    choice->flags   = flags;
    setUiFlag(FARM_PANEL_PICK_FARM);
}
