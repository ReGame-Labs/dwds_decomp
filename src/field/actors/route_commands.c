#include "field/actors/route_commands.h"
#include "engine/data.h"
#include "field/actors/actor_files.h"

/* Returns whether the main screen's actor has no route playing. */
u8 isMainActorRouteDone(u16 id) {
    u8 done;
    struct Actor *actor;

    actor = getMainActor(id);
    if (actor == NULL) {
        return TRUE;
    }
    if (actor->state != ACTOR_STATE_ROUTE) {
        done = TRUE;
    } else {
        done = FALSE;
    }
    return done;
}

/* Returns whether the sub screen's actor has no route playing. */
u8 isSubActorRouteDone(u16 id) {
    u8 done;
    struct Actor *actor;

    actor = getSubActor(id);
    if (actor == NULL) {
        return TRUE;
    }
    if (actor->state != ACTOR_STATE_ROUTE) {
        done = TRUE;
    } else {
        done = FALSE;
    }
    return done;
}

/* Ends the route written for the main screen's actor. */
void endMainRoute(void) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getMainActor(data_021e9c9c);
    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_END;
    route->length++;
    data_021e9c9c = 0xFFFF;
}

/* Ends the route written for the sub screen's actor. */
void endSubRoute(void) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getSubActor(data_021e9c98);
    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_END;
    route->length++;
    data_021e9c98 = 0xFFFF;
}

/* Adds to the main screen's actor's route: wait for the walk to end. */
void addMainRouteWaitArrival(void) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getMainActor(data_021e9c9c);
    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_WAIT_ARRIVAL;
    route->length++;
}

/* Adds to the sub screen's actor's route: wait for the walk to end. */
void addSubRouteWaitArrival(void) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getSubActor(data_021e9c98);
    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_WAIT_ARRIVAL;
    route->length++;
}

/* Adds to the main screen's actor's route: turn to where it moves again. */
void addMainRouteFreeFacing(void) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getMainActor(data_021e9c9c);
    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_FREE_FACING;
    route->length++;
}

/* Adds to the sub screen's actor's route: turn to where it moves again. */
void addSubRouteFreeFacing(void) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getSubActor(data_021e9c98);
    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_FREE_FACING;
    route->length++;
}

/* Adds to the main screen's actor's route: keep facing the same way. */
void addMainRouteFixFacing(void) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getMainActor(data_021e9c9c);
    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_FIX_FACING;
    route->length++;
}

/* Adds to the sub screen's actor's route: keep facing the same way. */
void addSubRouteFixFacing(void) {
    struct Actor *actor;
    struct ActorRoute *route;

    actor = getSubActor(data_021e9c98);
    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_FIX_FACING;
    route->length++;
}
