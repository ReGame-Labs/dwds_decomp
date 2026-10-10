#ifndef ENGINE_SCRIPT_ACTOR_PARTY_H
#define ENGINE_SCRIPT_ACTOR_PARTY_H

/* The script engine's commands that make actors, also for the party's
 * Digimon (main and sub pairs, as in engine/script/actor/flags.h), and a few map
 * switches. */

#include "types.h"

struct ScriptThread;

s32 func_02093a7c(struct ScriptThread *thread);
s32 func_02093a94(struct ScriptThread *thread);
s32 func_02093aac(struct ScriptThread *thread);
s32 func_02093ac4(struct ScriptThread *thread);
s32 func_02093fe8(struct ScriptThread *thread);
s32 func_020940d0(struct ScriptThread *thread);
s32 func_02093b28(struct ScriptThread *thread);
s32 func_02093e44(struct ScriptThread *thread);
s32 func_020940a4(struct ScriptThread *thread);
s32 func_02093adc(struct ScriptThread *thread);
s32 func_02093b5c(struct ScriptThread *thread);
s32 func_02093d5c(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_ACTOR_PARTY_H */
