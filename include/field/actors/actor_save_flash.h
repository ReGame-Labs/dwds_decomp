#ifndef FIELD_ACTORS_ACTOR_SAVE_FLASH_H
#define FIELD_ACTORS_ACTOR_SAVE_FLASH_H

/* The snapshot of the actors kept over a battle, the actors' palette flash
 * and more of the route codes. */

#include "types.h"

struct Actor;

/* The work of an actor's palette flash (updateMainActorFlash, updateSubActorFlash). */
struct ActorFlash {
    /* 0x00 */ struct Actor *actor;
    /* 0x04 */ u16 palette[16]; /* the actor's own colors */
    /* 0x24 */ u16 colors[16];  /* the colors shown, palette plus offset */
    /* 0x44 */ u16 step;        /* the color the offset grows by a frame */
    /* 0x46 */ u16 offset;
    /* 0x48 */ s16 level;       /* frames into the flash, 0-16 */
    /* 0x4A */ s16 delta;       /* 1 growing, -1 shrinking */
};

s32 func_020c2bec();
s32 func_020c2d0c();
void stopSubActorRoute(u16 id);
void stopMainActorRoute(u16 id);
s32 func_020c28a4();
void func_020c2e50();
void func_020c3088();
void addSubRoutePauseAnimation(void);
void addSubRouteResumeAnimation(void);
void updateSubActorFlash(s32 param, struct ActorFlash *flash);
void updateMainActorFlash(s32 param, struct ActorFlash *flash);
s32 func_020c2b64();
s32 func_020c2c74();
void func_020c2dec();
void addMainRoutePauseAnimation(void);
void addMainRouteResumeAnimation(void);
void func_020c3024();

#endif /* FIELD_ACTORS_ACTOR_SAVE_FLASH_H */
