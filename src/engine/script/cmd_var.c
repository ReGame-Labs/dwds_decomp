#include "engine/script/cmd_var.h"
#include "engine/data.h"
#include "engine/script/cmd_core.h"
#include "engine/script/interpreter.h"
#include "engine/script/operand.h"
#include "engine/system/system.h"
#include "engine/text/text_args.h"
#include "engine/text/text_banks.h"
#include "engine/ui/gauge.h"
#include "items/inventory.h"

/* Command 0x169: starts func_020903f4's task with the operand, sleeps until it
 * wakes the thread and sets event flag 0x409. */
s32 func_02090760(struct ScriptThread *thread) {
    s16 value;
    struct Task020903f4 *task;

    value        = readOperand(thread);
    task         = createTask(&func_020903f4, 0x123);
    task->state  = 0;
    task->wait   = 0;
    task->value  = value;
    task->thread = thread->index;
    suspendScriptThread(thread->index);
    setGameFlag(0x409);
    return 0;
}

/* Command 0x109: takes one of an item away (addItem) and puts its name
 * into text argument 0. */
s32 func_020903b8(struct ScriptThread *thread) {
    u16 item;

    item = (u16) readOperand(thread);
    addItem(item, -1);
    setTextArg(0, func_0209d5f4((s16) item));
    return 1;
}

/* Command 0xC4: goes on if one more of an item fits (canAddItem), and
 * jumps ahead otherwise. */
s32 func_0209036c(struct ScriptThread *thread) {
    u16 *pc;

    if (canAddItem((u16) resolveOperand(thread, thread->pc[1]), 1) == 1) {
        thread->pc += 2;
    } else {
        pc         = thread->pc;
        thread->pc = pc + pc[0];
    }
    return 1;
}

/* Command 0xC5: goes on if having an item (hasItem) is as the second
 * operand says, nonzero for having it, and jumps ahead otherwise. */
s32 func_020902d0(struct ScriptThread *thread) {
    u16 item;
    u16 *pc;

    item = (u16) resolveOperand(thread, thread->pc[1]);
    if ((u16) resolveOperand(thread, thread->pc[2]) == 0) {
        if (hasItem((u32) item) == 0) {
            thread->pc += 3;
        } else {
            pc         = thread->pc;
            thread->pc = pc + pc[0];
        }
    } else if (hasItem((u32) item) == 1) {
        thread->pc += 3;
    } else {
        pc         = thread->pc;
        thread->pc = pc + pc[0];
    }
    return 1;
}

/* Command 0x2D: copies a global variable into a local one. The operand holds
 * the local's index in its top 4 bits and the global's in the rest. */
s32 cmdCopyGlobalToVar(struct ScriptThread *thread) {
    u16 operand;

    operand                             = *thread->pc;
    thread->vars[(s16) (operand >> 12)] = SCRIPT_GLOBALS[(s16) (operand & 0xFFF) - SCRIPT_GLOBAL_VAR_FIRST];
    thread->pc++;
    return 1;
}

/* Command 0x2E: sets a global variable. */
s32 cmdSetGlobal(struct ScriptThread *thread) {
    s16 var;
    u16 *pc;

    pc  = thread->pc;
    var = pc[0];
    setScriptGlobal(var, resolveOperand(thread, pc[1]));
    thread->pc += 2;
    return 1;
}

/* Command 0x2F: waits until a global variable holds a value. */
s32 cmdWaitForGlobal(struct ScriptThread *thread) {
    s16 *operands;
    s16 var;
    s32 value;

    operands = (s16 *) thread->pc;
    var      = operands[0];
    value    = resolveOperand(thread, operands[1]);
    if (value == SCRIPT_GLOBALS[var - SCRIPT_GLOBAL_VAR_FIRST]) {
        thread->pc += 2;
        return 1;
    }
    thread->pc -= 1;
    return 0;
}

/* Command 0x30: adds to a global variable. */
s32 cmdAddToGlobal(struct ScriptThread *thread) {
    s16 *operands;
    s16 var;

    operands = (s16 *) thread->pc;
    var      = operands[0];
    SCRIPT_GLOBALS[var - SCRIPT_GLOBAL_VAR_FIRST] += resolveOperand(thread, operands[1]);
    thread->pc += 2;
    return 1;
}

/* Command 0x31: subtracts from a global variable. */
s32 cmdSubtractFromGlobal(struct ScriptThread *thread) {
    s16 *operands;
    s16 var;

    operands = (s16 *) thread->pc;
    var      = operands[0];
    SCRIPT_GLOBALS[var - SCRIPT_GLOBAL_VAR_FIRST] -= resolveOperand(thread, operands[1]);
    thread->pc += 2;
    return 1;
}
