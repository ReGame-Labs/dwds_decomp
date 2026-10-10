#ifndef ENGINE_SCRIPT_CMD_BATTLE_H
#define ENGINE_SCRIPT_CMD_BATTLE_H

/* The script engine's battle commands, the BGM kept across them, and the
 * tasks that leave the field and come back to it. */

#include "types.h"

struct ScriptThread;

s32 cmdRestoreBgm(struct ScriptThread *thread);
s32 cmdSaveBgm(struct ScriptThread *thread);
s32 func_0208c84c(struct ScriptThread *thread);
s32 func_0208c99c(struct ScriptThread *thread);
s32 func_0208ca28(struct ScriptThread *thread);
s32 func_0208ca5c(struct ScriptThread *thread);
s32 func_0208ce0c(struct ScriptThread *thread);
s32 func_0208ce40(struct ScriptThread *thread);
s32 cmdStartBattle(struct ScriptThread *thread);
s32 func_0208ca64(struct ScriptThread *thread);
s32 func_0208cdbc(struct ScriptThread *thread);
s32 func_0208c8c8(struct ScriptThread *thread);
s32 func_0208c864(struct ScriptThread *thread);
void func_0208ca98(void);
void func_0208ce74(void);
s32 func_0208c924(struct ScriptThread *thread);
s32 func_0208c960(struct ScriptThread *thread);
s32 func_0208c8e4(struct ScriptThread *thread);
s32 func_0208c904(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_BATTLE_H */
