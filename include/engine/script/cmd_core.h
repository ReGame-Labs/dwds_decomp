#ifndef ENGINE_SCRIPT_CMD_CORE_H
#define ENGINE_SCRIPT_CMD_CORE_H

/* The script engine's core commands: jumps, calls, sleep, flags, local
 * variables, BGM and sounds, and the threads' sleep and wake. */

#include "engine/data.h"
#include "types.h"

/* Command 0x0E's operand that stops the BGM instead of playing one. */
#define SCRIPT_BGM_STOP 9999

/* func_02094ec4's and func_02094f84's task: steps level by step every frame
 * until it reaches targetLevel. */
struct MapFadeTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 wait;
    /* 0x24 */ u8 unk24[0x40];
    /* 0x64 */ s16 level;
    /* 0x66 */ s16 targetLevel;
    /* 0x68 */ s16 step;
    /* 0x6A */ u8 thread; /* woken when done, 0xFF none */
};

s32 cmdSleep(struct ScriptThread *thread);
s32 func_02094e14();
void func_02094e64(void);
void sleepScriptThread(u8 thread, s16 frames);
s32 cmdPlayBgm(struct ScriptThread *thread);
void wakeScriptThread(u8 thread);
void suspendScriptThread(u8 thread);
s32 func_02094b7c(struct ScriptThread *thread);
void func_02094ec4(void);
void func_02094f84(void);
s32 cmdClearLocalFlag(struct ScriptThread *thread);
s32 cmdSetLocalFlag(struct ScriptThread *thread);
s32 cmdClearFlag(struct ScriptThread *thread);
s32 cmdSetFlag(struct ScriptThread *thread);
s32 cmdRandom(struct ScriptThread *thread);
s32 cmdGotoInThread(struct ScriptThread *thread);
s32 cmdGoto(struct ScriptThread *thread);
s32 cmdReturn(struct ScriptThread *thread);
s32 cmdJumpAhead(struct ScriptThread *thread);
s32 cmdJumpAndWaitIfFlag(struct ScriptThread *thread);
s32 cmdJumpAheadAndWait(struct ScriptThread *thread);
s32 cmdJumpBackAndWait(struct ScriptThread *thread);
void setScriptThreadSubSprite(u8 index, s16 sprite);
void func_02095044(void);
s32 isScriptThreadUsed(s32 index);
s32 getScriptGlobal(s32 var);
s32 cmdPlaySound(struct ScriptThread *thread);
s32 func_02094d64(struct ScriptThread *thread);
void func_02094e74(void);
s32 cmdJumpUnlessFlagIs(struct ScriptThread *thread);
s32 cmdCall(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_CORE_H */
