#ifndef FIELD_ACTORS_ACTOR_TASKS_H
#define FIELD_ACTORS_ACTOR_TASKS_H

#include "types.h"

void startSubActorTaskWithVram(s16 blocks);
void startMainActorTaskWithVram(s16 blocks);
s32 endSubActorTask(void);
s32 endMainActorTask(void);
void startSubActorTask(void);
void startMainActorTask(void);
s32 func_020c8410();
s32 func_020c8b6c();

#endif /* FIELD_ACTORS_ACTOR_TASKS_H */
