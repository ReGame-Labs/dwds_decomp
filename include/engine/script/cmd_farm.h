#ifndef ENGINE_SCRIPT_CMD_FARM_H
#define ENGINE_SCRIPT_CMD_FARM_H

/* The script engine's commands on the thread's sprites, the choice task, the
 * farm screen and func_020c28a4's module. */

#include "engine/data.h"
#include "types.h"

/* func_0208d3e0's task: a choice between two texts of a bank. */
struct ChoiceTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 wait;
    /* 0x24 */ s16 bank; /* loadTextBank's */
    /* 0x26 */ s16 text;
    /* 0x28 */ s16 text2;
    /* 0x2A */ u16 kind; /* func_020a85a0's first argument */
    /* 0x2C */ s16 thread;
};

s32 func_0208d170(struct ScriptThread *thread);
s32 func_0208d1c4(struct ScriptThread *thread);
s32 func_0208d248(struct ScriptThread *thread);
s32 func_0208d250(struct ScriptThread *thread);
s32 func_0208d628(struct ScriptThread *thread);
s32 func_0208d084(struct ScriptThread *thread);
void func_0208d3e0(void);
s32 func_0208d108(struct ScriptThread *thread);
s32 func_0208d1e8(struct ScriptThread *thread);
s32 func_0208d610(struct ScriptThread *thread);
s32 func_0208d7c8(struct ScriptThread *thread);
s32 func_0208d140(struct ScriptThread *thread);
s32 func_0208d18c(struct ScriptThread *thread);
s32 func_0208d20c(struct ScriptThread *thread);
s32 func_0208d258(struct ScriptThread *thread);
s32 func_0208d818(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_FARM_H */
