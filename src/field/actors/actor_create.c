#include "field/actors/actor_create.h"
#include "engine/data.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_update.h"
#include "field/actors/actor_walk.h"

/* Sets the flags of the main screen's actor at index to the given ones, and
 * starts what its new mode needs: leading, following or func_020c4c70. */
void setMainActorFlags(u32 index, s32 flags) {
    struct Actor *actor;
    u32 mode;

    if (index >= ACTOR_COUNT) {
        return;
    }
    actor = &MAIN_ACTORS[index];
    if (!(actor->flags & ACTOR_ACTIVE)) {
        return;
    }
    mode = flags & ACTOR_MODE;
    if (mode != 0) {
        actor->flags &= ~ACTOR_MODE;
    }
    actor->flags = flags | ACTOR_ACTIVE;
    switch (mode) {
        case ACTOR_MODE_LEADER:
            startActorLeading(actor);
            break;
        case ACTOR_MODE_FOLLOWER1:
        case ACTOR_MODE_FOLLOWER2:
        case ACTOR_MODE_FOLLOWER3:
            actor->flags |= ACTOR_PASS_THROUGH;
            startActorFollowing(actor);
            break;
        case 0x50:
            func_020c4c70(actor->index);
            break;
    }
}

/* Sets the flags of the sub screen's actor at index to the given ones, and
 * starts what its new mode needs: leading, following or func_020c4bd4. */
void setSubActorFlags(u32 index, s32 flags) {
    struct Actor *actor;
    u32 mode;

    if (index >= ACTOR_COUNT) {
        return;
    }
    actor = &SUB_ACTORS[index];
    if (!(actor->flags & ACTOR_ACTIVE)) {
        return;
    }
    mode = flags & ACTOR_MODE;
    if (mode != 0) {
        actor->flags &= ~ACTOR_MODE;
    }
    actor->flags = flags | ACTOR_ACTIVE;
    switch (mode) {
        case ACTOR_MODE_LEADER:
            startActorLeading(actor);
            break;
        case ACTOR_MODE_FOLLOWER1:
        case ACTOR_MODE_FOLLOWER2:
        case ACTOR_MODE_FOLLOWER3:
            actor->flags |= ACTOR_PASS_THROUGH;
            startActorFollowing(actor);
            break;
        case 0x50:
            func_020c4bd4(actor->index);
            break;
    }
}

/* Adds flags to the main screen's actor at index, and starts what a new mode
 * needs: leading, following or func_020c4c70. */
void addMainActorFlags(u32 index, s32 flags) {
    struct Actor *actor;
    u32 mode;

    if (index >= ACTOR_COUNT) {
        return;
    }
    actor = &MAIN_ACTORS[index];
    if (!(actor->flags & ACTOR_ACTIVE)) {
        return;
    }
    mode = flags & ACTOR_MODE;
    if (mode != 0) {
        actor->flags &= ~ACTOR_MODE;
    }
    actor->flags |= flags;
    switch (mode) {
        case ACTOR_MODE_LEADER:
            startActorLeading(actor);
            break;
        case ACTOR_MODE_FOLLOWER1:
        case ACTOR_MODE_FOLLOWER2:
        case ACTOR_MODE_FOLLOWER3:
            actor->flags |= ACTOR_PASS_THROUGH;
            startActorFollowing(actor);
            break;
        case 0x50:
            func_020c4c70(actor->index);
            break;
    }
}

/* Adds flags to the sub screen's actor at index, and starts what a new mode
 * needs: leading, following or func_020c4bd4. */
void addSubActorFlags(u32 index, s32 flags) {
    struct Actor *actor;
    u32 mode;

    if (index >= ACTOR_COUNT) {
        return;
    }
    actor = &SUB_ACTORS[index];
    if (!(actor->flags & ACTOR_ACTIVE)) {
        return;
    }
    mode = flags & ACTOR_MODE;
    if (mode != 0) {
        actor->flags &= ~ACTOR_MODE;
    }
    actor->flags |= flags;
    switch (mode) {
        case ACTOR_MODE_LEADER:
            startActorLeading(actor);
            break;
        case ACTOR_MODE_FOLLOWER1:
        case ACTOR_MODE_FOLLOWER2:
        case ACTOR_MODE_FOLLOWER3:
            actor->flags |= ACTOR_PASS_THROUGH;
            startActorFollowing(actor);
            break;
        case 0x50:
            func_020c4bd4(actor->index);
            break;
    }
}

/* Clears flags of the main screen's actor at index. */
void clearMainActorFlags(u32 index, s32 flags) {
    struct Actor *actor;

    if (index >= ACTOR_COUNT) {
        return;
    }
    actor = &MAIN_ACTORS[index];
    if (actor->flags & ACTOR_ACTIVE) {
        actor->flags &= ~flags;
    }
}

/* Clears flags of the sub screen's actor at index. */
void clearSubActorFlags(u32 index, s32 flags) {
    struct Actor *actor;

    if (index >= ACTOR_COUNT) {
        return;
    }
    actor = &SUB_ACTORS[index];
    if (actor->flags & ACTOR_ACTIVE) {
        actor->flags &= ~flags;
    }
}

/* Deletes every actor of the main screen. */
void deleteMainActors(void) {
    s32 i;

    i = 0;
    do {
        func_020c7060(i);
        i++;
    } while (i < ACTOR_COUNT);
}

/* Deletes every actor of the sub screen. */
void deleteSubActors(void) {
    s32 i;

    i = 0;
    do {
        func_020c6fb8(i);
        i++;
    } while (i < ACTOR_COUNT);
}
