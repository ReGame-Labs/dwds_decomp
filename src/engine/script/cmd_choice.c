#include "engine/script/cmd_choice.h"
#include "engine/data.h"
#include "engine/script/cmd_window.h"
#include "engine/script/operand.h"
#include "engine/ui/gauge.h"
#include "field/actors/actor_commands.h"
#include "m2c_macros.h"

/* Command 0xCD: clears event flags 0x3F8, 0x3F9 and 0x3ED and calls
 * func_020c22b8 and unfreezeMainActor on the actors 0-3. */
s32 func_0208bf80(struct ScriptThread *thread) {
    clearGameFlag(0x3F8);
    clearGameFlag(0x3F9);
    clearGameFlag(0x3ED);
    func_020c22b8(0);
    unfreezeMainActor(1);
    unfreezeMainActor(2);
    unfreezeMainActor(3);
    return 1;
}

/* Command 0xCE: the same with func_020c22a8 and unfreezeSubActor. */
s32 func_0208bf2c(struct ScriptThread *thread) {
    clearGameFlag(0x3F8);
    clearGameFlag(0x3F9);
    clearGameFlag(0x3ED);
    func_020c22a8(0);
    unfreezeSubActor(1);
    unfreezeSubActor(2);
    unfreezeSubActor(3);
    return 1;
}

/* Command 0x107: goes on if data_021de5f8's byte at 0xE34 is at least the
 * operand, and jumps ahead otherwise. */
s32 func_0208bee4(struct ScriptThread *thread) {
    if ((s32) M2C_FIELD(&data_021de5f8, u8 *, 0xE34) >= resolveOperand(thread, thread->pc[1])) {
        thread->pc += 2;
    } else {
        thread->pc += *thread->pc;
    }
    return 1;
}

/* Command 0x12D: goes on at an offset of the event scripts if two operands
 * are equal. */
s32 func_0208be30(struct ScriptThread *thread) {
    s32 offset;
    s16 a;

    offset = readScriptWord(thread);
    a      = readOperand(thread);
    if (a == readOperand(thread)) {
        jumpToScriptOffset(thread, offset);
    }
    return 1;
}
