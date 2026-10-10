#ifndef ENGINE_SCRIPT_CMD_MAP_H
#define ENGINE_SCRIPT_CMD_MAP_H

/* The script engine's flow and map commands: local variable compares, button
 * jumps, the end of a thread, the map's start and end, and a reset of the
 * screens. */

#include "types.h"

struct ScriptThread;

/* Command 0x16's comparisons, in its operand's high byte. */
enum ScriptCompare {
    SCRIPT_COMPARE_EQUAL,
    SCRIPT_COMPARE_LESS,
    SCRIPT_COMPARE_GREATER,
    SCRIPT_COMPARE_LESS_EQUAL,
    SCRIPT_COMPARE_GREATER_EQUAL,
    SCRIPT_COMPARE_NOT_EQUAL,
};

/* Command 0x17's tests, in its operand's top bits; the buttons are its low
 * bits. */
enum ScriptButtonTest {
    SCRIPT_BUTTONS_HELD        = 0x0000,
    SCRIPT_BUTTONS_PRESSED     = 0x1000,
    SCRIPT_BUTTONS_FAST_REPEAT = 0x2000,
    SCRIPT_BUTTONS_DOUBLE_TAP  = 0x3000,
    SCRIPT_BUTTONS_RELEASED    = 0x4000,
    SCRIPT_BUTTONS_EXACTLY     = 0x8000, /* jumps unless only these are held */
};

s32 func_02094114(struct ScriptThread *thread);
s32 func_02094158(struct ScriptThread *thread);
s32 func_0209419c(struct ScriptThread *thread);
s32 func_020941b4(struct ScriptThread *thread);
s32 func_02094398(struct ScriptThread *thread);
s32 func_02094484(struct ScriptThread *thread);
s32 func_0209449c(struct ScriptThread *thread);
s32 cmdEndThread(struct ScriptThread *thread);
s32 cmdJumpUnlessButtons(struct ScriptThread *thread);
s32 func_02094534(struct ScriptThread *thread);
s32 cmdSetVar(struct ScriptThread *thread);
s32 func_020940e8(struct ScriptThread *thread);
s32 func_0209412c(struct ScriptThread *thread);
s32 func_02094170(struct ScriptThread *thread);
s32 cmdJumpUnlessVarCompares(struct ScriptThread *thread);
s32 func_020944b4(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_MAP_H */
