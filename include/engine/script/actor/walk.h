#ifndef ENGINE_SCRIPT_ACTOR_WALK_H
#define ENGINE_SCRIPT_ACTOR_WALK_H

/* The script engine's commands that move actors to points, to other actors
 * and to the map's rectangles (main and sub pairs, as in engine/script/actor/flags.h). */

#include "types.h"

struct ScriptThread;

s32 func_02092d98(struct ScriptThread *thread);
s32 func_02092ef8(struct ScriptThread *thread);
s32 func_02092f9c(struct ScriptThread *thread);
s32 func_02092fe8(struct ScriptThread *thread);
s32 func_02092c38(struct ScriptThread *thread);
s32 func_020927f0(struct ScriptThread *thread);
s32 func_02092a54(struct ScriptThread *thread);
s32 func_02092b7c(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_ACTOR_WALK_H */
