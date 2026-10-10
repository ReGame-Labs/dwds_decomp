#ifndef ENGINE_SCRIPT_CMD_VAR_H
#define ENGINE_SCRIPT_CMD_VAR_H

/* The script engine's commands on global variables and items. */

#include "engine/data.h"
#include "types.h"

/* The task of command 0x169, run by func_020903f4. */
struct Task020903f4 {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 wait;
    /* 0x24 */ u8 unk24[0x40];
    /* 0x64 */ s16 value;
    /* 0x66 */ s8 thread; /* woken when done */
};

s32 cmdSetGlobal(struct ScriptThread *thread);
s32 func_020903f4();
s32 func_02090760(struct ScriptThread *thread);
s32 func_020902d0(struct ScriptThread *thread);
s32 func_0209036c(struct ScriptThread *thread);
s32 func_020903b8(struct ScriptThread *thread);
s32 cmdWaitForGlobal(struct ScriptThread *thread);
s32 cmdCopyGlobalToVar(struct ScriptThread *thread);
s32 cmdSubtractFromGlobal(struct ScriptThread *thread);
s32 cmdAddToGlobal(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_VAR_H */
