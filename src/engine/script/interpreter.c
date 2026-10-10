#include "engine/script/interpreter.h"
#include "eggs/egg_hatch.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "field/event_scripts/data.h"
#include "link/farm_visit.h"

/* Whether the field popup of func_02095c4c (system flag 0xE) is open. */
BOOL func_0209585c(void) {
    if (getUiFlag(0xE) != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Closes the field popup of func_02095c4c: its window, sprites, buttons and
 * font. */
void func_020957f0(void) {
    struct FieldPopupTask *task;

    if (getUiFlag(0xE) == 0) {
        return;
    }
    task = findTask(data_021da400);
    func_020957b0(task->window, task->sprites);
    closeButtonGroup(task->buttons);
    closeWindow(task->window);
    releaseGfxSlot(task->font);
    endTask(task);
    data_021da400 = 0;
    clearUiFlag(0xE);
}

/* Calls func_020a2c9c with func_0209a5d8's result for a Digimon id. */
void func_02095798(s32 id) {
    func_020a2c9c((void *) func_0209a5d8(id));
}

/* The farm (0-3) a Digimon is on, or -1. */
s32 func_02095728(s32 id) {
    s32 i;
    s32 j;
    struct Farm *group;

    if (id == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        group = (struct Farm *) func_0209a220(i); /* declared u8 * by its header */
        if (group == NULL) {
            return -1;
        }
        for (j = 0; j < 8 && group->digimon[j] != 0; j++) {
            if (id == group->digimon[j]) {
                return i;
            }
        }
    }
    return -1;
}

/* Pauses the script task: tickScripts runs no thread until resumed. */
void pauseScripts(void) {
    struct ScriptTask *task = findTask(SCRIPT_TASK);

    task->state = 0x1F4;
}

/* Resumes the paused script task, loading the event scripts' overlay again. */
void resumeScripts(void) {
    struct ScriptTask *task;

    task = findTask(SCRIPT_TASK);
    if (task->state != 0x1F4) {
        return;
    }
    loadOverlay(1);
    task->state = 0x12C;
}

/* Starts a thread on an event script, searching for a free thread from 0. */
u8 startEventScript(s32 script) {
    return startEventScriptFrom(script, 0);
}

/* The index of the event script at an offset. */
s32 findEventScript(s32 offset) {
    s32 i;

    for (i = 0;; i++) {
        if (offset == ((s32 *) EVENT_SCRIPTS)[i]) {
            break;
        }
    }
    return i;
}

/* The offset of an event script in the event scripts. */
s32 getEventScriptOffset(s32 index) {
    return ((s32 *) EVENT_SCRIPTS)[index];
}

/* A script thread, or NULL for an index of 16 and up. */
struct ScriptThread *getScriptThread(u32 index) {
    if (index < 16) {
        return &SCRIPT_THREADS[index];
    }
    return NULL;
}
