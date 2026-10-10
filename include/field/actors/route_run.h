#ifndef FIELD_ACTORS_ROUTE_RUN_H
#define FIELD_ACTORS_ROUTE_RUN_H

/* Playing the actors' routes (ACTOR_STATE_ROUTE) and walks
 * (ACTOR_STATE_WALK). */

#include "types.h"

struct Actor;

void startSubActorRoute(u16 id, s32 loops, u8 index);
void startMainActorRoute(u16 id, s32 loops, u8 index);
void stopSubActorWalk(u16 id);
void func_020c3d28(struct Actor *actor);
u8 isSubActorWalkDone(u16 id);
u8 isMainActorWalkDone(u16 id);

#endif /* FIELD_ACTORS_ROUTE_RUN_H */
