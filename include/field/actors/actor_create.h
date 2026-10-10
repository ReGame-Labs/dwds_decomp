#ifndef FIELD_ACTORS_ACTOR_CREATE_H
#define FIELD_ACTORS_ACTOR_CREATE_H

#include "types.h"

void deleteSubActors(void);
void deleteMainActors(void);
void clearSubActorFlags(u32 index, s32 flags);
void clearMainActorFlags(u32 index, s32 flags);
void setSubActorFlags(u32 index, s32 flags);
void setMainActorFlags(u32 index, s32 flags);
void func_020c7520();
void addSubActorFlags(u32 index, s32 flags);
void addMainActorFlags(u32 index, s32 flags);

#endif /* FIELD_ACTORS_ACTOR_CREATE_H */
