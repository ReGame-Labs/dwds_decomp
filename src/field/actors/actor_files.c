#include "field/actors/actor_files.h"
#include "engine/data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"

/* Loads the animation file (/dat/mchr/%xa) of a map character, unless it is
 * loaded, and counts a user more. */
void func_020c6d50(s32 character) {
    s8 name[8];
    s8 path[0x40];
    u16 anim;

    anim = data_02107f34[character].anim;
    if (data_021eb4bc[anim] == NULL && data_021e9e38[anim] == 0) {
        func_020e3a68(name, data_021382f8, anim);
        joinPath(path, data_021382fc, name);
        func_02043fc4(&data_021eb4bc[anim], path);
    }
    data_021e9e38[anim]++;
}

/* Loads the /dat/mchr/%xh file of a map character, unless it has none or it
 * is loaded. */
void func_020c6b3c(s32 character) {
    char name[8];
    char path[24];
    u16 file;

    file = data_02107f34[character].unk6;
    if (file == 0xFFFF) {
        return;
    }
    if (data_021eab20[file] != NULL) {
        return;
    }
    func_020e3a68(name, data_021382c8, file);
    joinPath(path, data_021382cc, name);
    func_02043fc4(&data_021eab20[file], path);
}

/* Returns the main screen's actor at index, or NULL when it isn't active. */
void *getMainActor(u32 index) {
    if (index >= ACTOR_COUNT) {
        return NULL;
    }
    if (MAIN_ACTORS[index].flags & ACTOR_ACTIVE) {
        return &MAIN_ACTORS[index];
    }
    return NULL;
}

/* Returns the sub screen's actor at index, or NULL when it isn't active. */
void *getSubActor(u32 index) {
    if (index >= ACTOR_COUNT) {
        return NULL;
    }
    if (SUB_ACTORS[index].flags & ACTOR_ACTIVE) {
        return &SUB_ACTORS[index];
    }
    return NULL;
}

/* Returns the first active actor of the main screen with all the given flags,
 * or NULL. */
struct Actor *findMainActor(s32 flags) {
    s32 i;
    struct Actor *actor;
    s32 actorFlags;

    actor = MAIN_ACTORS;
    for (i = 0; i < ACTOR_COUNT; i++) {
        actorFlags = actor->flags;
        if ((actorFlags & ACTOR_ACTIVE) && flags == (flags & actorFlags)) {
            return &MAIN_ACTORS[i];
        }
        actor++;
    }
    return NULL;
}

/* Returns the first active actor of the sub screen with all the given flags,
 * or NULL. */
struct Actor *findSubActor(s32 flags) {
    s32 i;
    struct Actor *actor;
    s32 actorFlags;

    actor = SUB_ACTORS;
    for (i = 0; i < ACTOR_COUNT; i++) {
        actorFlags = actor->flags;
        if ((actorFlags & ACTOR_ACTIVE) && flags == (flags & actorFlags)) {
            return &SUB_ACTORS[i];
        }
        actor++;
    }
    return NULL;
}
