#ifndef FIELD_ACTORS_ROUTE_COMMANDS_H
#define FIELD_ACTORS_ROUTE_COMMANDS_H

/* Writing the routes the actors play (ACTOR_STATE_ROUTE): the script writes a
 * route code by code for the actor of data_021e9c9c (main screen) or
 * data_021e9c98 (sub screen) into its route of ACTOR_ROUTES. */

#include "types.h"

/* The codes of a route, each followed by its arguments. */
enum RouteCode {
    ROUTE_END              = -1,         /* back to the start, or the end of the loops */
    ROUTE_WALK             = 0,         /* mode, x, y, s8: func_020c4668's arguments */
    ROUTE_WALK_1           = 1,       /* played as ROUTE_WALK */
    ROUTE_WAIT_ARRIVAL     = 2, /* until the walk ends */
    ROUTE_WAIT             = 3,         /* frames */
    ROUTE_FACE             = 4,         /* DIR_* */
    ROUTE_FREE_FACING      = 5,
    ROUTE_FIX_FACING       = 6,
    ROUTE_SET_ANIMATION    = 7, /* ACTOR_ANIM_* */
    ROUTE_RESUME_ANIMATION = 8,
    ROUTE_PAUSE_ANIMATION  = 9,
    ROUTE_SET_CELL         = 10 /* cell */
};

#define ROUTE_COUNT 8
#define ROUTE_LENGTH 256

u8 isSubActorRouteDone(u16 id);
u8 isMainActorRouteDone(u16 id);
void func_020c32c0();
void func_020c3388();
void addSubRouteFixFacing(void);
void addSubRouteFreeFacing(void);
void addSubRouteWaitArrival(void);
void addMainRouteFixFacing(void);
void addMainRouteFreeFacing(void);
void addMainRouteWaitArrival(void);
void func_020c3574();
void func_020c3704();
void endSubRoute(void);
void endMainRoute(void);
void func_020c34a4();
void func_020c3644();

#endif /* FIELD_ACTORS_ROUTE_COMMANDS_H */
