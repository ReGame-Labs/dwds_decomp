#ifndef BATTLE_CHARACTERS_MOVE_SCRIPT_H
#define BATTLE_CHARACTERS_MOVE_SCRIPT_H

/* The move scripts of /dat/wz/: the task that runs their commands. */

#include "types.h"

void freeMoveScript(void);
void initMoveScripts(void);
void tickMoveScriptTask(void);
void stopMoveScriptTask(void);
void startMoveScriptTask(s16 *script, u16 length);

#endif /* BATTLE_CHARACTERS_MOVE_SCRIPT_H */
