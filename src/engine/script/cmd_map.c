#include "engine/script/cmd_map.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"
#include "engine/script/interpreter.h"
#include "engine/script/operand.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/ui/gauge.h"
#include "engine/window/message_box.h"
#include "field/map/map.h"
#include "field/map/map_character.h"
#include "field/map/ov000_021fbb2c.h"
#include "title/title_menu.h"

/* Command 0x15: sets a local variable to a value. */
s32 cmdSetVar(struct ScriptThread *thread) {
    s16 index;

    index               = readOperand(thread);
    thread->vars[index] = readOperand(thread);
    return 1;
}

/* Command 0x16: goes on if a local variable compares with a value as the operand's high byte says (SCRIPT_COMPARE_*), else
 * jumps. */
s32 cmdJumpUnlessVarCompares(struct ScriptThread *thread) {
    s32 result;
    s16 *operands; /* signed: the comparisons are */
    u16 operand;

    operands = (s16 *) thread->pc;
    result   = 0;
    operand  = operands[1];
    switch (operand & 0xFF00) {
        case SCRIPT_COMPARE_EQUAL << 8:
            if (operands[2] == thread->vars[operand & 0xFF]) {
                result = 1;
            }
            break;
        case SCRIPT_COMPARE_LESS << 8:
            if (thread->vars[operand & 0xFF] < operands[2]) {
                result = 1;
            }
            break;
        case SCRIPT_COMPARE_GREATER << 8:
            if (thread->vars[operand & 0xFF] > operands[2]) {
                result = 1;
            }
            break;
        case SCRIPT_COMPARE_LESS_EQUAL << 8:
            if (thread->vars[operand & 0xFF] <= operands[2]) {
                result = 1;
            }
            break;
        case SCRIPT_COMPARE_GREATER_EQUAL << 8:
            if (thread->vars[operand & 0xFF] >= operands[2]) {
                result = 1;
            }
            break;
        case SCRIPT_COMPARE_NOT_EQUAL << 8:
            if (operands[2] != thread->vars[operand & 0xFF]) {
                result = 1;
            }
            break;
    }
    if (result == 1) {
        thread->pc += 3;
    } else {
        thread->pc += (u16) operands[0];
    }
    return 1;
}

/* Command 0x17: goes on if one of the buttons given is held, pressed, repeated, double tapped or released (SCRIPT_BUTTONS_*),
 * or, with SCRIPT_BUTTONS_EXACTLY, held alone; else jumps. */
s32 cmdJumpUnlessButtons(struct ScriptThread *thread) {
    s32 kind;
    s32 result;
    u16 held;
    u16 operand;
    u16 *pc;

    result  = 0;
    held    = getPadHeld();
    pc      = thread->pc;
    operand = pc[1];
    if ((operand & SCRIPT_BUTTONS_EXACTLY) && (held != (operand & 0x2FFF))) {
        thread->pc = pc + pc[0];
        return 1;
    }
    kind = operand & 0x7000;
    switch (kind) {
        case SCRIPT_BUTTONS_HELD:
            if (operand & getPadHeld()) {
                result = 1;
            }
            break;
        case SCRIPT_BUTTONS_PRESSED:
            if (operand & getPadPressed()) {
                result = 1;
            }
            break;
        case SCRIPT_BUTTONS_FAST_REPEAT:
            if (operand & getPadFastRepeat()) {
                result = 1;
            }
            break;
        case SCRIPT_BUTTONS_DOUBLE_TAP:
            if (operand & getPadDoubleTap()) {
                result = 1;
            }
            break;
        case SCRIPT_BUTTONS_RELEASED:
            if (operand & getPadReleased()) {
                result = 1;
            }
            break;
    }
    if (result == 1) {
        thread->pc += 2;
    } else {
        pc         = thread->pc;
        thread->pc = pc + pc[0];
    }
    return 1;
}

/* Command 0x18: waits until the thread's sprites end their curve move, then ends the thread. */
s32 cmdEndThread(struct ScriptThread *thread) {
    if (thread->curve.frame != -1) {
        thread->pc -= 1;
    } else {
        endScriptThread((u8) thread->index);
    }
    return 0;
}

/* Command 0x1C: func_ov000_021ff4f4 with three operands, then lockMainPalettes. */
s32 func_02094534(struct ScriptThread *thread) {
    s32 b;
    u16 a;

    a = resolveOperand(thread, thread->pc[0]);
    b = resolveOperand(thread, thread->pc[1]);
    func_ov000_021ff4f4(a, b, resolveOperand(thread, thread->pc[2]));
    lockMainPalettes();
    thread->pc += 3;
    return 1;
}

/* Command 0x1D: loadSubMap with three operands, then lockSubPalettes, unless event flag 0x3E9 is set. */
s32 func_020944b4(struct ScriptThread *thread) {
    u16 a;
    s32 b;

    if (getGameFlag(0x3E9) == 0) {
        a = resolveOperand(thread, thread->pc[0]);
        b = resolveOperand(thread, thread->pc[1]);
        loadSubMap(a, b, resolveOperand(thread, thread->pc[2]));
        lockSubPalettes();
    }
    thread->pc += 3;
    return 1;
}

/* Command 0x128: calls stopMainMapTask. */
s32 func_0209449c(struct ScriptThread *thread) {
    stopMainMapTask();
    return 1;
}

/* Command 0x129: calls stopSubMapTask. */
s32 func_02094484(struct ScriptThread *thread) {
    stopSubMapTask();
    return 1;
}

/* Command 0x12A: closes the message windows (func_020ac1f8, func_020ac1cc), calls func_020a3454(5), func_020aa340 and
 * func_020aa308, fades both screens in over 8 steps and frees the sprites. */
s32 func_02094398(struct ScriptThread *thread) {
    func_020ac1f8();
    func_020ac1cc();
    func_020a3454(5);
    func_020aa340(1, 0);
    func_020aa308(1, 0);
    fadeInMainPalette(0, 0x100, 0, 0, 8);
    fadeInMainPalette(0x900, 0x100, 0, 0, 8);
    fadeInMainPalette(0xA00, 0x300, 0, 0, 8);
    fadeInSubPalette(0, 0x100, 0, 0, 8);
    fadeInSubPalette(0x900, 0x100, 0, 0, 8);
    fadeInSubPalette(0xA00, 0x300, 0, 0, 8);
    freeMainSprites();
    freeSubSprites();
    return 1;
}

/* Command 0xFE: calls func_ov000_021fbd2c and clears event flag 0x3ED. */
s32 func_020941b4(struct ScriptThread *thread) {
    func_ov000_021fbd2c();
    clearGameFlag(0x3ED);
    return 1;
}

/* Command 0xF9: calls func_ov000_021fc028. */
s32 func_0209419c(struct ScriptThread *thread) {
    func_ov000_021fc028();
    return 1;
}

/* Command 0xFA: calls func_ov000_021fbef8, unless event flag 0x3E9 is set. */
s32 func_02094170(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        func_ov000_021fbef8();
    }
    return 1;
}

/* Command 0x1A: calls startMainMap. */
s32 func_02094158(struct ScriptThread *thread) {
    startMainMap();
    return 1;
}

/* Command 0x1B: calls startSubMap, unless event flag 0x3E9 is set. */
s32 func_0209412c(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        startSubMap();
    }
    return 1;
}

/* Command 0x1E: calls startMainMapSpriteTask. */
s32 func_02094114(struct ScriptThread *thread) {
    startMainMapSpriteTask();
    return 1;
}

/* Command 0xA5: calls startSubMapSpriteTask, unless event flag 0x3E9 is set. */
s32 func_020940e8(struct ScriptThread *thread) {
    if (getGameFlag(0x3E9) == 0) {
        startSubMapSpriteTask();
    }
    return 1;
}
