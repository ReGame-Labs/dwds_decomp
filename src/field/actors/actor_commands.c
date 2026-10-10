#include "field/actors/actor_commands.h"
#include "engine/data.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_files.h"
#include "m2c_macros.h"

/* Clears the 0x2 flag of the main screen's actor and zeroes fields 0x3C-0x4E
 * of the main screen's map scroll, MAIN_MAP_STATE. */
void func_020c2404(s32 index) {
    clearMainActorFlags(index, 2);
    M2C_FIELD(&MAIN_MAP_STATE, s32 *, 0x3C) = 0;
    M2C_FIELD(&MAIN_MAP_STATE, s32 *, 0x40) = 0;
    M2C_FIELD(&MAIN_MAP_STATE, s32 *, 0x44) = 0;
    M2C_FIELD(&MAIN_MAP_STATE, s32 *, 0x48) = 0;
    M2C_FIELD(&MAIN_MAP_STATE, s16 *, 0x4C) = 0;
    M2C_FIELD(&MAIN_MAP_STATE, s16 *, 0x4E) = 0;
}

/* The same for the sub screen's actor and SUB_MAP_STATE. */
void func_020c23c8(s32 index) {
    clearSubActorFlags(index, 2);
    M2C_FIELD(&SUB_MAP_STATE, s32 *, 0x3C) = 0;
    M2C_FIELD(&SUB_MAP_STATE, s32 *, 0x40) = 0;
    M2C_FIELD(&SUB_MAP_STATE, s32 *, 0x44) = 0;
    M2C_FIELD(&SUB_MAP_STATE, s32 *, 0x48) = 0;
    M2C_FIELD(&SUB_MAP_STATE, s16 *, 0x4C) = 0;
    M2C_FIELD(&SUB_MAP_STATE, s16 *, 0x4E) = 0;
}

/* Lets the main screen's actor turn to where it moves again. */
void freeMainActorFacing(s32 index) {
    clearMainActorFlags(index, ACTOR_FIXED_FACING);
}

/* Lets the sub screen's actor turn to where it moves again. */
void freeSubActorFacing(s32 index) {
    clearSubActorFlags(index, ACTOR_FIXED_FACING);
}

/* Keeps the main screen's actor facing the way it faces as it moves. */
void fixMainActorFacing(s32 index) {
    addMainActorFlags(index, ACTOR_FIXED_FACING);
}

/* Keeps the sub screen's actor facing the way it faces as it moves. */
void fixSubActorFacing(s32 index) {
    addSubActorFlags(index, ACTOR_FIXED_FACING);
}

/* Resumes the animation of the main screen's actor. */
void resumeMainActorAnimation(s32 index) {
    clearMainActorFlags(index, ACTOR_PAUSED_ANIMATION);
}

/* Resumes the animation of the sub screen's actor. */
void resumeSubActorAnimation(s32 index) {
    clearSubActorFlags(index, ACTOR_PAUSED_ANIMATION);
}

/* Pauses the animation of the main screen's actor. */
void pauseMainActorAnimation(s32 index) {
    addMainActorFlags(index, ACTOR_PAUSED_ANIMATION);
}

/* Pauses the animation of the sub screen's actor. */
void pauseSubActorAnimation(s32 index) {
    addSubActorFlags(index, ACTOR_PAUSED_ANIMATION);
}

/* Lets the main screen's actor go on with its state. */
void unfreezeMainActor(s32 index) {
    clearMainActorFlags(index, ACTOR_FROZEN);
}

/* Lets the sub screen's actor go on with its state. */
void unfreezeSubActor(s32 index) {
    clearSubActorFlags(index, ACTOR_FROZEN);
}

/* Freezes the main screen's actor: it stands whatever its state. */
void freezeMainActor(s32 index) {
    addMainActorFlags(index, ACTOR_FROZEN);
}

/* Freezes the sub screen's actor: it stands whatever its state. */
void freezeSubActor(s32 index) {
    addSubActorFlags(index, ACTOR_FROZEN);
}

/* Shows the main screen's actor again. */
void showMainActor(s32 index) {
    clearMainActorFlags(index, ACTOR_HIDDEN);
}

/* Shows the sub screen's actor again. */
void showSubActor(s32 index) {
    clearSubActorFlags(index, ACTOR_HIDDEN);
}

/* Hides the main screen's actor. */
void hideMainActor(s32 index) {
    addMainActorFlags(index, ACTOR_HIDDEN);
}

/* Hides the sub screen's actor. */
void hideSubActor(s32 index) {
    addSubActorFlags(index, ACTOR_HIDDEN);
}

/* Clears the 0x20000 flag of the main screen's actor. */
void func_020c22b8(s32 index) {
    clearMainActorFlags(index, 0x20000);
}

/* Clears the 0x20000 flag of the sub screen's actor. */
void func_020c22a8(s32 index) {
    clearSubActorFlags(index, 0x20000);
}

/* Sets the 0x20000 flag of the main screen's actor, with its unk28. */
void func_020c227c(s32 index) {
    struct Actor *actor;

    actor = getMainActor(index);
    if (actor == NULL) {
        return;
    }
    actor->unk28 = 1;
    addMainActorFlags(index, 0x20000);
}

/* Sets the 0x20000 flag of the sub screen's actor, with its unk28. */
void func_020c2250(s32 index) {
    struct Actor *actor;

    actor = getSubActor(index);
    if (actor == NULL) {
        return;
    }
    actor->unk28 = 1;
    addSubActorFlags(index, 0x20000);
}

/* Shows the second sprite of the main screen's actor again. */
void showMainActorExtra(s32 index) {
    clearMainActorFlags(index, ACTOR_EXTRA_HIDDEN);
}

/* Shows the second sprite of the sub screen's actor again. */
void showSubActorExtra(s32 index) {
    clearSubActorFlags(index, ACTOR_EXTRA_HIDDEN);
}

/* Hides the second sprite of the main screen's actor. */
void hideMainActorExtra(s32 index) {
    addMainActorFlags(index, ACTOR_EXTRA_HIDDEN);
}

/* Hides the second sprite of the sub screen's actor. */
void hideSubActorExtra(s32 index) {
    addSubActorFlags(index, ACTOR_EXTRA_HIDDEN);
}

/* Sets the OAM priority of the sub screen's actor and of its second sprite:
 * with a map shown, 2, 3 and 4 put it behind, at or before the map's priority.
 * It is never more than 3. */
void setSubActorPriority(s32 index, u16 priority) {
    struct Actor *actor;

    actor = getSubActor(index);
    if (actor == NULL) {
        return;
    }
    if (data_021ab7a8 != NULL) {
        switch (priority) {
            case 4:
                actor->unk80          = M2C_FIELD(data_021ab7a8, u16 *, 0x28) + 1;
                actor->extra.priority = M2C_FIELD(data_021ab7a8, u16 *, 0x28) + 1;
                break;
            case 3:
                actor->unk80          = M2C_FIELD(data_021ab7a8, u16 *, 0x28);
                actor->extra.priority = M2C_FIELD(data_021ab7a8, u16 *, 0x28);
                break;
            case 2:
                actor->unk80          = M2C_FIELD(data_021ab7a8, u16 *, 0x28) - 1;
                actor->extra.priority = M2C_FIELD(data_021ab7a8, u16 *, 0x28) - 1;
                break;
        }
    } else {
        actor->unk80          = priority;
        actor->extra.priority = priority;
    }
    if (actor->unk80 > 3) {
        actor->unk80          = 3;
        actor->extra.priority = 3;
    }
}

/* Sets unk82 of the sub screen's actor, the second argument of its sprite's
 * addSubOamEntry. */
void func_020c2070(u16 index, u16 value) {
    struct Actor *actor;

    actor = getSubActor(index);
    if (actor != NULL) {
        actor->unk82 = value;
    }
}
