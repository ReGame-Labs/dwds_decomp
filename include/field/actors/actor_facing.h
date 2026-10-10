#ifndef FIELD_ACTORS_ACTOR_FACING_H
#define FIELD_ACTORS_ACTOR_FACING_H

/* An actor's facing and animation, its move by its velocity and its place in
 * the map's collision. */

#include "types.h"

struct Actor;
struct MapAnimFile;
struct MapAnimFrame;

void setActorAnimation(struct Actor *actor, s16 animation);
void setActorCell(struct Actor *actor, s16 cell);
void updateActorDirection(struct Actor *actor);
void faceActor(struct Actor *actor, u8 direction);
void moveLeaderByPad(struct Actor *actor);
s32 func_020c6228(struct Actor *actor);
struct MapAnimFrame *func_020c6734(struct MapAnimFile *file, u16 animation, s16 *frameTime);
void func_020c5fe4(struct Actor *actor);
void removeSubActorCollision(struct Actor *actor);
void removeMainActorCollision(struct Actor *actor);

#endif /* FIELD_ACTORS_ACTOR_FACING_H */
