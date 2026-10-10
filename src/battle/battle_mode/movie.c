#include "battle/battle_mode/movie.h"
#include "battle/battle_mode/data.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"

/* Forgets the movie's buffer. */
void initBattleMovieBufferPointer(void) {
    MOVIE_BUFFER = NULL;
}

/* Plays a movie's frames from first to last, loops times (-1 for ever). */
void playBattleMovie(s32 movie, s32 first, s32 last, s32 loops) {
    func_ov002_02251794(movie, first, last, loops);
    func_ov002_02251500(movie);
}

/* Stops the movie at the end of the frame. */
void stopBattleMovie(void) {
    struct MovieTask *task = MOVIE_TASK;

    if (task != NULL) {
        task->stop = TRUE;
    }
}

/* Called when the movie's task is removed: frees what it read. */
void freeBattleMovieTask(void) {
    void *block;

    MOVIE_TASK = NULL;
    block      = MOVIE_BUFFER;
    heapFree(block);
    MOVIE_BUFFER = NULL;

    block = BATTLE_MOVIE_GRAPHICS[0];
    if (block != NULL) {
        heapFree(block);
        BATTLE_MOVIE_GRAPHICS[0] = NULL;
    }

    block = BATTLE_MOVIE_GRAPHICS[2];
    if (block != NULL) {
        heapFree(block);
        BATTLE_MOVIE_GRAPHICS[2] = NULL;
    }
}

/* Forgets the movie's task. */
void initBattleMovieTaskPointer(void) {
    MOVIE_TASK = NULL;
}

/* Plays a range of the movie from its next frame. */
void queueNextBattleMovieRange(u16 first, u16 last, s16 loops) {
    struct MovieTask *task = MOVIE_TASK;

    if (task != NULL) {
        task->next.first = first;
        task->next.last  = last;
        task->next.loops = loops;
        task->hasNext    = TRUE;
    }
}

/* Starts the range queued for the next frame, from its first frame. */
void startNextBattleMovieRange(u16 first, u16 last, s16 loops) {
    struct MovieTask *task = MOVIE_TASK;

    if (task == NULL) {
        return;
    }
    task->firstFrame = first;
    task->lastFrame  = last;
    task->frame      = first;
    task->loops      = loops;
    task->loopsDone  = 0;
    task->stop       = FALSE;
}

/* Plays a range of the movie once the range playing ends. */
void queueAfterLoopBattleMovieRange(u16 first, u16 last, s16 loops) {
    struct MovieTask *task = MOVIE_TASK;

    if (task != NULL) {
        task->afterLoop.first = first;
        task->afterLoop.last  = last;
        task->afterLoop.loops = loops;
        task->hasAfterLoop    = TRUE;
    }
}

/* Starts the range queued for after the loop. */
void startAfterLoopBattleMovieRange(u16 first, u16 last, s16 loops) {
    struct MovieTask *task = MOVIE_TASK;

    if (task == NULL) {
        return;
    }
    task->firstFrame = first;
    task->lastFrame  = last;
    task->frame      = first;
    task->loops      = loops;
    task->loopsDone  = 0;
    task->stop       = FALSE;
}

/* Starts the range queued for after the last loop. */
void startAfterEndBattleMovieRange(u16 first, u16 last, s16 loops) {
    struct MovieTask *task = MOVIE_TASK;

    if (task == NULL) {
        return;
    }
    task->firstFrame = first;
    task->lastFrame  = last;
    task->frame      = first;
    task->loops      = loops;
    task->loopsDone  = 0;
    task->stop       = FALSE;
}

/* Switches to another movie, read again from its first frame: first and last
 * are not used. */
void switchBattleMovie(u16 movie, s32 first, s32 last, s16 loops) {
    struct MovieTask *task = MOVIE_TASK;
    void *block;

    task->state      = 0xFF;
    task->frame      = 0;
    task->frameCount = 30;
    task->loops      = loops;

    block = BATTLE_MOVIE_GRAPHICS[0];
    if (block != NULL) {
        heapFree(block);
        BATTLE_MOVIE_GRAPHICS[0] = NULL;
    }

    block = BATTLE_MOVIE_GRAPHICS[2];
    if (block != NULL) {
        heapFree(block);
        BATTLE_MOVIE_GRAPHICS[2] = NULL;
    }
    func_ov002_02251500(movie);
}

/* Whether the movie's frame has been shown, or no movie plays. */
u8 isBattleMovieFrameShown(void) {
    if (MOVIE_TASK != NULL) {
        return MOVIE_TASK->frameShown;
    }
    return TRUE;
}
