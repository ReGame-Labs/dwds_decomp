#include "farm/results.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/save/game_state.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/ui/gauge.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/farm_screen.h"
#include "farm/farms.h"
#include "farm/results_food.h"
#include "field/actors/actor_tasks.h"

/* Does nothing; the results screen calls it twice. */
void func_ov005_0227dad4(void) {}

/* Settles the day's food: keeps the food before, what the farms gathered and
 * what their digimon ate in the results, and adds the difference to the food.
 * Flag 0x3EE is set when the food and what was gathered don't cover what was
 * eaten (func_020a0894). */
void settleFarmFood(struct Results *results) {
    if (func_020a0894() == 0) {
        setGameFlag(0x3EE);
    } else {
        clearGameFlag(0x3EE);
    }
    results->food     = addFood(0);
    results->consumed = getFoodConsumed();
    results->produced = getFoodProduced();
    addFood(results->produced - results->consumed);
}

/* Ages the goods of every farm by a day: counts their unkE up to 99 and grows
 * them toward their next stage. */
void ageFarmGoods(void) {
    s32 i;
    s32 j;
    struct Farm *farm;
    struct FarmGoods *goods;

    for (i = 0; i < FARM_COUNT; i++) {
        farm = (struct Farm *) getGroupInOrder(i);
        if (farm == NULL) {
            return;
        }
        for (j = 0; j < FARM_SLOT_COUNT && farm->goods[j] != 0; j++) {
            goods = findFarmGoods(farm->goods[j]);
            goods->unkE++;
            if (goods->unkE > 99) {
                goods->unkE = 99;
            }
            growFarmGoods(farm->goods[j]);
        }
    }
}

/* Whether the results are on screen. */
s32 isResultsOpen(void) {
    if (RESULTS_TASK_ID != 0xFFFF) {
        return 1;
    }
    return 0;
}

/* The results of the results screen. */
struct Results *getResults(void) {
    struct ResultsScreen *screen = findTask(RESULTS_TASK_ID);

    return screen->results;
}

/* The digimon as it was before the day ended, or NULL if it is in no farm. */
struct Digimon *getDigimonBeforeDay(s32 digimon) {
    s32 i;
    struct Results *results;

    results = getResults();
    for (i = 0; i < results->count; i++) {
        if (digimon == results->digimon[i].id) {
            break;
        }
    }
    if (i == results->count) {
        return NULL;
    }
    return &results->digimon[i];
}

/* Closes the results screen: frees its backgrounds, windows and graphics, and
 * the results. */
void closeResults(void) {
    struct Results *results;
    struct ResultsScreen *screen;

    screen = findTask(RESULTS_TASK_ID);
    func_0208577c(3, screen->unk2C);
    func_02085710(3, screen->unk2E);
    closeWindowAndClear(&screen->windows[0]);
    closeWindowAndClear(&screen->windows[1]);
    releaseGfxSlot(screen->gfxSlots[0]);
    releaseGfxSlot(screen->gfxSlots[1]);
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a98a8(4);
    func_020a98a8(5);
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(4);
    func_020a9844(5);
    endMainActorTask();
    results = screen->results;
    heapFree(results);
    freeTextBank();
    endTaskById(RESULTS_TASK_ID);
    RESULTS_TASK_ID = 0xFFFF;
}

/* Opens the "Food Information" windows of the farm with the id owner. */
void openFarmFoodInfo(s32 owner, s8 unk28, s16 unk2A) {
    struct FarmFoodInfo *balance;

    balance             = createTask(&tickFarmFoodInfo, 0x10F);
    data_ov005_022a1d18 = getTaskId(balance);
    balance->state      = 0;
    balance->wait       = 0;
    balance->owner      = owner;
    balance->unk28      = unk28;
    balance->unk2A      = unk2A;
}
