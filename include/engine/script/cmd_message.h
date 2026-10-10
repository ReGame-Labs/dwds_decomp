#ifndef ENGINE_SCRIPT_CMD_MESSAGE_H
#define ENGINE_SCRIPT_CMD_MESSAGE_H

/* The script engine's window commands: windows that slide in, texts in the
 * message windows, and the farm results. */

#include "engine/data.h"
#include "types.h"

struct ScriptThread;

/* func_0208a3c0's task, started by command 0x113. */
struct FarmResultsTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 wait;
    /* 0x24 */ u8 unk24[0x40];
    /* 0x64 */ s16 unk64; /* global variable 10: func_ov005_0227d914 instead
                           * of the results screen */
};

s32 func_0208a72c(struct ScriptThread *thread);
s32 func_0208a744(struct ScriptThread *thread);
s32 func_0208a278(struct ScriptThread *thread);
s32 func_0208a31c(struct ScriptThread *thread);
s32 func_0208a6ec(struct ScriptThread *thread);
void func_0208a3c0(void);
s32 func_02089f48(struct ScriptThread *thread);
s32 func_02089fec(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_MESSAGE_H */
