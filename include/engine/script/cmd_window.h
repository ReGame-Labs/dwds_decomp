#ifndef ENGINE_SCRIPT_CMD_WINDOW_H
#define ENGINE_SCRIPT_CMD_WINDOW_H

/* The script engine's window commands: windows that slide out, the entries
 * of data_021d8c98 and data_021d8cac, and programs. */

#include "types.h"

struct ScriptThread;

s32 func_020899a0();
void func_02089b88(void);
void func_02089bb0(void);
s32 func_02089d10();
void func_02089f08(void);
void func_02089f28(void);
s32 func_02089604(struct ScriptThread *thread);
s32 func_02089650(struct ScriptThread *thread);
s32 func_02089754(struct ScriptThread *thread);
s32 func_020896c8(struct ScriptThread *thread);
s32 func_0208968c(struct ScriptThread *thread);
s32 func_02089bd8(struct ScriptThread *thread);
s32 func_02089c74(struct ScriptThread *thread);
void jumpToScriptOffset(struct ScriptThread *thread, s32 offset);

#endif /* ENGINE_SCRIPT_CMD_WINDOW_H */
