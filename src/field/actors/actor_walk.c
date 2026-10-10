#include "field/actors/actor_walk.h"
#include "engine/data.h"
#include "field/actors/actor_facing.h"
#include "field/actors/actor_files.h"
#include "field/map/data.h"

/* The handler of ACTOR_STATE_ANIMATE: the actor only steps its animation. */
void tickActorAnimate(struct Actor *actor) {
    if (!(actor->flags & ACTOR_PAUSED_ANIMATION)) {
        actor->animFrame = func_020c6734(actor->animFile, actor->animation, &actor->frameTime);
        actor->cell      = actor->animFrame->cell;
    }
    actor->halfWidth  = actor->animFrame->width >> 1;
    actor->halfHeight = actor->animFrame->height >> 1;
}

/* Makes the main screen's actor wander at random in a rectangle of the
 * given size around where it stands (ACTOR_STATE_WANDER). */
void startMainActorWander(u16 id, s32 width, s32 height) {
    struct Actor *actor;
    struct ActorWander *wander;

    actor = getMainActor(id);
    actor->flags &= ~ACTOR_MODE;
    actor->flags |= ACTOR_MODE_WANDER;
    actor->state   = ACTOR_STATE_WANDER;
    wander         = &actor->work.wander;
    wander->actor  = actor;
    wander->timer  = 0;
    wander->left   = actor->x - (width >> 1);
    wander->top    = actor->y - (height >> 1);
    wander->right  = wander->left + width;
    wander->bottom = wander->top + height;
    wander->paused = 0;
}

/* Makes the sub screen's actor wander at random in a rectangle of the
 * given size around where it stands (ACTOR_STATE_WANDER). */
void startSubActorWander(u16 id, s32 width, s32 height) {
    struct Actor *actor;
    struct ActorWander *wander;

    actor = getSubActor(id);
    actor->flags &= ~ACTOR_MODE;
    actor->flags |= ACTOR_MODE_WANDER;
    actor->state   = ACTOR_STATE_WANDER;
    wander         = &actor->work.wander;
    wander->actor  = actor;
    wander->timer  = 0;
    wander->left   = actor->x - (width >> 1);
    wander->top    = actor->y - (height >> 1);
    wander->right  = wander->left + width;
    wander->bottom = wander->top + height;
    wander->paused = 0;
}

/* Stops the wandering of the main screen's actor. */
void pauseMainActorWander(u16 id) {
    struct Actor *actor;

    actor = getMainActor(id);
    if (actor != NULL) {
        actor->work.wander.paused = 1;
    }
}

/* Stops the wandering of the sub screen's actor. */
void pauseSubActorWander(u16 id) {
    struct Actor *actor;

    actor = getSubActor(id);
    if (actor != NULL) {
        actor->work.wander.paused = 1;
    }
}

/* Lets the main screen's actor wander again. */
void resumeMainActorWander(u16 id) {
    struct Actor *actor;

    actor = getMainActor(id);
    if (actor != NULL) {
        actor->work.wander.paused = 0;
    }
}

/* Lets the sub screen's actor wander again. */
void resumeSubActorWander(u16 id) {
    struct Actor *actor;

    actor = getSubActor(id);
    if (actor != NULL) {
        actor->work.wander.paused = 0;
    }
}

/* Makes the main screen's actor stand (ACTOR_STATE_STAND). */
void standMainActor(u16 id) {
    struct Actor *actor;

    actor = getMainActor(id);
    if (actor != NULL) {
        actor->state = ACTOR_STATE_STAND;
    }
}

/* Makes the sub screen's actor stand (ACTOR_STATE_STAND). */
void standSubActor(u16 id) {
    struct Actor *actor;

    actor = getSubActor(id);
    if (actor != NULL) {
        actor->state = ACTOR_STATE_STAND;
    }
}

/* Makes the sub screen's actor walk to (x, y) (ACTOR_STATE_WALK). A leader
 * or a follower goes back to its state once there. */
void walkSubActorTo(u16 id, s32 mode, s16 x, s16 y, s8 speed) {
    struct Actor *actor;
    struct ActorWalk *walk;
    s32 state;

    actor = getSubActor(id);
    if (actor == NULL) {
        return;
    }
    if (actor->state == ACTOR_STATE_WALK) {
        return;
    }
    walk            = &actor->work.walk;
    walk->prevState = -1;
    state           = actor->state;
    if (state == ACTOR_STATE_LEAD || state == ACTOR_STATE_FOLLOW) {
        walk->prevState = state;
    }
    actor->state = ACTOR_STATE_WALK;
    func_020c4668(walk, actor, mode, x, y, speed);
}
