#ifndef ENGINE_SCRIPT_CMD_GAMESTATE_H
#define ENGINE_SCRIPT_CMD_GAMESTATE_H

/* The script engine's game state commands: counters, the conditions command
 * 0x108 checks on the Digimon, and waits on the choice menu. */

#include "types.h"

struct ButtonGroup;
struct Digimon;
struct ScriptThread;

/* The condition values of func_0208b2b4 and func_0208b0f4: below 2000 a
 * Digimon's unk4, then ranges of 100 for its unk1D, unk1A and unk1E; 9999
 * fits any Digimon. */
#define CONDITION_UNK1D 2000
#define CONDITION_UNK1A 2100
#define CONDITION_UNK1E 2200
#define CONDITION_ANY 9999

s32 func_0208b068(struct ScriptThread *thread);
s32 func_0208b0d8(s32 count);
s32 func_0208b0f4(s32 condition, s32 count);
s32 func_0208b2b4(s32 condition, struct Digimon *digimon);
s32 func_0208b35c(s32 mask, struct Digimon *digimon);
s32 func_0208b04c(struct ScriptThread *thread);
s32 func_0208b010(struct ScriptThread *thread);
s32 func_0208b080(struct ScriptThread *thread);
s32 func_0208b0b4(s32 count);
s32 func_0208b23c(s32 mask, struct Digimon *digimon);
void func_0208b69c(s16 touched, s16 cursor, struct ButtonGroup *group);
s32 func_0208b5a0(struct ScriptThread *thread);
s32 func_0208b62c(struct ScriptThread *thread);
void func_0208b6f4(s16 touched, s16 cursor, struct ButtonGroup *group);

#endif /* ENGINE_SCRIPT_CMD_GAMESTATE_H */
