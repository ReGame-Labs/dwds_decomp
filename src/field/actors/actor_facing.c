#include "field/actors/actor_facing.h"
#include "engine/data.h"
#include "field/actors/actor_files.h"
#include "field/map/ov000_021ff94c.h"
#include "field/map/ov000_022001c4.h"

/* Takes the main screen's actor out of the map's collision, from where it
 * was the frame before (func_ov000_02200528). */
void removeMainActorCollision(struct Actor *actor) {
    s32 rect[4];
    s32 flags;

    rect[0] = actor->prevX.part.whole;
    rect[1] = actor->prevY.part.whole - actor->halfHeight;
    rect[2] = actor->halfWidth;
    rect[3] = actor->halfHeight;
    flags   = actor->flags;
    if (!(flags & ACTOR_SOLID)) {
        return;
    }
    if ((flags & ACTOR_MODE) == 0x50) {
        func_ov000_021ffca4(actor->index);
        return;
    }
    if (flags & ACTOR_PASS_THROUGH) {
        return;
    }
    func_ov000_02200528(rect);
}

/* Takes the sub screen's actor out of the map's collision, from where it
 * stands (func_ov000_02200450). */
void removeSubActorCollision(struct Actor *actor) {
    s32 rect[4];
    s32 flags;

    rect[0] = actor->x;
    rect[1] = actor->y - actor->halfHeight;
    rect[2] = actor->halfWidth;
    rect[3] = actor->halfHeight;
    flags   = actor->flags;
    if (!(flags & ACTOR_SOLID)) {
        return;
    }
    if ((flags & ACTOR_MODE) == 0x50) {
        func_ov000_021ffa10(actor->index);
        return;
    }
    if (flags & ACTOR_PASS_THROUGH) {
        return;
    }
    func_ov000_02200450(rect);
}

/* Lets the pad move the leader, at speed 2. */
void moveLeaderByPad(struct Actor *actor) {
    if ((actor->flags & ACTOR_MODE) != ACTOR_MODE_LEADER) {
        return;
    }
    actor->speed = 2;
    func_020c6228(actor);
}

/* Turns the actor to the given directions (DIR_*): walking that way, or
 * standing that way when it doesn't move along both axes. */
void faceActor(struct Actor *actor, u8 direction) {
    s16 animation;
    u8 dir;

    if (!(actor->flags & ACTOR_ACTIVE)) {
        return;
    }
    actor->direction = direction;
    dir              = actor->direction;
    if (dir & DIR_DOWN) {
        if (dir & DIR_RIGHT) {
            actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_DOWN_RIGHT;
        } else if (dir & DIR_LEFT) {
            actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_DOWN_LEFT;
        } else {
            actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_DOWN;
        }
    } else if (dir & DIR_UP) {
        if (dir & DIR_RIGHT) {
            actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_UP_RIGHT;
        } else if (dir & DIR_LEFT) {
            actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_UP_LEFT;
        } else {
            actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_UP;
        }
    } else if (dir & DIR_RIGHT) {
        actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_RIGHT;
    } else if (dir & DIR_LEFT) {
        actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_LEFT;
    }
    if (actor->velX != 0 && actor->velY != 0) {
        return;
    }
    animation = actor->animation;
    if (animation >= ACTOR_ANIM_WALK) {
        actor->animation = animation - ACTOR_ANIM_WALK;
    }
}

/* Sets the actor's direction from its velocity, when it moves. */
void updateActorDirection(struct Actor *actor) {
    s32 velY;
    s32 velX;

    if (actor->velX == 0 && actor->velY == 0) {
        return;
    }
    actor->direction = 0;
    velY             = actor->velY;
    if (velY > 0) {
        actor->direction = actor->direction | DIR_DOWN;
    } else if (velY < 0) {
        actor->direction = actor->direction | DIR_UP;
    }
    velX = actor->velX;
    if (velX > 0) {
        actor->direction = actor->direction | DIR_RIGHT;
        return;
    }
    if (velX < 0) {
        actor->direction = actor->direction | DIR_LEFT;
    }
}

/* Sets the cell the actor shows. */
void setActorCell(struct Actor *actor, s16 cell) {
    if (actor->flags & ACTOR_ACTIVE) {
        actor->cell = cell;
    }
}

/* Starts one of the actor's animations (ACTOR_ANIM_*) from its first frame. */
void setActorAnimation(struct Actor *actor, s16 animation) {
    if (actor->flags & ACTOR_ACTIVE) {
        actor->animation = animation;
        actor->frameTime = 0;
    }
}

/* Turns the actor to where it moves and walks it, or stands it when it
 * doesn't move. */
void func_020c5fe4(struct Actor *actor) {
    u8 dir;

    updateActorDirection(actor);
    if (actor->velX != 0 || actor->velY != 0) {
        dir = actor->direction;
        if (dir & DIR_DOWN) {
            if (dir & DIR_RIGHT) {
                actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_DOWN_RIGHT;
            } else if (dir & DIR_LEFT) {
                actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_DOWN_LEFT;
            } else {
                actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_DOWN;
            }
        } else if (dir & DIR_UP) {
            if (dir & DIR_RIGHT) {
                actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_UP_RIGHT;
            } else if (dir & DIR_LEFT) {
                actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_UP_LEFT;
            } else {
                actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_UP;
            }
        } else if (dir & DIR_RIGHT) {
            actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_RIGHT;
        } else if (dir & DIR_LEFT) {
            actor->animation = ACTOR_ANIM_WALK + ACTOR_ANIM_LEFT;
        }
    } else if (actor->animation >= ACTOR_ANIM_WALK) {
        actor->animation -= ACTOR_ANIM_WALK;
    }
}
