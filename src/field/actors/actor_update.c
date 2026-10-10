#include "field/actors/actor_update.h"
#include "engine/data.h"
#include "field/actors/actor_facing.h"
#include "field/actors/actor_files.h"
#include "field/map/data.h"

/* The handler of ACTOR_STATE_STAND: the actor stops, turns to stand and
 * steps its animation. */
void tickActorStand(struct Actor *actor) {
    actor->velX = 0;
    actor->velY = 0;
    if (!(actor->flags & ACTOR_FIXED_FACING)) {
        func_020c5fe4(actor);
    }
    if (!(actor->flags & ACTOR_PAUSED_ANIMATION)) {
        actor->animFrame = func_020c6734(actor->animFile, actor->animation, &actor->frameTime);
        actor->cell      = actor->animFrame->cell;
    }
    actor->halfWidth  = actor->animFrame->width >> 1;
    actor->halfHeight = actor->animFrame->height >> 1;
}

/* Makes the actor the party's leader: fills the trail with where it stands,
 * spaces the three followers 8, 16 and 24 steps behind it and starts
 * ACTOR_STATE_LEAD. */
void startActorLeading(struct Actor *actor) {
    s32 i;
    struct ActorFollow *follow;

    for (i = 0; i < 80; i++) {
        FOLLOW_TRAIL.x[i]         = actor->xFixed;
        FOLLOW_TRAIL.y[i]         = actor->yFixed;
        FOLLOW_TRAIL.animation[i] = actor->animation;
    }
    for (i = 0; i < 3; i++) {
        FOLLOW_TRAIL.spacing[i] = (i + 1) * 8;
    }
    FOLLOW_TRAIL.targetSpacing = 8;
    FOLLOW_TRAIL.steps         = 0;
    actor->state               = ACTOR_STATE_LEAD;
    follow                     = &actor->work.follow;
    follow->actor              = actor;
    follow->trail              = &FOLLOW_TRAIL;
}

/* Makes the actor follow the leader along the trail (ACTOR_STATE_FOLLOW). */
void startActorFollowing(struct Actor *actor) {
    struct ActorFollow *follow;

    actor->state  = ACTOR_STATE_FOLLOW;
    follow        = &actor->work.follow;
    follow->actor = actor;
    follow->trail = &FOLLOW_TRAIL;
}
