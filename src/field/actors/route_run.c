#include "field/actors/route_run.h"
#include "engine/data.h"
#include "field/actors/actor_files.h"

/* Returns whether the main screen's actor isn't walking to a point. */
u8 isMainActorWalkDone(u16 id) {
    u8 done;
    struct Actor *actor;

    actor = getMainActor(id);
    if (actor == NULL) {
        return TRUE;
    }
    if (actor->state != ACTOR_STATE_WALK) {
        done = TRUE;
    } else {
        done = FALSE;
    }
    return done;
}

/* Returns whether the sub screen's actor isn't walking to a point. */
u8 isSubActorWalkDone(u16 id) {
    u8 done;
    struct Actor *actor;

    actor = getSubActor(id);
    if (actor == NULL) {
        return TRUE;
    }
    if (actor->state != ACTOR_STATE_WALK) {
        done = TRUE;
    } else {
        done = FALSE;
    }
    return done;
}

/* Stops the walk of the sub screen's actor: a leader or a follower goes back
 * to its state. */
void stopSubActorWalk(u16 id) {
    struct Actor *actor;

    actor = getSubActor(id);
    if (actor == NULL) {
        return;
    }
    if (actor->state != ACTOR_STATE_WALK) {
        return;
    }
    actor->state = ACTOR_STATE_STAND;
    func_020c3d28(actor);
}

/* Starts a route of ACTOR_ROUTES for the main screen's actor, played loops
 * times (-1 for ever), and makes it the actor whose route the next codes
 * write. */
void startMainActorRoute(u16 id, s32 loops, u8 index) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getMainActor(id);
    if (actor == NULL) {
        return;
    }
    if (actor->state == ACTOR_STATE_ROUTE) {
        return;
    }
    actor->work.route.actor = actor;
    route                   = &actor->work.route;
    route->loops            = loops;
    route->loopsDone        = 0;
    route->pc               = 0;
    route->length           = 0;
    route->route            = index;
    route->wait             = 0;
    actor->state            = ACTOR_STATE_ROUTE;
    data_021e9c9c           = id;
}

/* Starts a route of ACTOR_ROUTES for the sub screen's actor, played loops
 * times (-1 for ever), and makes it the actor whose route the next codes
 * write. */
void startSubActorRoute(u16 id, s32 loops, u8 index) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getSubActor(id);
    if (actor == NULL) {
        return;
    }
    if (actor->state == ACTOR_STATE_ROUTE) {
        return;
    }
    actor->work.route.actor = actor;
    route                   = &actor->work.route;
    route->loops            = loops;
    route->loopsDone        = 0;
    route->pc               = 0;
    route->length           = 0;
    route->route            = index;
    route->wait             = 0;
    actor->state            = ACTOR_STATE_ROUTE;
    data_021e9c98           = id;
}
