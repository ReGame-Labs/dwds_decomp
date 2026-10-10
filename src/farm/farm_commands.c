#include "farm/farm_commands.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "engine/system/system.h"
#include "farm/farm_task.h"

/* The id of the first record whose func_020a2c9c bits have any of mask's. */
s32 func_020b35cc(s32 mask) {
    s32 i;
    struct Digimon *digimon;

    for (i = 0; i < 40; i++) {
        digimon = getDigimonAt(i);
        if (digimon->id != 0 && (mask & func_020a2c9c(digimon))) {
            return digimon->id;
        }
    }
    return 0;
}

/* Starts the farm's main task (tickFarmTask) on the group in the slot;
 * cmdRestoreBgm starts it on the first group in the order. */
void startFarmTask(s16 slot) {
    struct FarmTask *task = createTask(tickFarmTask, 0x10F);

    FARM_TASK_ID = getTaskId(task);
    task->state  = 0;
    task->slot   = slot;
}
