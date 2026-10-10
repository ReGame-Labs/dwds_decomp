#include "engine/script/cmd_thread.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/script/cmd_core.h"
#include "engine/script/interpreter.h"
#include "engine/script/operand.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/window/choice_dialog.h"
#include "engine/window/dialogue_window.h"
#include "field/event_scripts/data.h"

/* Command 0x33: goes on if a global variable shares a bit with a value, and
 * jumps ahead otherwise. The variable is the operand's low 12 bits, not an
 * operand of the globals' range, so the read lands past the globals. */
s32 func_0208ff08(struct ScriptThread *thread) {
    u16 *pc;
    s16 var;
    s32 value;

    pc    = thread->pc;
    var   = pc[1] & 0xFFF;
    value = resolveOperand(thread, (s16) pc[2]);
    if (value & SCRIPT_GLOBALS[var - SCRIPT_GLOBAL_VAR_FIRST]) {
        thread->pc += 3;
    } else {
        thread->pc += *thread->pc;
    }
    return 1;
}

/* Command 0x34: the same, going on if the value or the variable is nonzero. */
s32 func_0208fe94(struct ScriptThread *thread) {
    u16 *pc;
    s16 var;
    s32 value;

    pc    = thread->pc;
    var   = pc[1] & 0xFFF;
    value = resolveOperand(thread, (s16) pc[2]);
    if (value | SCRIPT_GLOBALS[var - SCRIPT_GLOBAL_VAR_FIRST]) {
        thread->pc += 3;
    } else {
        thread->pc += *thread->pc;
    }
    return 1;
}

/* Command 0x35: jumps ahead and waits for the next frame if the variable
 * holds a value, read as by command 0x33. */
s32 func_0208fe14(struct ScriptThread *thread) {
    u16 *pc   = thread->pc;
    s16 var   = pc[1] & 0xFFF;
    s32 value = resolveOperand(thread, (s16) pc[2]);

    if (value == SCRIPT_GLOBALS[var - SCRIPT_GLOBAL_VAR_FIRST]) {
        thread->pc += *thread->pc;
        return 0;
    }
    thread->pc += 3;
    return 1;
}

/* Command 0x8C: draws a random number below the second operand into the local
 * variable of the first. */
s32 func_0208fdd8(struct ScriptThread *thread) {
    s16 var;

    var               = readOperand(thread);
    thread->vars[var] = getRandom((u16) readOperand(thread));
    return 1;
}

/* Command 0x8D: starts func_020a7bac's task with two operands and sleeps until
 * it ends (func_0208fc90). */
s32 func_0208fd5c(struct ScriptThread *thread) {
    s16 a = readOperand(thread);
    s16 b = readOperand(thread);
    struct ThreadWaitTask *task;

    func_020a7bac(a, 0xFFFF, 0xFFFF, b, 0);
    task         = createTask(func_0208fc90, 0xF000);
    task->state  = 0;
    task->thread = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x8F: the same with a third operand, given plus one. */
s32 func_0208fccc(struct ScriptThread *thread) {
    s16 a = readOperand(thread);
    s16 b = readOperand(thread);
    s16 c = readOperand(thread);
    struct ThreadWaitTask *task;

    func_020a7bac(a, 0xFFFF, 0xFFFF, b, c + 1);
    task         = createTask(func_0208fc90, 0xF000);
    task->state  = 0;
    task->thread = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Wakes its thread once func_020a7bac's task has ended. */
void func_0208fc90(void) {
    struct ThreadWaitTask *task;

    task = (struct ThreadWaitTask *) getCurrentTask();
    if (func_020a7538() != 0) {
        return;
    }
    wakeScriptThread(getScriptThread((u8) task->thread)->index);
    endTask(task);
}

/* Frees command 0x8E's main screen sprite once its frames are over, and wakes
 * the thread. */
void func_0208fae8(void) {
    struct TimedSpriteTask *task;

    task         = (struct TimedSpriteTask *) getCurrentTask();
    task->frames = task->frames - 1;
    if ((s32) task->frames >= 1) {
        return;
    }
    freeMainSprite(task->sprite);
    wakeScriptThread(getScriptThread((u8) task->thread)->index);
    endTask(task);
}

/* The same for command 0xCF's sub screen sprite. */
void func_0208fa98(void) {
    struct TimedSpriteTask *task;

    task         = (struct TimedSpriteTask *) getCurrentTask();
    task->frames = task->frames - 1;
    if ((s32) task->frames >= 1) {
        return;
    }
    freeSubSprite(task->sprite);
    wakeScriptThread(getScriptThread((u8) task->thread)->index);
    endTask(task);
}

/* Command 0x90: starts a thread on the script at an offset of the event
 * scripts. A thread after this one sleeps a frame, so that it doesn't run in
 * this frame's pass too. */
s32 cmdStartThread(struct ScriptThread *thread) {
    s16 index;

    index = startScriptThread((u16 *) &EVENT_SCRIPTS[readScriptWord(thread)], 0);
    if (thread->index < index) {
        sleepScriptThread(index, 1);
    }
    return 1;
}

/* Command 0x91: starts a thread and puts its index into a local variable. The
 * thread starts at the operand itself, not at an offset of the event
 * scripts. */
s32 func_0208fa20(struct ScriptThread *thread) {
    s32 var;
    s32 pc;

    pc                = readScriptWord(thread);
    var               = readOperand(thread);
    thread->vars[var] = startScriptThread((u16 *) pc, 0);
    return 1;
}

/* Command 0x92: starts a child thread on the script at an offset of the event
 * scripts, as command 0x90. */
s32 cmdStartChildThread(struct ScriptThread *thread) {
    u8 index;
    s16 i;
    struct ScriptThread *child;

    index = startScriptThread((u16 *) &EVENT_SCRIPTS[readScriptWord(thread)], 0);
    i     = 0;
    child = &SCRIPT_THREADS[index];
    while (1) {
        if (thread->children[i] == 0xFF) {
            break;
        }
        i++;
    }
    thread->children[i] = index;
    child->parent       = thread->index;
    if (thread->index < index) {
        sleepScriptThread(index, 1);
    }
    return 1;
}

/* Command 0x94: waits until a child slot is free, its thread ended. */
s32 cmdWaitForChildSlot(struct ScriptThread *thread) {
    if (thread->children[readOperand(thread)] != 0xFF) {
        thread->pc -= 2;
        return 0;
    }
    return 1;
}

/* Command 0x95: waits until a thread is in use. */
s32 func_0208f8a8(struct ScriptThread *thread) {
    if (isScriptThreadUsed((u8) readOperand(thread)) != 1) {
        thread->pc -= 2;
        return 0;
    }
    return 1;
}

/* Command 0x96: fades the sub screen's palettes in. */
s32 func_0208f888(struct ScriptThread *thread) {
    func_0208f7f8(0, 4);
    return 1;
}

/* Command 0x97: fades the main screen's palettes in. */
s32 func_0208f868(struct ScriptThread *thread) {
    func_0208f788(0, 4);
    return 1;
}

/* Fades the sub screen's palettes in (fadeInMainPalette). */
void func_0208f7f8(s16 interval, s16 step) {
    fadeInMainPalette(0, 0x100, 0, interval, step);
    fadeInMainPalette(0x900, 0x100, 0, interval, step);
    fadeInMainPalette(0xA00, 0x310, 0, interval, step);
    data_021d8ca4 = 1;
}

/* Fades the main screen's palettes in (fadeInSubPalette). */
void func_0208f788(s16 interval, s16 step) {
    fadeInSubPalette(0, 0x100, 0, interval, step);
    fadeInSubPalette(0x900, 0x100, 0, interval, step);
    fadeInSubPalette(0xA00, 0x310, 0, interval, step);
    data_021d8ca0 = 1;
}

/* Command 0x163: fades the sub screen's palettes in at a given pace. */
s32 func_0208f754(struct ScriptThread *thread) {
    s16 interval;

    interval = readOperand(thread);
    func_0208f7f8(interval, readOperand(thread));
    return 1;
}

/* Command 0x164: fades the main screen's palettes in at a given pace. */
s32 func_0208f720(struct ScriptThread *thread) {
    s16 interval;

    interval = readOperand(thread);
    func_0208f788(interval, readOperand(thread));
    return 1;
}
