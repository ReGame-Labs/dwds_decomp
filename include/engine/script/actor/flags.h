#ifndef ENGINE_SCRIPT_ACTOR_FLAGS_H
#define ENGINE_SCRIPT_ACTOR_FLAGS_H

/* The script engine's actor flag commands. Each comes in a pair: one for a
 * sub actor (getMainActor, MAIN_ACTORS) and one for a main actor
 * (getSubActor, SUB_ACTORS); the main one does nothing while event flag
 * 0x3E9 is set. The current actors are data_021e9c98 (main) and
 * data_021e9c9c (sub). */

#include "types.h"

struct ScriptThread;

s32 func_0209168c(struct ScriptThread *thread);
s32 func_020916d0(struct ScriptThread *thread);
s32 func_02091784(struct ScriptThread *thread);
s32 func_020917c8(struct ScriptThread *thread);
s32 func_0209101c(struct ScriptThread *thread);
s32 func_0209109c(struct ScriptThread *thread);
s32 func_0209111c(struct ScriptThread *thread);
s32 func_0209119c(struct ScriptThread *thread);
s32 func_0209121c(struct ScriptThread *thread);
s32 func_0209136c(struct ScriptThread *thread);
s32 func_020913ec(struct ScriptThread *thread);
s32 func_0209153c(struct ScriptThread *thread);
s32 func_020915bc(struct ScriptThread *thread);
s32 func_02091634(struct ScriptThread *thread);
s32 func_0209172c(struct ScriptThread *thread);
s32 func_020912c4(struct ScriptThread *thread);
s32 func_02091494(struct ScriptThread *thread);
s32 func_020915f0(struct ScriptThread *thread);
s32 func_02091660(struct ScriptThread *thread);
s32 func_020916a4(struct ScriptThread *thread);
s32 func_020916e8(struct ScriptThread *thread);
s32 func_02091758(struct ScriptThread *thread);
s32 func_0209179c(struct ScriptThread *thread);
s32 func_02090fd0(struct ScriptThread *thread);
s32 func_02091050(struct ScriptThread *thread);
s32 func_020910d0(struct ScriptThread *thread);
s32 func_02091150(struct ScriptThread *thread);
s32 func_020911d0(struct ScriptThread *thread);
s32 func_02091250(struct ScriptThread *thread);
s32 func_02091320(struct ScriptThread *thread);
s32 func_020913a0(struct ScriptThread *thread);
s32 func_02091420(struct ScriptThread *thread);
s32 func_020914f0(struct ScriptThread *thread);
s32 func_02091570(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_ACTOR_FLAGS_H */
