#include "field/actors/actor_tasks.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "field/actors/actor_update.h"

/* Starts the task that runs and draws the main screen's actors, with
 * 0x300 blocks of the main screen's sprite VRAM for their graphics. */
void startMainActorTask(void) {
    struct Task *task;

    task          = createTask(func_020c5a8c, 0x11E);
    data_021e9cb0 = getTaskId(task);
    task->onEnd   = NULL;
    data_021e9c90 = 0x300;
    data_021e9ca8 = allocMainVram(4, 0x300);
}

/* Starts the task that runs and draws the sub screen's actors, with
 * 0x300 blocks of the sub screen's sprite VRAM for their graphics. */
void startSubActorTask(void) {
    struct Task *task;

    task          = createTask(func_020c5534, 0x11E);
    data_021e9cb4 = getTaskId(task);
    task->onEnd   = NULL;
    data_021e9c94 = 0x300;
    data_021e9cac = allocSubVram(4, 0x300);
}

/* Starts the task that runs and draws the main screen's actors, with
 * blocks blocks of the main screen's sprite VRAM for their graphics. */
void startMainActorTaskWithVram(s16 blocks) {
    struct Task *task;

    task          = createTask(func_020c5a8c, 0x11E);
    data_021e9cb0 = getTaskId(task);
    task->onEnd   = NULL;
    data_021e9c90 = blocks;
    data_021e9ca8 = allocMainVram(4, blocks);
}

/* Starts the task that runs and draws the sub screen's actors, with
 * blocks blocks of the sub screen's sprite VRAM for their graphics. */
void startSubActorTaskWithVram(s16 blocks) {
    struct Task *task;

    task          = createTask(func_020c5534, 0x11E);
    data_021e9cb4 = getTaskId(task);
    task->onEnd   = NULL;
    data_021e9c94 = blocks;
    data_021e9cac = allocSubVram(4, blocks);
}

/* Ends the task of the main screen's actors and frees their sprite VRAM. */
s32 endMainActorTask(void) {
    if (data_021e9cb0 == -1) {
        return data_021e9cb0;
    }
    endTaskById(data_021e9cb0);
    data_021e9cb0 = -1;
    return func_0208577c(4, (u16) data_021e9ca8);
}

/* Ends the task of the sub screen's actors and frees their sprite VRAM. */
s32 endSubActorTask(void) {
    if (data_021e9cb4 == -1) {
        return data_021e9cb4;
    }
    endTaskById(data_021e9cb4);
    data_021e9cb4 = -1;
    return func_02085710(4, (u16) data_021e9cac);
}
