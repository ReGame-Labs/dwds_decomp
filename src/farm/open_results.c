#include "farm/open_results.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "farm/data.h"
#include "farm/farms.h"
#include "farm/results.h"

/* The id of the goods under the cursor of the farm's goods list, 0 if
 * none. */
s32 func_ov005_0227ee2c(void) {
    struct FarmGoodsList *list;
    s8 index;

    list = findTask(DIGIMON_LIST_TASK_ID);
    if (list == NULL) {
        return 0;
    }
    index = list->entries[list->scroll + list->cursor];
    if (index == -1) {
        return 0;
    }
    return getFarmGoodsIdAt(index);
}

/* Opens the results of the farm day. */
void openResults(void) {
    struct ResultsScreen *screen;

    screen              = createTask(&func_ov005_0227dd28, 0x108);
    RESULTS_TASK_ID     = getTaskId(screen);
    screen->state       = 0;
    screen->wait        = 0;
    data_ov005_022a1d18 = 0;
    data_ov005_022a1d30 = 0;
}
