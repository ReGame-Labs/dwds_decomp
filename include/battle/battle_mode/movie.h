#ifndef BATTLE_BATTLE_MODE_MOVIE_H
#define BATTLE_BATTLE_MODE_MOVIE_H

/* The battle's copy of engine/movie/movie_player.c: the same functions
 * built into the overlay, on the same task and buffer but with graphics of
 * their own (BATTLE_MOVIE_GRAPHICS). */

#include "types.h"

u8 isBattleMovieFrameShown(void);
void initBattleMovieTaskPointer(void);
void stopBattleMovie(void);
void initBattleMovieBufferPointer(void);
void playBattleMovie(s32 movie, s32 first, s32 last, s32 loops);
void func_ov002_02251500(u16 movie);
void func_ov002_02251794(s32 movie, s32 first, s32 last, s32 loops);
void freeBattleMovieTask(void);
void startAfterEndBattleMovieRange(u16 first, u16 last, s16 loops);
void startAfterLoopBattleMovieRange(u16 first, u16 last, s16 loops);
void queueAfterLoopBattleMovieRange(u16 first, u16 last, s16 loops);
void startNextBattleMovieRange(u16 first, u16 last, s16 loops);
void queueNextBattleMovieRange(u16 first, u16 last, s16 loops);
void switchBattleMovie(u16 movie, s32 first, s32 last, s16 loops);

#endif /* BATTLE_BATTLE_MODE_MOVIE_H */
