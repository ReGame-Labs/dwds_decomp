#include "menus/farm_stats/stats_open.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "menus/farm_stats/stats_screen.h"
#include "menus/shop/farm_shops.h"
#include "menus/widgets/menu_displays.h"
#include "menus/widgets/window_anim.h"

/* Clears what func_020d0f30 wrote. */
void func_020cd6ac(struct Shop *shop) {
    func_020d0ef8(shop);
}

/* The end of the View Stats screen's task: frees its buffer, forgets the
 * screen and tears down the display task (startMenuDisplaysTask) and the windows. */
void endStatsScreen(void) {
    void *buffer;

    buffer = ((struct StatsScreen *) getCurrentTask())->buffer;
    heapFree(buffer);
    STATS_SCREEN_TASK_ID = -1;
    STATS_SCREEN         = NULL;
    releaseMenuDisplays();
    unloadMainWindowFrame();
    unloadSubWindowFrame();
}

/* Whether the View Stats screen is closed. */
u8 isStatsScreenClosed(void) {
    u8 closed;

    if (STATS_SCREEN == NULL) {
        closed = 1;
    } else {
        closed = 0;
    }
    return closed;
}
