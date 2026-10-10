#include "farm/exit_question.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/window_text.h"
#include "engine/ui/digimon_list.h"
#include "engine/window/message_box.h"
#include "farm/data.h"
#include "farm/farm_groups.h"

/* Writes text of getFarmText in the window. */
void func_ov005_02292d5c(u8 window, s32 text) {
    func_020a6990(window, 1, 2, 0xB, 0xA, getFarmText(text), 0, 2, 0x100);
}

/* Loads the background of entry 100 of data_0213537c. */
void func_ov005_02292cfc(struct Task02292f48 *task) {
    struct BgGraphics gfx;

    func_02086df4(100, (s32 *) &gfx);
    task->bg = func_02085f34(&gfx, 3, 0xFFFF, 2, 0, 0, 0x20, 0x18, 0, 0);
}

/* Asks FARM_TEXTS 0x5D, "Exit DigiFarm?", leaving 1 in data_021e5ca4 for yes
 * and 0 for no. */
void askExitFarm(void) {
    struct Task02292b48 *task;

    findTask(FARM_TASK_ID);
    task = (struct Task02292b48 *) getCurrentTask();
    switch (task->state) {
        case 0:
            task->answer = -1;
            openFarmMessage(0x5D, 1, -1, 0xD, 8, 0);
            task->state = 500;
            break;
        case 500:
            task->answer = func_020ac6b8();
            if (task->answer != -1) {
                task->state = 10000;
            }
            break;
        case 10000:
            if (task->answer == 0) {
                data_021e5ca4 = 1;
            } else {
                data_021e5ca4 = 0;
            }
            func_020ac6f8();
            endTask(task);
            break;
    }
}
