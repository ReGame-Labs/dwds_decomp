#include "engine/script/cmd_wait.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/script/cmd_core.h"
#include "engine/script/interpreter.h"
#include "engine/script/operand.h"
#include "engine/sprite/sprite.h"
#include "engine/system/system.h"
#include "engine/ui/gauge.h"
#include "farm/farms.h"

/* Command 0xF5: sets a local variable of a child thread. */
s32 func_0208de80(struct ScriptThread *thread) {
    s16 slot;
    s16 var;
    s16 value;
    struct ScriptThread *child;

    slot  = readOperand(thread);
    var   = readOperand(thread);
    value = readOperand(thread);
    child = getScriptThread(thread->children[slot]);
    if (child != NULL) {
        child->vars[var] = value;
    }
    return 1;
}

/* Command 0xF6: copies a local variable of a child thread into one of this
 * thread. Its third operand is read and dropped. */
s32 func_0208de28(struct ScriptThread *thread) {
    s16 slot;
    s16 var;
    s16 childVar;
    struct ScriptThread *child;

    slot     = readOperand(thread);
    childVar = readOperand(thread);
    readOperand(thread);
    var   = readOperand(thread);
    child = getScriptThread(thread->children[slot]);
    if (child != NULL) {
        thread->vars[var] = child->vars[childVar];
    }
    return 1;
}

/* Command 0x167: goes on if the farms have fewer than 50 goods, and jumps
 * ahead otherwise. */
s32 func_0208dd4c(struct ScriptThread *thread) {
    u16 *pc;

    if (countPlayerGoods() < 50) {
        thread->pc += 1;
    } else {
        pc         = thread->pc;
        thread->pc = pc + *pc;
    }
    return 1;
}

/* Command 0xAE: waits until one of the given buttons is pressed. */
s32 func_0208dd14(struct ScriptThread *thread) {
    u16 buttons;

    buttons = (u16) readOperand(thread);
    if (!(buttons & getPadPressed())) {
        thread->pc -= 2;
    }
    return 0;
}

/* Command 0xFB: waits until an event flag is in a given state. */
s32 func_0208dcd8(struct ScriptThread *thread) {
    s16 flag;
    s16 state;

    flag  = readOperand(thread);
    state = readOperand(thread);
    if (state != getGameFlag(flag)) {
        thread->pc -= 3;
    }
    return 0;
}

/* Command 0xAF: puts a child thread to sleep until woken. */
s32 func_0208dcb4(struct ScriptThread *thread) {
    suspendScriptThread(thread->children[(u16) readOperand(thread)]);
    return 1;
}

/* Command 0xB0: wakes a child thread. */
s32 func_0208dc90(struct ScriptThread *thread) {
    wakeScriptThread(thread->children[(u16) readOperand(thread)]);
    return 1;
}

/* Command 0xB1: pauseMainPaletteEffects with -1. */
s32 func_0208dc74(struct ScriptThread *thread) {
    pauseMainPaletteEffects(-1);
    return 1;
}

/* Command 0xB2: pauseSubPaletteEffects with -1. */
s32 func_0208dc58(struct ScriptThread *thread) {
    pauseSubPaletteEffects(-1);
    return 1;
}

/* Command 0xB3: resumeMainPaletteEffects with -1. */
s32 func_0208dc3c(struct ScriptThread *thread) {
    resumeMainPaletteEffects(-1);
    return 1;
}

/* Command 0xB4: resumeSubPaletteEffects with -1. */
s32 func_0208dc20(struct ScriptThread *thread) {
    resumeSubPaletteEffects(-1);
    return 1;
}

/* Command 0xB9: puts the thread's sprites at a point. */
s32 func_0208d8b8(struct ScriptThread *thread) {
    s16 x;
    s16 y;

    x = readOperand(thread);
    y = readOperand(thread);
    if (thread->mainSprite != 0xFFFF) {
        setMainSpritePos(thread->mainSprite, x, y);
    }
    if (thread->subSprite != 0xFFFF) {
        setSubSpritePos(thread->subSprite, x, y);
    }
    return 1;
}
