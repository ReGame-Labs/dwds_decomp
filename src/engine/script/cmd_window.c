#include "engine/script/cmd_window.h"
#include "engine/data.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/script/cmd_core.h"
#include "engine/script/cmd_screen.h"
#include "engine/script/operand.h"
#include "engine/system/system.h"
#include "field/event_scripts/data.h"

/* The task of command 0x11A: slides in the window of data_021d8cb0. */
void func_02089f28(void) {
    func_02089d10(getCurrentTask(), &data_021d8cb0);
}

/* The task of command 0x11B: slides in the window of data_021d8c9c. */
void func_02089f08(void) {
    func_02089d10(getCurrentTask(), &data_021d8c9c);
}

/* The two commands below slide the window out (mode 0-3), if there is one, and
 * sleep until it is gone. */
/* Command 0x11C: the window of data_021d8cb0. */
s32 func_02089c74(struct ScriptThread *thread) {
    s16 mode = readOperand(thread);
    struct WindowSlideTask *task;

    if (data_021d8cb0 != -1) {
        task = createTask(func_02089bb0, 0x107);
        if (mode == 0) {
            task->state = 500;
        }
        if (mode == 1) {
            task->state = 600;
        }
        if (mode == 2) {
            task->state = 700;
        }
        if (mode == 3) {
            task->state = 800;
        }
        task->thread = thread->index;
        suspendScriptThread(thread->index);
        return 0;
    }
    return 1;
}

/* Command 0x11D: the window of data_021d8c9c. */
s32 func_02089bd8(struct ScriptThread *thread) {
    s16 mode = readOperand(thread);
    struct WindowSlideTask *task;

    if (data_021d8c9c != -1) {
        task = createTask(func_02089b88, 0x107);
        if (mode == 0) {
            task->state = 500;
        }
        if (mode == 1) {
            task->state = 600;
        }
        if (mode == 2) {
            task->state = 700;
        }
        if (mode == 3) {
            task->state = 800;
        }
        task->thread = thread->index;
        suspendScriptThread(thread->index);
        return 0;
    }
    return 1;
}

/* Command 0x11C's task: slides out the window of data_021d8cb0. */
void func_02089bb0(void) {
    func_020899a0(getCurrentTask(), &data_021d8cb0, &data_021d8c94);
}

/* Command 0x11D's task: slides out the window of data_021d8c9c. */
void func_02089b88(void) {
    func_020899a0(getCurrentTask(), &data_021d8c9c, &data_021d8c90);
}

/* The two commands below free the entry held in data_021d8c98 / data_021d8cac
 * and create a new one from five operands. The operands are named after the
 * fields func_02083d9c stores them in; unk4 sets the entry's kind (by sign and
 * +-10000) and scales the value it stores at 0x4. */
/* Command 0x120: the entry of data_021d8c98 (func_02083ea8). */
s32 func_02089754(struct ScriptThread *thread) {
    s16 unk8  = readOperand(thread);
    s16 unkA  = readOperand(thread);
    s16 unk1  = readOperand(thread);
    s16 unk10 = readOperand(thread);
    s16 unk4  = readOperand(thread);

    if (data_021d8c98 != -1) {
        stopMainPaletteEffects(data_021d8c98);
    }
    data_021d8c98 = func_02083ea8(unk8, unkA, unk1, unk10, unk4);
    return 1;
}

/* Command 0x121: the entry of data_021d8cac (func_02083e78). */
s32 func_020896c8(struct ScriptThread *thread) {
    s16 unk8  = readOperand(thread);
    s16 unkA  = readOperand(thread);
    s16 unk1  = readOperand(thread);
    s16 unk10 = readOperand(thread);
    s16 unk4  = readOperand(thread);

    if (data_021d8cac != -1) {
        stopSubPaletteEffects(data_021d8cac);
    }
    data_021d8cac = func_02083e78(unk8, unkA, unk1, unk10, unk4);
    return 1;
}

/* Command 0x122: frees the entry of data_021d8c98, if there is one. */
s32 func_0208968c(struct ScriptThread *thread) {
    if (data_021d8c98 != -1) {
        stopMainPaletteEffects(data_021d8c98);
    }
    data_021d8c98 = -1;
    return 1;
}

/* Command 0x123: frees the entry of data_021d8cac, if there is one. */
s32 func_02089650(struct ScriptThread *thread) {
    if (data_021d8cac != -1) {
        stopSubPaletteEffects(data_021d8cac);
    }
    data_021d8cac = -1;
    return 1;
}

/* Makes thread go on at offset into the script file. */
void jumpToScriptOffset(struct ScriptThread *thread, s32 offset) {
    /* An integer sum: as pointer arithmetic, mwcc would add the base first. */
    thread->pc = (u16 *) (offset + (u32) EVENT_SCRIPTS);
}

/* Command 0x132: runs program number of data_02136684 and data_02136694. */
s32 func_02089604(struct ScriptThread *thread) {
    s16 number               = readOperand(thread);
    struct ProgramTask *task = createTask(func_020892a0, 0x107);

    task->state = 0;
    task->wait  = 0;
    task->index = number;
    return 0;
}
