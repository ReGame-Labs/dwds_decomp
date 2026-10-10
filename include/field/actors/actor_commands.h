#ifndef FIELD_ACTORS_ACTOR_COMMANDS_H
#define FIELD_ACTORS_ACTOR_COMMANDS_H

/* The script commands' work on the field's actors: their flags, priority and
 * the snapshot restored after a battle. */

#include "types.h"

void hideSubActorExtra(s32 index);
void hideMainActorExtra(s32 index);
void showSubActorExtra(s32 index);
void showMainActorExtra(s32 index);
void func_020c2250(s32 index);
void func_020c227c(s32 index);
void func_020c22a8(s32 index);
void func_020c22b8(s32 index);
void hideSubActor(s32 index);
void hideMainActor(s32 index);
void showSubActor(s32 index);
void showMainActor(s32 index);
void freezeSubActor(s32 index);
void freezeMainActor(s32 index);
void unfreezeSubActor(s32 index);
void unfreezeMainActor(s32 index);
void pauseSubActorAnimation(s32 index);
void pauseMainActorAnimation(s32 index);
void resumeSubActorAnimation(s32 index);
void resumeMainActorAnimation(s32 index);
void fixSubActorFacing(s32 index);
void fixMainActorFacing(s32 index);
void freeSubActorFacing(s32 index);
void freeMainActorFacing(s32 index);
void func_020c23c8(s32 index);
void func_020c2404(s32 index);
s32 func_020c2088();
s32 func_020c2158();
s32 func_020c257c();
void func_020c2070(u16 index, u16 value);
void setSubActorPriority(s32 index, u16 priority);
void func_020c26b8();
void func_020c26f8();
void func_020c2440();

#endif /* FIELD_ACTORS_ACTOR_COMMANDS_H */
