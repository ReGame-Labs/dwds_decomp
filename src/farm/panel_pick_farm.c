#include "farm/panel_pick_farm.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "engine/ui/gauge.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/farm_queries.h"
#include "farm/farms.h"
#include "farm/goods_panel.h"
#include "farm/panel_pages.h"
#include "field/actors/actor_files.h"
#include "nitro/pad.h"

/* Whether panel 5 is open. */
s32 isFarmChoiceOpen(void) {
    return getUiFlag(FARM_PANEL_PICK_FARM);
}

/* The farm picked in panel 5: -1 if it is not open, 0 until one is picked. */
s32 getChosenFarm(void) {
    s32 farm = 0;

    if (getUiFlag(FARM_PANEL_PICK_FARM) != 0) {
        struct FarmChoice *choice = findTask(data_021e5cc4);

        if (choice->state == 900) {
            farm = choice->farm;
        }
    } else {
        farm = -1;
    }
    return farm;
}

/* Closes panel 5. */
void closeFarmChoice(void) {
    if (getUiFlag(FARM_PANEL_PICK_FARM) == 0) {
        return;
    }
    func_ov005_02283048();
    endTaskById(data_021e5cc4);
    data_021e5cc4 = 0;
    clearUiFlag(FARM_PANEL_PICK_FARM);
}

/* Frees what panel 5 shows, but leaves its task. */
void func_ov005_02283048(void) {
    struct FarmChoice *choice;

    if (getUiFlag(FARM_PANEL_PICK_FARM) == 0) {
        return;
    }
    choice = findTask(data_021e5cc4);
    if (!(choice->flags & 1)) {
        func_020c6fb8(choice->actor);
    }
    closeWindowAndClear(&choice->window);
    releaseGfxSlot(choice->gfxSlots[1]);
    releaseGfxSlot(choice->gfxSlots[0]);
    func_ov005_022890f0();
}

/* Whether panel 8 is open. */
s32 isFarmTabsOpen(void) {
    return getUiFlag(FARM_PANEL_TABS);
}

/* Opens panel 8 on the farm with that index. */
void openFarmTabs(s16 farm) {
    struct FarmTabs *tabs;

    tabs          = createTask(&func_ov005_02282c58, 0x10F);
    data_021e5cb4 = getTaskId(tabs);
    tabs->state   = 0;
    tabs->wait    = 0;
    tabs->farm    = farm;
    setUiFlag(FARM_PANEL_TABS);
}

/* The handler of panel 8's touch buttons, called with the touched and the
 * selected button: B or button 5 cancels, L and R or buttons 6 and 7 change the
 * farm, and buttons 0 to 4 are the tabs. */
void func_ov005_02282a58(s32 touched, s32 selected, void *buttons) {
    u16 keys;
    struct FarmTabs *tabs;
    s32 count;
    s16 hit;

    keys = getPadPressed();
    if (data_021e5ca4 != -1) {
        return;
    }
    tabs  = findTask(data_021e5cb4);
    count = countFarms();
    hit   = getGroupTappedButton(buttons);
    if ((keys & PAD_BUTTON_B) || hit == 5) {
        playSound(3);
        tabs->result = 0;
        return;
    }
    if ((keys & 0x200) /* L */ || hit == 6) {
        playSound(0xD);
        tabs->farm--;
        if (tabs->farm < 0) {
            tabs->farm = count - 1;
        }
        tabs->farmId = getFarmIdAt(tabs->farm);
        drawFarmStatus(tabs->farmId);
        setFarmPage(tabs->farmId, selected + 3);
        return;
    }
    if ((keys & 0x100) /* R */ || hit == 7) {
        playSound(0xD);
        tabs->farm++;
        if (tabs->farm >= count) {
            tabs->farm = 0;
        }
        tabs->farmId = getFarmIdAt(tabs->farm);
        drawFarmStatus(tabs->farmId);
        setFarmPage(tabs->farmId, selected + 3);
        return;
    }
    if (touched != selected || touched >= 5 || tabs->tab == touched) {
        return;
    }
    if (tabs->cursorEffect != -1) {
        stopSubPaletteEffects(tabs->cursorEffect);
        restoreSubPalette(0xAB, 5);
    }
    tabs->cursorEffect = func_020839c8((s16) (touched + 0xAB), 1, 0x7FFF, 0x50, 1, 2, 10000);
    setFarmPage(tabs->farmId, selected + 3);
    tabs->tab = touched;
}

/* Opens panel 4 on the page of the farm, or turns to it if it is open. */
void openFarmPages(s32 owner, s16 page, s8 palette) {
    struct FarmPages *pages;

    if (getUiFlag(FARM_PANEL_PAGES) != 0) {
        setFarmPage(owner, page);
        return;
    }
    pages          = createTask(&func_ov005_02281080, 0x10F);
    data_021e5cb8  = getTaskId(pages);
    pages->state   = 0;
    pages->wait    = 0;
    pages->owner   = owner;
    pages->page    = page;
    pages->palette = palette;
    setUiFlag(FARM_PANEL_PAGES);
}
