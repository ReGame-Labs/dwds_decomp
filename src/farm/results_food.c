#include "farm/results_food.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_args.h"
#include "engine/text/text_banks.h"
#include "engine/text/window_text.h"
#include "engine/ui/gauge.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/stats_window.h"

/* Closes the "Food Information" windows. */
void closeFarmFoodInfo(void) {
    struct FarmFoodInfo *balance;

    balance = findTask(data_ov005_022a1d18);
    closeWindowAndClear(&balance->window);
    closeWindowAndClear(&balance->consumedWindow);
    releaseGfxSlot(balance->gfxSlot);
    func_020a98a8(2);
    endTaskById(data_ov005_022a1d18);
    freeTextBank();
    data_ov005_022a1d18 = 0;
}

/* Turns the "Food Information" windows to the farm with the id owner. */
void setFarmFoodInfoFarm(s32 owner) {
    struct FarmFoodInfo *balance;

    balance        = findTask(data_ov005_022a1d18);
    balance->owner = owner;
    drawFarmFoodInfo(balance->window, balance->consumedWindow, balance->owner);
}

/* Opens the window of the food of the results. */
void openFoodWindow(s8 unk24, s16 unk26, struct Results *results) {
    struct FoodWindow *foodWindow;

    foodWindow          = createTask(&func_ov005_0227d0c4, 0x10E);
    data_ov005_022a1d30 = getTaskId(foodWindow);
    foodWindow->state   = 0;
    foodWindow->wait    = 0;
    foodWindow->unk24   = unk24;
    foodWindow->unk26   = unk26;
    foodWindow->results = results;
}

/* Writes FARM_TEXTS 0xCD in the window: the food before, what the farms
 * gathered, what their digimon ate and the food after, which stays within 0
 * and 999999 as the food does. */
void drawFoodWindow(u8 window, struct Results *results) {
    u16 text[0x40];
    s32 after;
    s32 consumed;
    s32 produced;
    s32 food;

    food     = results->food;
    produced = results->produced;
    consumed = results->consumed;
    after    = food + produced - consumed;
    if (after < 0) {
        after = 0;
    }
    if (after > 999999) {
        after = 999999;
    }
    formatNumber(food, 6, text, 0);
    setTextArg(0, text);
    func_0209d0ec(produced, 6, text);
    setTextArg(1, text);
    func_0209d0ec(-consumed, 6, text);
    setTextArg(2, text);
    formatNumber(after, 6, text, 0);
    setTextArg(3, text);
    func_020a6990(window, 3, 1, 0x1C, 0xF, getFarmText(0xCD), 0, 2, 1);
}

/* Closes the window of the food of the results. */
void closeFoodWindow(void) {
    struct FoodWindow *foodWindow;

    foodWindow = findTask(data_ov005_022a1d30);
    closeWindowAndClear(&foodWindow->window);
    releaseGfxSlot(foodWindow->gfxSlot);
    func_020a9844(2);
    endTaskById(data_ov005_022a1d30);
    freeTextBank();
    data_ov005_022a1d30 = 0;
}

/* Opens the stats of a digimon before and after the results, or shows the
 * given digimon's if they are open. */
void openStatsCompare(s32 digimon, s8 palette, s8 unk2D, s16 unk2E) {
    struct StatsCompare *compare;

    if (getUiFlag(FARM_PANEL_STATS) != 0) {
        showStatsCompare(digimon);
        return;
    }
    compare          = createTask(&func_ov005_0227c9ac, 0x10F);
    data_021e5cb8    = getTaskId(compare);
    compare->state   = 0;
    compare->wait    = 0;
    compare->digimon = digimon;
    compare->shown   = 0;
    compare->palette = palette;
    compare->unk2D   = unk2D;
    compare->unk2E   = unk2E;
    setUiFlag(FARM_PANEL_STATS);
}
