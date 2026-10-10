#ifndef ENGINE_SAVE_GAME_STATE_H
#define ENGINE_SAVE_GAME_STATE_H

/* The save's counters: money, food, play time, the species' counts and
 * records of the Digimon kept. */

#include "engine/data.h"
#include "types.h"

/* The task that counts the play time (func_020a0130). */
struct PlayTimeTask {
    struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
};

BOOL func_020a01d8(s32 group);
s32 func_020a0268(s32 index);
void func_020a0278(s32 index);
s16 getHighestLevel(void);
void recordHighestLevel(void);
s32 func_020a03f0();
s16 func_020a0428(s32 value);
u32 func_020a04a0(s32 id);
u32 func_020a04c0(s32 id, s32 delta);
void func_020a0724(BOOL set);
s16 func_020a0754(void);
s16 func_020a07e8(s16 value);
u32 addMoney(s32 amount);
u8 func_020a0854(void);
s32 func_020a0864(s32 amount);
BOOL func_020a0894(void);
s32 func_020a0908();
s32 startPlayTimeClock(void);
void healDigimon(s32 id);
void *func_020a0258(s32 index);
s16 func_020a0288(s32 index);
void *func_020a0470(); /* (s32 id), left open for a caller that passes none */
s16 func_020a0980(s32 id, s32 amount);
s32 func_020a020c(void);
s16 func_020a02b0(void);
s32 func_020a0570(void);
u32 func_020a05e4(s32 id, s32 delta);
u32 func_020a0684(s32 id, s32 delta);
s32 func_020a0764(s32 delta);
s32 addFood(s32 amount);
void func_020a02f4();

#endif /* ENGINE_SAVE_GAME_STATE_H */
