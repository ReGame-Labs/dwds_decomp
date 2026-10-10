#include "battle/battle_mode/map_scroll.h"
#include "battle/battle_mode/data.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/system/system.h"

/* The map's scroll task, which startMapScrollTask starts: from its second
 * frame on, the stylus scrolls the map. */
void tickMapScrollTask(void) {
    struct MapScrollTask *task = (struct MapScrollTask *) getCurrentTask();

    switch (task->step) {
        case 0:
            task->step++;
            break;
        case 1:
            scrollMapByTouch();
            break;
    }
    func_ov002_0222b5d8();
}

/* While allowed, a touch near an edge of the screen scrolls the map toward it. */
void scrollMapByTouch(void) {
    u16 x;
    u16 y;

    if (TOUCH_SCROLL_ENABLED == 0) {
        return;
    }
    if (getTouchHeld() == 0) {
        return;
    }
    x = getTouchX();
    y = getTouchY();
    if (x < 120) {
        BATTLE_MAP_SCROLL.x[0].part.whole -= 2;
    } else if (x > 136) {
        BATTLE_MAP_SCROLL.x[0].part.whole += 2;
    }
    if (y < 90) {
        BATTLE_MAP_SCROLL.y[0].part.whole -= 2;
    } else if (y > 102) {
        BATTLE_MAP_SCROLL.y[0].part.whole += 2;
    }
}

/* Stops the stylus from scrolling the map. */
void disableTouchScroll(void) {
    TOUCH_SCROLL_ENABLED = 0;
}

/* Lets the stylus scroll the map. */
void enableTouchScroll(void) {
    TOUCH_SCROLL_ENABLED = 1;
}

/* Scrolls the map to (x, y). */
void setMapScroll(s16 x, s16 y) {
    BATTLE_MAP_SCROLL.x[0].part.whole = x;
    BATTLE_MAP_SCROLL.y[0].part.whole = y;
}
