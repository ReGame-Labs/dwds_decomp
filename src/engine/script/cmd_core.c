#include "engine/script/cmd_core.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"
#include "engine/script/interpreter.h"
#include "engine/script/operand.h"
#include "engine/system/system.h"
#include "engine/ui/digimon_list.h"
#include "engine/ui/gauge.h"
#include "field/event_scripts/data.h"
#include "field/map/ov000_021fbb2c.h"

/* The value of a global script variable, given as its operand. */
s32 getScriptGlobal(s32 var) {
    return SCRIPT_GLOBALS[var - SCRIPT_GLOBAL_VAR_FIRST];
}

/* Whether a script thread is in use. */
s32 isScriptThreadUsed(s32 index) {
    s16 running;

    if (SCRIPT_THREADS[index].flags != 0) {
        running = TRUE;
    } else {
        running = FALSE;
    }
    return running;
}

/* Puts a script thread to sleep until another one wakes it. */
void suspendScriptThread(u8 thread) {
    sleepScriptThread(thread, -1);
}

/* Starts func_02094ec4's fade from level 0 down to -16. */
void func_02095044(void) {
    struct MapFadeTask *task;

    task              = createTask(func_02094ec4, 0xF000);
    task->state       = 0;
    task->wait        = 0;
    task->step        = -4;
    task->level       = 0;
    task->targetLevel = task->step * 4;
    task->thread      = 0xFF;
}

/* Shifts three palette ranges (func_020846bc) by level, a step every frame,
 * until it reaches its target, then wakes its thread. */
void func_02094f84(void) {
    struct MapFadeTask *task = (struct MapFadeTask *) getCurrentTask();

    switch (task->state) {
        case 0:
            func_ov000_021fbec0();
            task->state = 0x12C;
            return;
        case 0x12C:
            task->level = task->level + task->step;
            func_020846bc(0, 0x90, task->level);
            func_020846bc(0x900, 0x100, task->level);
            func_020846bc(0xA00, 0x800, task->level);
            markMainPalettesDirty();
            if (task->level == task->targetLevel) {
                task->state = 0x2710;
            }
            return;
        case 0x2710:
            func_ov000_021fc028();
            if (task->thread != 0xFF) {
                wakeScriptThread(task->thread);
            }
            endTask(task);
            return;
    }
}

/* The same with func_020845e4, the other screen's version of func_020846bc. */
void func_02094ec4(void) {
    struct MapFadeTask *task = (struct MapFadeTask *) getCurrentTask();

    switch (task->state) {
        case 0:
            func_ov000_021fbe88();
            task->state = 0x12C;
            return;
        case 0x12C:
            task->level = task->level + task->step;
            func_020845e4(0, 0x90, task->level);
            func_020845e4(0x900, 0x100, task->level);
            func_020845e4(0xA00, 0x800, task->level);
            markSubPalettesDirty();
            if (task->level == task->targetLevel) {
                task->state = 0x2710;
            }
            return;
        case 0x2710:
            func_ov000_021fbef8();
            if (task->thread != 0xFF) {
                wakeScriptThread(task->thread);
            }
            endTask(task);
            return;
    }
}

/* Starts func_02094ec4's fade from level -16 back up to 0. */
void func_02094e74(void) {
    struct MapFadeTask *task = createTask(func_02094ec4, 0xF000);

    task->state       = 0;
    task->wait        = 0;
    task->step        = 4;
    task->level       = task->step * -4;
    task->targetLevel = 0;
    task->thread      = 0xFF;
}

/* Calls isMainPaletteEffectRunning with -1 and drops its result. */
void func_02094e64(void) {
    isMainPaletteEffectRunning(-1);
}

/* Sets a script thread's sub screen sprite. */
void setScriptThreadSubSprite(u8 index, s16 sprite) {
    getScriptThread(index)->subSprite = sprite;
}

/* Command 0x00: jumps back by the operand and waits for the next frame. */
s32 cmdJumpBackAndWait(struct ScriptThread *thread) {
    thread->pc -= *thread->pc;
    return 0;
}

/* Command 0x01: jumps ahead by the operand and waits for the next frame. */
s32 cmdJumpAheadAndWait(struct ScriptThread *thread) {
    thread->pc += *thread->pc;
    return 0;
}

/* Command 0xC0: jumps ahead and waits for the next frame if a local variable
 * holds a value. */
s32 func_02094d64(struct ScriptThread *thread) {
    s32 index = resolveOperand(thread, thread->pc[1]);
    s32 value = resolveOperand(thread, thread->pc[2]);

    if (value == thread->vars[index]) {
        thread->pc += *thread->pc;
        return 0;
    }
    thread->pc += 3;
    return 1;
}

/* Command 0x154: jumps ahead and waits for the next frame if an event flag is
 * set. */
s32 cmdJumpAndWaitIfFlag(struct ScriptThread *thread) {
    if (getGameFlag(resolveOperand(thread, thread->pc[1])) != 0) {
        thread->pc += *thread->pc;
        return 0;
    }
    thread->pc += 2;
    return 1;
}

/* Command 0x07: jumps ahead by the operand. */
s32 cmdJumpAhead(struct ScriptThread *thread) {
    thread->pc += *thread->pc;
    return 1;
}

/* Command 0x02: calls the script at an offset of the event scripts. */
s32 cmdCall(struct ScriptThread *thread) {
    s32 i;
    u16 *pc;

    for (i = 3; i > 0; i--) {
        thread->returnStack[i] = thread->returnStack[i - 1];
    }
    thread->returnStack[0] = thread->pc + 2;
    pc                     = thread->pc;
    thread->pc             = (u16 *) &EVENT_SCRIPTS[pc[0] + (pc[1] << 16)];
    return 1;
}

/* Command 0x03: returns from the latest call. */
s32 cmdReturn(struct ScriptThread *thread) {
    s32 i;

    thread->pc = thread->returnStack[0];
    for (i = 0; i < 3; i++) {
        thread->returnStack[i] = thread->returnStack[i + 1];
    }
    return 1;
}

/* Command 0x04: goes on at an offset of the event scripts. */
s32 cmdGoto(struct ScriptThread *thread) {
    u16 *pc;

    pc         = thread->pc;
    thread->pc = (u16 *) &EVENT_SCRIPTS[pc[0] + (pc[1] << 16)];
    return 1;
}

/* Command 0x138: makes another thread go on at an offset of the event
 * scripts. */
s32 cmdGotoInThread(struct ScriptThread *thread) {
    s16 index;
    s32 offset;

    index                           = readOperand(thread);
    offset                          = readScriptWord(thread);
    getScriptThread((u8) index)->pc = (u16 *) (offset + (s32) EVENT_SCRIPTS);
    return 1;
}

/* Command 0x05: sleeps for a number of frames. */
s32 cmdSleep(struct ScriptThread *thread) {
    sleepScriptThread(thread->index, readOperand(thread));
    return 0;
}

/* Command 0x08: draws a random number below the operand into unk1C. */
s32 cmdRandom(struct ScriptThread *thread) {
    thread->unk1C = getRandom(*thread->pc);
    thread->pc += 1;
    return 1;
}

/* Command 0x145: draws a random number below the first operand into the local
 * variable of the second. */
s32 func_02094b7c(struct ScriptThread *thread) {
    s16 range;
    s16 index;

    range               = readOperand(thread);
    index               = readOperand(thread);
    thread->vars[index] = getRandom((u16) range);
    return 1;
}

/* Command 0x09: sets an event flag. */
s32 cmdSetFlag(struct ScriptThread *thread) {
    setGameFlag(resolveOperand(thread, *thread->pc));
    thread->pc += 1;
    return 1;
}

/* Command 0x0A: clears an event flag. */
s32 cmdClearFlag(struct ScriptThread *thread) {
    clearGameFlag(resolveOperand(thread, *thread->pc));
    thread->pc += 1;
    return 1;
}

/* Command 0x0B: sets one of the thread's own flags. */
s32 cmdSetLocalFlag(struct ScriptThread *thread) {
    setBit(*thread->pc, thread->localFlags);
    thread->pc += 1;
    return 1;
}

/* Command 0x0C: clears one of the thread's own flags. */
s32 cmdClearLocalFlag(struct ScriptThread *thread) {
    clearBit(*thread->pc, thread->localFlags);
    thread->pc += 1;
    return 1;
}

/* Command 0x06: goes on if an event flag is in the state the operand's top
 * bit gives, and jumps ahead otherwise. */
s32 cmdJumpUnlessFlagIs(struct ScriptThread *thread) {
    u32 operand = thread->pc[1];
    u8 isSet    = getGameFlag((s16) (operand & 0x7FFF));

    if (isSet == (operand << 1) >> 16) {
        thread->pc += 2;
    } else {
        thread->pc += thread->pc[0];
    }
    return 1;
}

/* Command 0x0E: plays a BGM, or stops it for SCRIPT_BGM_STOP. */
s32 cmdPlayBgm(struct ScriptThread *thread) {
    s16 bgm;

    bgm = readOperand(thread);
    if (bgm == SCRIPT_BGM_STOP) {
        stopBgm();
    } else {
        playBgm(bgm);
    }
    return 1;
}

/* Command 0x0F: plays a sound (playSound); a negative one calls
 * stopSound. */
s32 cmdPlaySound(struct ScriptThread *thread) {
    s16 sound = resolveOperand(thread, *thread->pc);

    if (sound < 0) {
        stopSound(-sound);
    } else {
        playSound(sound);
    }
    thread->pc += 1;
    return 1;
}
