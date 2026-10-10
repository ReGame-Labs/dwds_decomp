#ifndef FIELD_ACTORS_ACTOR_UPDATE_H
#define FIELD_ACTORS_ACTOR_UPDATE_H

/* The actors' states that follow the party's leader, and the screens' tasks
 * that run and draw the actors. */

#include "types.h"

struct Actor;

void func_020c5534(void);
void func_020c5a8c(void);
void startActorFollowing(struct Actor *actor);
void tickActorStand(struct Actor *actor);
void func_020c4c70(u32 index);
void startActorLeading(struct Actor *actor);

#endif /* FIELD_ACTORS_ACTOR_UPDATE_H */
