#include "engine/movie/movie_player.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/display_modes.h"
#include "engine/system/setup.h"
#include "engine/system/system.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Clears the movie's buffer pointer, the first time a movie plays. */
void initMovieBufferPointer(void) {
    if (isSystemSetUp(SYSTEM_MOVIE_BUFFER) != 0) {
        return;
    }
    setSystemSetUp(SYSTEM_MOVIE_BUFFER);
    MOVIE_BUFFER = 0;
}

/* Plays a movie's frames from first to last, loops times (-1 for ever). */
void playMovie(s32 movie, s32 first, s32 last, s32 loops) {
    func_020a3454(3);
    startMovieTask(movie, first, last, loops);
    loadMovieFiles(movie);
}

/* Stops the movie at the end of the frame. */
void stopMovie(void) {
    struct MovieTask *task = MOVIE_TASK;

    if (task != NULL) {
        task->stop = TRUE;
    }
}

/* The movie task's end: frees what it read and clears the main screen. */
void freeMovieTask(void) {
    void *buffer;

    MOVIE_TASK = NULL;
    heapFree(MOVIE_BUFFER);
    MOVIE_BUFFER = 0;
    buffer       = MOVIE_GRAPHICS[0];
    if (buffer != NULL) {
        heapFree(buffer);
        MOVIE_GRAPHICS[0] = NULL;
    }
    buffer = MOVIE_GRAPHICS[2];
    if (buffer != NULL) {
        heapFree(buffer);
        MOVIE_GRAPHICS[2] = NULL;
    }
    clearMainScreen();
}

/* Clears the main screen's backgrounds and sprites. */
void clearMainScreen(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
}

/* Clears the movie's task pointer, the first time a movie plays. */
void initMovieTaskPointer(void) {
    if (isSystemSetUp(SYSTEM_MOVIE_TASK) != 0) {
        return;
    }
    setSystemSetUp(SYSTEM_MOVIE_TASK);
    MOVIE_TASK = NULL;
}

/* Plays a range of the movie from its next frame. */
void queueNextMovieRange(u16 first, u16 last, s16 loops) {
    struct MovieTask *task = MOVIE_TASK;

    if (task != NULL) {
        task->next.first = first;
        task->next.last  = last;
        task->next.loops = loops;
        task->hasNext    = TRUE;
    }
}

/* Plays a range of the movie at once: the task's switch to its next range.
 * startAfterLoopMovieRange and startAfterEndMovieRange, the same code, switch to the ranges after
 * a loop and after the last loop. */
void startNextMovieRange(u16 first, u16 last, s16 loops) {
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
void queueAfterLoopMovieRange(u16 first, u16 last, s16 loops) {
    struct MovieTask *task = MOVIE_TASK;

    if (task != NULL) {
        task->afterLoop.first = first;
        task->afterLoop.last  = last;
        task->afterLoop.loops = loops;
        task->hasAfterLoop    = TRUE;
    }
}

/* Plays a range of the movie from its first frame (when a range has looped). */
void startAfterLoopMovieRange(u16 first, u16 last, s16 loops) {
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

/* Plays a range of the movie from its first frame (when a range has ended). */
void startAfterEndMovieRange(u16 first, u16 last, s16 loops) {
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

/* Switches to another movie, read again from its first frame; unused1 and
 * unused2 are not used. */
void switchMovie(u16 movie, u16 unused1, u16 unused2, s16 loops) {
    struct MovieTask *task = MOVIE_TASK;
    void *buffer;

    task->state      = 0xFF;
    task->frame      = 0;
    task->frameCount = 30;
    task->loops      = loops;
    buffer           = MOVIE_GRAPHICS[0];
    if (buffer != NULL) {
        heapFree(buffer);
        MOVIE_GRAPHICS[0] = NULL;
    }
    buffer = MOVIE_GRAPHICS[2];
    if (buffer != NULL) {
        heapFree(buffer);
        MOVIE_GRAPHICS[2] = NULL;
    }
    loadMovieFiles(movie);
}

/* Whether the movie's frame has been shown, or no movie plays. */
u8 isMovieFrameShown(void) {
    if (MOVIE_TASK != NULL) {
        return MOVIE_TASK->frameShown;
    }
    return TRUE;
}

/* Counts a frame. */
void countFrame(void) {
    FRAME_COUNT++;
}

/* The frames counted since the game started. */
s32 getFrameCount(void) {
    return FRAME_COUNT;
}
