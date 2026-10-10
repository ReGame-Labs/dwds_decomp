#include "field/actors/actor_save_flash.h"
#include "engine/data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "field/actors/actor_files.h"
#include "field/actors/route_commands.h"

/* Adds to the main screen's actor's route: resume the animation. */
void addMainRouteResumeAnimation(void) {
    struct Actor *actor = getMainActor(data_021e9c9c);
    struct ActorRoute *route;

    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_RESUME_ANIMATION;
    route->length++;
}

/* Adds to the sub screen's actor's route: resume the animation. */
void addSubRouteResumeAnimation(void) {
    struct Actor *actor = getSubActor(data_021e9c98);
    struct ActorRoute *route;

    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_RESUME_ANIMATION;
    route->length++;
}

/* Adds to the main screen's actor's route: pause the animation. */
void addMainRoutePauseAnimation(void) {
    struct Actor *actor = getMainActor(data_021e9c9c);
    struct ActorRoute *route;

    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_PAUSE_ANIMATION;
    route->length++;
}

/* Adds to the sub screen's actor's route: pause the animation. */
void addSubRoutePauseAnimation(void) {
    struct Actor *actor = getSubActor(data_021e9c98);
    struct ActorRoute *route;

    if (actor == NULL) {
        return;
    }
    route                                     = &actor->work.route;
    ACTOR_ROUTES[route->route][route->length] = ROUTE_PAUSE_ANIMATION;
    route->length++;
}

/* Stops the route of the main screen's actor: it stands. */
void stopMainActorRoute(u16 id) {
    struct Actor *actor;

    actor = getMainActor(id);
    if (actor->state == ACTOR_STATE_ROUTE) {
        actor->state = ACTOR_STATE_STAND;
    }
}

/* Stops the route of the sub screen's actor: it stands. */
void stopSubActorRoute(u16 id) {
    struct Actor *actor;

    actor = getSubActor(id);
    if (actor->state == ACTOR_STATE_ROUTE) {
        actor->state = ACTOR_STATE_STAND;
    }
}

/* The palette flash of a main screen's actor, one of its updates: each frame
 * the offset grows by a step for 16 frames, then shrinks back, and the actor's
 * colors plus the offset are loaded into its palette slot. */
void updateMainActorFlash(s32 param, struct ActorFlash *flash) {
    struct Actor *actor = flash->actor;

    func_02030f78(flash->colors, flash->palette, sizeof(flash->colors));
    if (flash->delta > 0) {
        func_02043da0(&flash->offset, 0, 0, flash->step);
        func_02043da0(flash->colors, 0, 15, flash->offset);
    } else {
        func_02043cdc(&flash->offset, 0, 0, flash->step);
        func_02043da0(flash->colors, 0, 15, flash->offset);
    }
    loadMainPalette((u16) (actor->palette * 16 + 0xA00), 16, (s32) flash->colors);
    flash->level += flash->delta;
    if (flash->level >= 16 || flash->level <= 0) {
        flash->delta *= -1;
    }
}

/* The palette flash of a sub screen's actor, one of its updates: each frame
 * the offset grows by a step for 16 frames, then shrinks back, and the actor's
 * colors plus the offset are loaded into its palette slot. */
void updateSubActorFlash(s32 param, struct ActorFlash *flash) {
    struct Actor *actor = flash->actor;

    func_02030f78(flash->colors, flash->palette, sizeof(flash->colors));
    if (flash->delta > 0) {
        func_02043da0(&flash->offset, 0, 0, flash->step);
        func_02043da0(flash->colors, 0, 15, flash->offset);
    } else {
        func_02043cdc(&flash->offset, 0, 0, flash->step);
        func_02043da0(flash->colors, 0, 15, flash->offset);
    }
    loadSubPalette((u16) (actor->palette * 16 + 0xA00), 16, (s32) flash->colors);
    flash->level += flash->delta;
    if (flash->level >= 16 || flash->level <= 0) {
        flash->delta *= -1;
    }
}
