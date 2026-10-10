#ifndef FIELD_ACTORS_ACTOR_WALK_H
#define FIELD_ACTORS_ACTOR_WALK_H

/* Actors walking to a point or wandering in a rectangle. */

#include "types.h"

struct Actor;
struct ActorWalk;

void standSubActor(u16 id);
void standMainActor(u16 id);
void resumeSubActorWander(u16 id);
void resumeMainActorWander(u16 id);
void pauseSubActorWander(u16 id);
void pauseMainActorWander(u16 id);
void tickActorAnimate(struct Actor *actor);
s32 func_020c44e4();
s32 func_020c45f0();
void func_020c4bd4(u32 index);
void walkSubActorTo(u16 id, s32 mode, s16 x, s16 y, s8 speed);
void func_020c4668(struct ActorWalk *walk, struct Actor *actor, s32 mode, s16 x, s16 y, s8 speed);
void startSubActorWander(u16 id, s32 width, s32 height);
void startMainActorWander(u16 id, s32 width, s32 height);

#endif /* FIELD_ACTORS_ACTOR_WALK_H */
