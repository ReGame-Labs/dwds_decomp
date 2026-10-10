#include "engine/bg/bg_screen_task.h"
#include "engine/bg/bg_screen.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"

/* Frees a background's palette, character and screen files. A void pointer
 * for the callers that pass a u8 *. */
void freeBgGraphics(void *graphics) {
    struct BgGraphics *bg = graphics;
    void *file;

    file = bg->paletteFile;
    if (file != NULL) {
        heapFree(file);
        bg->paletteFile = NULL;
    }
    file = bg->charFile;
    if (file != NULL) {
        heapFree(file);
        bg->charFile = NULL;
    }
    file = bg->screenFile;
    if (file == NULL) {
        return;
    }
    heapFree(file);
    bg->screenFile = NULL;
}

/* Starts the task of tickBgScreen's screen, after setting up the display
 * (func_02041fe4), with the graphics of its two backgrounds. */
void startBgScreenTask(void *arg) {
    struct BgScreenTask *task;

    func_02041fe4();
    task              = createTask(tickBgScreen, 0x11B);
    BG_SCREEN_TASK_ID = getTaskId(task);
    BG_SCREEN_TASK    = task;
    task->task.onEnd  = freeBgScreenTask;
    task->arg         = arg;
    task->state       = 0;
    task->graphics    = heapAlloc(2 * sizeof(struct BgGraphics), 4);
    func_02030f18(task->graphics, 0, 2 * sizeof(struct BgGraphics));
}

/* The end of startBgScreenTask's task: frees its graphics' block. */
void freeBgScreenTask(void) {
    struct BgScreenTask *task = (struct BgScreenTask *) getCurrentTask();

    heapFree(task->graphics);
    BG_SCREEN_TASK_ID = -1;
    BG_SCREEN_TASK    = NULL;
}
