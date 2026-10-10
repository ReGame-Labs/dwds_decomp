#ifndef ENGINE_MOVIE_MOVIE_PLAYER_H
#define ENGINE_MOVIE_MOVIE_PLAYER_H

#include "types.h"

/* The movie player: its task, its files and the ranges of frames it plays. */

s32 getFrameCount(void);
void countFrame(void);
u8 isMovieFrameShown(void);
void initMovieTaskPointer(void);
void clearMainScreen(void);
void stopMovie(void);
void initMovieBufferPointer(void);
void playMovie(s32 movie, s32 first, s32 last, s32 loops);
s32 loadMovieFiles(u16 movie);
void startMovieTask(s32 movie, s32 first, s32 last, s32 loops);
void freeMovieTask(void);
void startAfterEndMovieRange(u16 first, u16 last, s16 loops);
void startAfterLoopMovieRange(u16 first, u16 last, s16 loops);
void queueAfterLoopMovieRange(u16 first, u16 last, s16 loops);
void startNextMovieRange(u16 first, u16 last, s16 loops);
void queueNextMovieRange(u16 first, u16 last, s16 loops);
void switchMovie(u16 movie, u16 unused1, u16 unused2, s16 loops);

#endif /* ENGINE_MOVIE_MOVIE_PLAYER_H */
