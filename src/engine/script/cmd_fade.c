#include "engine/script/cmd_fade.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/script/cmd_core.h"
#include "engine/script/cmd_thread.h"
#include "engine/script/operand.h"
#include "engine/system/system.h"
#include "engine/ui/gauge.h"
#include "field/map/ov000_021fbb2c.h"

/* Command 0x98: fades the sub screen's palettes out (func_0208f668). */
s32 func_0208f6fc(struct ScriptThread *thread) {
    func_ov000_021fbec0();
    func_0208f668(0, 4);
    return 1;
}

/* Command 0x99: fades the main screen's palettes out (func_0208f5f8). */
s32 func_0208f6d8(struct ScriptThread *thread) {
    func_ov000_021fbe88();
    func_0208f5f8(0, 4);
    return 1;
}

/* Fades the sub screen's palettes out (fadeOutMainPalette). */
void func_0208f668(s16 interval, s16 step) {
    fadeOutMainPalette(0, 0x100, 0, interval, step);
    fadeOutMainPalette(0x900, 0x100, 0, interval, step);
    fadeOutMainPalette(0xA00, 0x300, 0, interval, step);
    data_021d8ca4 = 0;
}

/* Fades the main screen's palettes out (fadeOutSubPalette). */
void func_0208f5f8(s16 interval, s16 step) {
    fadeOutSubPalette(0, 0x100, 0, interval, step);
    fadeOutSubPalette(0x900, 0x100, 0, interval, step);
    fadeOutSubPalette(0xA00, 0x300, 0, interval, step);
    data_021d8ca0 = 0;
}

/* Command 0x165: command 0x98 at a given pace. */
s32 func_0208f5bc(struct ScriptThread *thread) {
    s16 interval;
    s16 step;

    interval = readOperand(thread);
    step     = readOperand(thread);
    func_ov000_021fbec0();
    func_0208f668(interval, step);
    return 1;
}

/* Command 0x166: command 0x99 at a given pace. */
s32 func_0208f580(struct ScriptThread *thread) {
    s16 interval;
    s16 step;

    interval = readOperand(thread);
    step     = readOperand(thread);
    func_ov000_021fbe88();
    func_0208f5f8(interval, step);
    return 1;
}

/* Command 0x13F: fades the sub screen's palettes out with three operands for
 * fadeOutMainPalette. */
s32 func_0208f4e4(struct ScriptThread *thread) {
    s16 a;
    s16 interval;
    s16 step;

    a             = readOperand(thread);
    interval      = readOperand(thread);
    step          = readOperand(thread);
    data_021d8ca4 = 0;
    func_ov000_021fbec0();
    fadeOutMainPalette(0, 0x100, a, interval, step);
    fadeOutMainPalette(0x900, 0x100, a, interval, step);
    fadeOutMainPalette(0xA00, 0x800, a, interval, step);
    return 1;
}

/* Command 0x140: the same on the main screen (fadeOutSubPalette). */
s32 func_0208f448(struct ScriptThread *thread) {
    s16 a;
    s16 interval;
    s16 step;

    a             = readOperand(thread);
    interval      = readOperand(thread);
    step          = readOperand(thread);
    data_021d8ca0 = 0;
    func_ov000_021fbe88();
    fadeOutSubPalette(0, 0x100, a, interval, step);
    fadeOutSubPalette(0x900, 0x100, a, interval, step);
    fadeOutSubPalette(0xA00, 0x800, a, interval, step);
    return 1;
}

/* Command 0x12E: starts func_02094f84's fade from level -16 up to 0, and sleeps until it is done. */
s32 func_0208f3ec(struct ScriptThread *thread) {
    struct MapFadeTask *task;

    task              = createTask(&func_02094f84, 0xF000);
    task->state       = 0;
    task->wait        = 0;
    task->step        = 4;
    task->level       = 0 - task->step * 4;
    task->targetLevel = 0;
    task->thread      = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x12F: starts func_02094ec4's fade from level -16 up to 0, and sleeps until it is done. */
s32 func_0208f390(struct ScriptThread *thread) {
    struct MapFadeTask *task;

    task              = createTask(&func_02094ec4, 0xF000);
    task->state       = 0;
    task->wait        = 0;
    task->step        = 4;
    task->level       = 0 - task->step * 4;
    task->targetLevel = 0;
    task->thread      = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x130: starts func_02094f84's fade from level 0 down to -16, and sleeps until it is done. */
s32 func_0208f338(struct ScriptThread *thread) {
    struct MapFadeTask *task;

    task              = createTask(&func_02094f84, 0xF000);
    task->state       = 0;
    task->wait        = 0;
    task->step        = -4;
    task->level       = 0;
    task->targetLevel = task->step * 4;
    task->thread      = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x131: starts func_02094ec4's fade from level 0 down to -16, and sleeps until it is done. */
s32 func_0208f2e0(struct ScriptThread *thread) {
    struct MapFadeTask *task;

    task              = createTask(&func_02094ec4, 0xF000);
    task->state       = 0;
    task->wait        = 0;
    task->step        = -4;
    task->level       = 0;
    task->targetLevel = task->step * 4;
    task->thread      = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x9A: waits until the sub screen's palette fades are done; after a
 * fade in, calls func_ov000_021fc028. */
s32 func_0208f28c(struct ScriptThread *thread) {
    if (isMainPaletteEffectRunning(-1) == 0) {
        if ((u8) data_021d8ca4 != 0) {
            data_021d8ca4 = 0;
            func_ov000_021fc028();
        }
        return 1;
    }
    thread->pc -= 1;
    return 0;
}

/* Command 0x9B: the same on the main screen, with func_ov000_021fbef8. */
s32 func_0208f238(struct ScriptThread *thread) {
    if (isSubPaletteEffectRunning(-1) == 0) {
        if ((u8) data_021d8ca0 != 0) {
            data_021d8ca0 = 0;
            func_ov000_021fbef8();
        }
        return 1;
    }
    thread->pc -= 1;
    return 0;
}

/* Wakes its thread once bit 2 of data_021d8cb8 is clear. */
void func_0208f030(void) {
    struct ThreadWaitTask *task;

    task = (struct ThreadWaitTask *) getCurrentTask();
    if (data_021d8cb8 & 4) {
        return;
    }
    wakeScriptThread(task->thread);
    endTask(task);
}

/* Wakes its thread once bit 3 of data_021d8cb8 is clear. */
void func_0208eff8(void) {
    struct ThreadWaitTask *task;

    task = (struct ThreadWaitTask *) getCurrentTask();
    if (data_021d8cb8 & 8) {
        return;
    }
    wakeScriptThread(task->thread);
    endTask(task);
}

/* Command 0xAA: closes the message of the first message window, if one is
 * showing, and sleeps until its task has ended (func_0208eebc). */
s32 func_0208ef8c(struct ScriptThread *thread) {
    if (!(data_021d8cb8 & 1)) {
        return 1;
    }
    ((struct MessageWindowTask *) findTask(data_021e33d8))->state         = 0x2710;
    ((struct ThreadWaitTask *) createTask(&func_0208eebc, 0x105))->thread = (u16) thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0xAB: the same for the second message window (func_0208ee58). */
s32 func_0208ef20(struct ScriptThread *thread) {
    if (!(data_021d8cb8 & 2)) {
        return 1;
    }
    ((struct MessageWindowTask *) findTask(data_021e33dc))->state         = 0x2710;
    ((struct ThreadWaitTask *) createTask(&func_0208ee58, 0x105))->thread = (u16) thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Once the first message window's task has ended, wakes its thread and clears
 * event flags 0x3F5, 0x3F4, 0x3F2 and 0x3F6. */
void func_0208eebc(void) {
    struct ThreadWaitTask *task;

    task = (struct ThreadWaitTask *) getCurrentTask();
    if (data_021e33d8 != 0) {
        return;
    }
    wakeScriptThread(task->thread);
    endTask(task);
    clearGameFlag(0x3F5);
    clearGameFlag(0x3F4);
    clearGameFlag(0x3F2);
    clearGameFlag(0x3F6);
}

/* The same for the second message window. */
void func_0208ee58(void) {
    struct ThreadWaitTask *task;

    task = (struct ThreadWaitTask *) getCurrentTask();
    if (data_021e33dc != 0) {
        return;
    }
    wakeScriptThread(task->thread);
    endTask(task);
    clearGameFlag(0x3F5);
    clearGameFlag(0x3F4);
    clearGameFlag(0x3F2);
    clearGameFlag(0x3F6);
}
