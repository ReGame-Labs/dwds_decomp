#include "farm/panel_digimon.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/ui/gauge.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/farm_queries.h"
#include "farm/goods_panel.h"
#include "farm/open_results.h"
#include "field/actors/actor_files.h"
#include "menus/widgets/digimon_detail.h"
#include "menus/widgets/menu_displays.h"
#include "menus/widgets/status_window.h"

/* Ends the actor view, freeing its actor in mode 0. */
void func_ov005_0227fe84(struct ActorView *view) {
    if (view->mode == 0 && view->actor != 0xFFFF) {
        func_020c7060(view->actor);
    }
    endTask(view);
}

/* Shows the digimon with an id in panel 0. */
void func_ov005_0227fe6c(s32 digimon) {
    func_ov005_0227fdd8(getDigimon(digimon));
}

/* Shows the digimon with an id in panel 0xA. */
void func_ov005_0227fe54(s32 digimon) {
    func_ov005_0227fda8(getDigimon(digimon));
}

/* Shows the digimon in panel 0, drawn again even if it is the one shown. */
void func_ov005_0227fe08(s32 digimon) {
    struct DigimonPanel *panel;
    struct ActorView *view;

    if (getUiFlag(FARM_PANEL_DIGIMON) == 0) {
        return;
    }
    panel        = findTask(data_021e5cb8);
    panel->shown = NULL;
    view         = findTask(panel->actorTask);
    view->shown  = NULL;
    func_ov005_0227fe6c(digimon);
}

/* Closes panel 0xA. */
void func_ov005_0227fc64(void) {
    struct DigimonPanel *panel;

    if (getUiFlag(FARM_PANEL_DIGIMON_B) == 0) {
        return;
    }
    panel = findTask(data_021e5cb0);
    if (panel->statusUp != 0) {
        freeStatusWindowSprites(1);
        func_020587fc(1);
    }
    if (panel->unk38 != 0) {
        freeDigimonDetailSprites(1);
        func_02059c50(1);
    }
    closeWindowAndClear(&panel->window);
    releaseMenuDisplays();
    releaseGfxSlot(panel->gfxSlot);
    endTaskById(data_021e5cb0);
    data_021e5cb0 = 0;
    freeTextBank();
    clearUiFlag(FARM_PANEL_DIGIMON_B);
}

/* Opens the list of the goods of the farm with the id owner, from the given
 * entry and row on, sorted the first way. */
void func_ov005_0227fbb8(s32 owner, s16 scroll, s16 cursor, s8 palette, s8 unk33, u16 unk2C) {
    struct FarmGoodsList *list;

    list                 = createTask(&func_ov005_0227f688, 0x108);
    DIGIMON_LIST_TASK_ID = getTaskId(list);
    list->state          = 0;
    list->wait           = 0;
    list->owner          = owner;
    list->scroll         = scroll;
    list->cursor         = cursor;
    list->palette        = palette;
    list->unk33          = unk33;
    list->unk2C          = unk2C;
    list->inputTask      = 0;
    list->cursorEffect   = -1;
    list->unkA0          = -1;
    list->count          = countFarmGoods(list->owner);
    list->unk3C          = getFarmGoodsCapacity(owner);
    func_ov005_0227ee88(list->owner, list->entries);
    func_ov005_0228bb40(0, list->count, list->entries);
}
