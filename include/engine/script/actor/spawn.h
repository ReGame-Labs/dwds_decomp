#ifndef ENGINE_SCRIPT_ACTOR_SPAWN_H
#define ENGINE_SCRIPT_ACTOR_SPAWN_H

/* The script engine's commands that create and place actors (main and sub
 * pairs, as in engine/script/actor/flags.h), and the jumps that start a map's scripts. */

#include "types.h"

struct ScriptThread;

s32 func_020932c8(struct ScriptThread *thread);
s32 func_020932e0(struct ScriptThread *thread);
s32 func_020932f8(struct ScriptThread *thread);
s32 func_0209339c(struct ScriptThread *thread);
s32 func_02093198(struct ScriptThread *thread);
s32 func_0209301c(struct ScriptThread *thread);
s32 func_02093068(struct ScriptThread *thread);
s32 func_0209309c(struct ScriptThread *thread);
s32 func_020930e8(struct ScriptThread *thread);
s32 func_0209311c(struct ScriptThread *thread);
s32 func_020931fc(struct ScriptThread *thread);
s32 func_02093270(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_ACTOR_SPAWN_H */
