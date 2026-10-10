#include "field/map/map.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/display_modes.h"
#include "engine/system/setup.h"
#include "engine/system/system.h"
#include "field/map/data.h"
#include "field/map/map_task_end.h"
#include "field/map/ov000_021fbb2c.h"
#include "field/map/ov000_021fc674.h"

/* Clears the main screen's map state, with no task. */
void clearMainMapState(void) {
    setSystemSetUp(0);
    CLEAR(&MAIN_MAP_STATE, sizeof(struct MapState));
    func_02030f18(MAIN_MAP_STATE.unk50, -1, sizeof(MAIN_MAP_STATE.unk50));
    MAIN_MAP_STATE.taskId = -1;
    data_ov000_0220d860   = 0;
    data_ov000_0220d86c   = 0;
    func_02030f18(data_021ab808, -1, 0x20);
}

/* The same for the sub screen. */
void clearSubMapState(void) {
    setSystemSetUp(1);
    CLEAR(&SUB_MAP_STATE, sizeof(struct MapState));
    func_02030f18(SUB_MAP_STATE.unk50, -1, sizeof(SUB_MAP_STATE.unk50));
    SUB_MAP_STATE.taskId = -1;
    data_ov000_0220d868  = 0;
    data_ov000_0220d864  = 0;
    func_02030f18(data_021ab848, -1, 0x20);
}

/* Starts the main screen's map anew, its four backgrounds unscrolled. */
void startMainMap(void) {
    clearMainMapState();
    startMainMapTask();
    func_020a3454(1);
    setMainBgOffset(0, 0, 0);
    setMainBgOffset(1, 0, 0);
    setMainBgOffset(2, 0, 0);
    setMainBgOffset(3, 0, 0);
}

/* The same for the sub screen. */
void startSubMap(void) {
    clearSubMapState();
    startSubMapTask();
    func_020a3454(2);
    setSubBgOffset(0, 0, 0);
    setSubBgOffset(1, 0, 0);
    setSubBgOffset(2, 0, 0);
    setSubBgOffset(3, 0, 0);
}

/* Starts the main screen's map task, which frees the map when it ends. */
void startMainMapTask(void) {
    struct Task *task = createTask(tickMainMap, 0x116);

    MAIN_MAP_STATE.taskId = getTaskId(task);
    task->onEnd           = freeMainMap;
}

/* The same for the sub screen. */
void startSubMapTask(void) {
    struct Task *task = createTask(tickSubMap, 0x116);

    SUB_MAP_STATE.taskId = getTaskId(task);
    task->onEnd          = freeSubMap;
}

/* Ends the main screen's map task, if there is one. */
void stopMainMapTask(void) {
    if (MAIN_MAP_STATE.taskId == -1) {
        return;
    }
    endTaskById(MAIN_MAP_STATE.taskId);
    MAIN_MAP_STATE.taskId = -1;
}

/* The same for the sub screen. */
void stopSubMapTask(void) {
    if (SUB_MAP_STATE.taskId == -1) {
        return;
    }
    endTaskById(SUB_MAP_STATE.taskId);
    SUB_MAP_STATE.taskId = -1;
}
