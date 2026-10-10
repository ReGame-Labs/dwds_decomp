#include "battle/characters/move_script.h"
#include "battle/characters/data.h"
#include "battle/characters/fade_sprite_slot.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/setup.h"
#include "engine/system/system.h"

/* Sets up the move scripts, once until freeMoveScript ends them. */
void initMoveScripts(void) {
    if (isSystemSetUp(8) != 0) {
        return;
    }
    setSystemSetUp(8);
    MOVE_SCRIPT_TASK_ID = -1;
    MOVE_SCRIPT_TASK    = NULL;
    MOVE_SCRIPT_FILE    = NULL;
    FADE_TASK           = NULL;
    FADE_LEVEL          = 0;
    data_ov001_0222b204 = 0;
    data_ov001_0222b20c = 0;
    data_ov001_0222b200 = 0;
    data_ov001_0222b1fc = 0;
}

/* The script task's end: frees the script's file. */
void freeMoveScript(void) {
    void *file;

    file                = MOVE_SCRIPT_FILE;
    MOVE_SCRIPT_TASK_ID = -1;
    MOVE_SCRIPT_TASK    = NULL;
    if (file != NULL) {
        /* The second test is the freeing function's own, inlined. */
        heapFree(file);
        MOVE_SCRIPT_FILE = NULL;
    }
    clearSystemSetUp(8);
}

/* Runs script, for length halfwords or, for MOVE_SCRIPT_UNTIL_END, until it
 * ends itself; nothing while one runs already. */
void startMoveScriptTask(s16 *script, u16 length) {
    struct MoveScriptTask *task;

    if (MOVE_SCRIPT_TASK != NULL) {
        return;
    }
    task                = createTask(tickMoveScriptTask, EFFECT_TASK_PRIORITY);
    MOVE_SCRIPT_TASK_ID = getTaskId(task);
    MOVE_SCRIPT_TASK    = task;
    task->script        = script;
    task->length        = length;
    task->pc            = 0;
    task->wait          = 0;
    task->task.onEnd    = freeMoveScript;
}

/* Ends the script task. */
void stopMoveScriptTask(void) {
    endTask(findTask(MOVE_SCRIPT_TASK_ID));
}

/* The script task: runs commands until one waits for the next frame, and ends
 * once past the script's length. */
void tickMoveScriptTask(void) {
    struct MoveScriptTask *task;

    task = (struct MoveScriptTask *) getCurrentTask();
    if (task->length <= task->pc) {
        stopMoveScriptTask();
        return;
    }
    while (runMoveScriptCommand() == 0) {
    }
}
