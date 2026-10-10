#ifndef FIELD_ACTORS_ACTOR_FILES_H
#define FIELD_ACTORS_ACTOR_FILES_H

/* The field's actors: finding them by index or by flags, loading their
 * characters' files from /dat/mchr/ and deleting them. */

#include "engine/data.h"
#include "types.h"

/* The bits of an actor's flags. */
enum ActorFlag {
    ACTOR_ACTIVE           = 0x1,
    ACTOR_MODE             = 0xF0,          /* one of ACTOR_MODE_* */
    ACTOR_SOLID            = 0x100,        /* it takes its place in the map's collision */
    ACTOR_PASS_THROUGH     = 0x400, /* it doesn't, a follower */
    ACTOR_HIDDEN           = 0x1000,
    ACTOR_CAMERA           = 0x2000,          /* the map scrolls with it, as with the leader */
    ACTOR_FIXED_FACING     = 0x4000,    /* its velocity doesn't turn it */
    ACTOR_PAUSED_ANIMATION = 0x8000,
    ACTOR_FROZEN           = 0x10000,         /* it stands, whatever its state */
    ACTOR_EXTRA_HIDDEN     = 0x40000    /* its second sprite isn't drawn */
};

/* What an actor is, in its flags' ACTOR_MODE bits. */
enum ActorMode {
    ACTOR_MODE_LEADER    = 0x10,    /* the party's leader, moved by the pad */
    ACTOR_MODE_FOLLOWER1 = 0x20, /* the followers, spacing[0-2] steps behind */
    ACTOR_MODE_FOLLOWER2 = 0x30,
    ACTOR_MODE_FOLLOWER3 = 0x40,
    ACTOR_MODE_WANDER    = 0x60
};

/* An actor's state, the index of its handler in ACTOR_STATE_HANDLERS. */
enum ActorState {
    ACTOR_STATE_STAND,
    ACTOR_STATE_LEAD,
    ACTOR_STATE_FOLLOW,
    ACTOR_STATE_ANIMATE,
    ACTOR_STATE_WANDER,
    ACTOR_STATE_WALK,
    ACTOR_STATE_ROUTE
};

/* The bits of an actor's direction. */
enum Direction {
    DIR_UP    = 0x1,
    DIR_LEFT  = 0x2,
    DIR_DOWN  = 0x4,
    DIR_RIGHT = 0x8
};

/* An actor's animations: standing facing each way, then walking. */
enum ActorAnimation {
    ACTOR_ANIM_UP,
    ACTOR_ANIM_UP_RIGHT,
    ACTOR_ANIM_RIGHT,
    ACTOR_ANIM_DOWN_RIGHT,
    ACTOR_ANIM_UP_LEFT,
    ACTOR_ANIM_LEFT,
    ACTOR_ANIM_DOWN_LEFT,
    ACTOR_ANIM_DOWN,
    ACTOR_ANIM_WALK /* added to a standing one */
};

#define ACTOR_COUNT 48

void func_020c6fb8(u32 index);
void func_020c7060(u32 index);
struct Actor *findSubActor(s32 flags);
struct Actor *findMainActor(s32 flags);
/* These two return a struct Actor *; engine/script/actor/move.c still takes it as a u8 *. */
void *getSubActor(u32 index);
void *getMainActor(u32 index);
void func_020c6b3c(s32 character);
void func_020c6d50(s32 character);

#endif /* FIELD_ACTORS_ACTOR_FILES_H */
