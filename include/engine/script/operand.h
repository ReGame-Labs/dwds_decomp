#ifndef ENGINE_SCRIPT_OPERAND_H
#define ENGINE_SCRIPT_OPERAND_H

/* The script engine's operand readers, and the commands that read actors'
 * positions and Digimon into variables, show a Digimon's message and reload
 * the field. */

#include "types.h"

struct ScriptThread;

s32 func_0208c0e4(struct ScriptThread *thread);
s32 func_0208c474(struct ScriptThread *thread);
s16 readOperand(struct ScriptThread *thread);
s32 func_0208c5a0(struct ScriptThread *thread);
s32 func_0208c658(struct ScriptThread *thread);
s32 readScriptWord(struct ScriptThread *thread);
s32 func_0208c710(struct ScriptThread *thread);
s32 func_0208c748(struct ScriptThread *thread);
s32 func_0208c7a0(struct ScriptThread *thread);
void func_0208c170(void);
s32 peekScriptWord(struct ScriptThread *thread, s32 index);
s16 resolveOperand(struct ScriptThread *thread, s16 value);

#endif /* ENGINE_SCRIPT_OPERAND_H */
