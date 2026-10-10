#include "engine/system/system.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "nitro/gx.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"
#include "nitro/pad.h"

/* The task of the list's first and last tasks: does nothing. */
void tickEmptyTask(void) {}

/* Makes the game's two heaps of the main arena: 64 KB and the rest. */
void initHeaps(void) {
    u32 small;
    u32 arenaLo;
    u32 size;
    u32 main;

    small   = func_020e5000(0, 0x10000, 16);
    arenaLo = func_020e52cc(0);
    size    = (func_020e52e0(0) & ~0xF) - ((arenaLo + 0xF) & ~0xF);
    main    = func_020e5000(0, size, 16);

    SMALL_HEAP        = func_020b9068(small, 0x10000, 0);
    MAIN_HEAP         = func_020b9068(main, size, 0);
    HEAP_INITIAL_FREE = func_020b8fb0(MAIN_HEAP);
    HEAP_PEAK_USE     = 0;
}

/* Counts a block allocated from the main heap (heapAlloc). */
void countHeapBlockAllocated(void) {
    HEAP_BLOCK_COUNT++;
}

/* Counts a block of the main heap freed (heapFree). */
void countHeapBlockFreed(void) {
    HEAP_BLOCK_COUNT--;
}

/* The number of blocks of the main heap in use. */
s32 getHeapBlockCount(void) {
    return HEAP_BLOCK_COUNT;
}

/* The bytes of the main heap in use. */
s32 getHeapUsedSize(void) {
    return HEAP_INITIAL_FREE - func_020b8fb0(MAIN_HEAP);
}

/* Clears all of VRAM through the LCDC mapping, then the sprites and their
 * palettes of both screens. */
void clearVram(void) {
    disableVramBanks();
    func_020da7f0(0x1FF);
    MI_CpuClearFast((void *) HW_LCDC_VRAM, HW_LCDC_VRAM_SIZE);
    func_020da29c();
    clearSprites();
}

/* Clears both screens' sprites, moved below the screen, and their palettes. */
void clearSprites(void) {
    MI_CpuFillFast((void *) HW_OAM, 192, HW_OAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_PLTT, HW_OBJ_PLTT_SIZE);
    MI_CpuFillFast((void *) HW_DB_OAM, 192, HW_OAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_PLTT, HW_OBJ_PLTT_SIZE);
}

/* Takes every VRAM bank away from the screens (GX_DisableBankFor*). */
void disableVramBanks(void) {
    func_020da564();
    func_020da52c();
    func_020da4cc();
    func_020da550();
    func_020da508();
    func_020da4b8();
    func_020da47c();
    func_020da4a4();
    func_020da454();
    func_020da4f4();
    func_020da4e0();
}

/* Ends the main screen's fade, at full brightness. */
void endMainFade(void) {
    MAIN_FADE_FRAMES     = 0;
    MAIN_FADE_BRIGHTNESS = 0;
    MAIN_FADE_TARGET     = 0;
    MAIN_FADE_STEP       = 0;
    GX_SetMasterBrightness(0);
    endTaskById(MAIN_FADE_TASK_ID);
    MAIN_FADE_TASK_ID = 0;
}

/* Whether the main screen is fading. */
BOOL isMainFading(void) {
    if (MAIN_FADE_FRAMES != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Fades the main screen in from black over frames frames (at least one) by
 * the task tickMainFade, which replaces the fade going on. The brightness is
 * in 20.12 fixed point. */
void startMainFadeIn(s32 frames) {
    if (frames <= 0) {
        frames = 1;
    }
    MAIN_FADE_FRAMES     = frames;
    MAIN_FADE_BRIGHTNESS = -16 << 12;
    MAIN_FADE_TARGET     = 0;
    MAIN_FADE_STEP       = (16 << 12) / frames;
    endTaskById(MAIN_FADE_TASK_ID);
    MAIN_FADE_TASK_ID = getTaskId(createTask(tickMainFade, 0xF003));
}

/* The task of a fade of the main screen: steps its brightness each frame. */
void tickMainFade(void) {
    struct Task *task = (struct Task *) getCurrentTask();

    if (--MAIN_FADE_FRAMES == 0) {
        GX_SetMasterBrightness(MAIN_FADE_TARGET >> 12);
        endTask(task);
        MAIN_FADE_TASK_ID = 0;
    } else {
        MAIN_FADE_BRIGHTNESS += MAIN_FADE_STEP;
        GX_SetMasterBrightness(MAIN_FADE_BRIGHTNESS >> 12);
    }
}

/* Ends the sub screen's fade, at full brightness. */
void endSubFade(void) {
    SUB_FADE_FRAMES     = 0;
    SUB_FADE_BRIGHTNESS = 0;
    SUB_FADE_TARGET     = 0;
    SUB_FADE_STEP       = 0;
    GXS_SetMasterBrightness(0);
    endTaskById(SUB_FADE_TASK_ID);
    SUB_FADE_TASK_ID = 0;
}

/* Fades the sub screen in from black, by the task tickSubFade. */
void startSubFadeIn(s32 frames) {
    if (frames <= 0) {
        frames = 1;
    }
    SUB_FADE_FRAMES     = frames;
    SUB_FADE_BRIGHTNESS = -16 << 12;
    SUB_FADE_TARGET     = 0;
    SUB_FADE_STEP       = (16 << 12) / frames;
    endTaskById(SUB_FADE_TASK_ID);
    SUB_FADE_TASK_ID = getTaskId(createTask(tickSubFade, 0xF003));
}

/* The task of a fade of the sub screen. */
void tickSubFade(void) {
    struct Task *task = (struct Task *) getCurrentTask();

    if (--SUB_FADE_FRAMES == 0) {
        GXS_SetMasterBrightness(SUB_FADE_TARGET >> 12);
        endTask(task);
        SUB_FADE_TASK_ID = 0;
    } else {
        SUB_FADE_BRIGHTNESS += SUB_FADE_STEP;
        GXS_SetMasterBrightness(SUB_FADE_BRIGHTNESS >> 12);
    }
}

/* Sets up the sound: its heap and the sound archive. */
void initSound(void) {
    func_020bc2ec();
    SOUND_HEAP = func_020bdf6c(SOUND_HEAP_MEMORY, 0x5F000);
    func_020bdb90(&SOUND_ARCHIVE, PATH_SOUND_DATA, SOUND_HEAP, 0);
    if (func_020bedc8(SOUND_HEAP) == 0) {
        func_020e6250();
    }
    func_020c0020(10, SOUND_HEAP);
}

/* The sound's task, which main starts: calls the sound library each frame. */
void tickSound(void) {
    func_020bc2b8();
}

/* Clears both pads. */
void clearPads(void) {
    clearRawPad();
    clearGamePad();
}

/* The pads' task, which main starts. Reads the buttons into both pads, none while the lid is closed: the game's
 * pad leaves out the buttons masked off, and stays as it was while it is
 * switched off. */
void tickPads(void) {
    u16 keys = PAD_Read();

    if (PAD_DetectFold()) {
        keys = 0;
    }
    updatePad(&RAW_PAD, keys);
    if (GAME_PAD_DISABLED == 0) {
        updatePad(&GAME_PAD, keys & ~GAME_PAD_IGNORED_KEYS);
    }
}

/* Updates a pad from the buttons held: what was pressed and released, the
 * repeats and the double taps. */
void updatePad(struct Pad *pad, u16 keys) {
    pad->prevHeld = pad->held;
    pad->held     = keys;
    pad->pressed  = ~pad->prevHeld & pad->held;
    pad->released = ~pad->held & pad->prevHeld;

    if (pad->held != pad->prevHeld) {
        pad->holdFrames = 0;
    } else if (pad->holdFrames < 16) {
        pad->holdFrames++;
    }
    pad->fastRepeat = pad->holdFrames >= 16 ? pad->held : pad->pressed;

    if (pad->held != pad->prevHeld) {
        pad->longHoldFrames = 0;
    } else if (pad->holdFrames >= 16 && pad->longHoldFrames < 60) {
        pad->longHoldFrames++;
    }
    pad->longHeld = pad->longHoldFrames >= 60 ? pad->held : 0;

    if (pad->held != pad->prevHeld) {
        pad->repeatFrames = 0;
    } else if (pad->holdFrames >= 16) {
        pad->repeatFrames++;
    }
    pad->repeat = pad->repeatFrames >= 4 ? pad->held : pad->pressed;
    if (pad->repeatFrames >= 4) {
        pad->repeatFrames = 0;
    }

    switch (pad->doubleTapState) {
        case 0:
            if (pad->pressed != 0) {
                pad->doubleTapKeys   = pad->pressed;
                pad->doubleTapFrames = 0;
                pad->doubleTapState  = 1;
            }
            break;
        case 1:
            pad->doubleTapFrames++;
            if (pad->doubleTapFrames > 20) {
                pad->doubleTapFrames = 0;
                pad->doubleTapState  = 0;
            } else if (pad->doubleTapKeys == pad->pressed) {
                pad->doubleTap       = pad->doubleTapKeys;
                pad->doubleTapFrames = 0;
                pad->doubleTapState  = 2;
            }
            break;
        case 2:
            pad->doubleTap       = 0;
            pad->doubleTapFrames = 0;
            pad->doubleTapState  = 0;
            break;
    }
}

/* Clears the pad of all the buttons. */
void clearRawPad(void) {
    func_020e23c0(&RAW_PAD, 0, sizeof(struct Pad));
}

/* Clears the game's pad. */
void clearGamePad(void) {
    func_020e23c0(&GAME_PAD, 0, sizeof(struct Pad));
}

/* Switches the game's pad off (nonzero) or on. */
void setPadDisabled(s32 off) {
    GAME_PAD_DISABLED = off;
}

/* The game pad's buttons held. */
u16 getPadHeld(void) {
    return GAME_PAD.held;
}

/* The game pad's buttons pressed this frame. */
u16 getPadPressed(void) {
    return GAME_PAD.pressed;
}

/* The game pad's buttons let go this frame. */
u16 getPadReleased(void) {
    return GAME_PAD.released;
}

/* The game pad's buttons that repeat this frame, at the fast rate. */
u16 getPadFastRepeat(void) {
    return GAME_PAD.fastRepeat;
}

/* The game pad's buttons that repeat this frame. */
u16 getPadRepeat(void) {
    return GAME_PAD.repeat;
}

/* The game pad's buttons pressed twice in a row. */
u16 getPadDoubleTap(void) {
    return GAME_PAD.doubleTap;
}

/* A random number below range (below 1 for 0), from a linear congruential
 * generator. */
u16 getRandom(u32 range) {
    if (range == 0) {
        range = 1;
    }
    RANDOM_SEED = RANDOM_SEED * 7 + 5;
    return (RANDOM_SEED >> 16) % range;
}

/* A random number from -(range - 1) to range - 1. */
s32 getRandomSigned(u32 range) {
    s32 value = getRandom(range);

    if (getRandom(2) == 0) {
        value = -value;
    }
    return value;
}

/* The angle, in degrees, turned by delta and brought back into 0-359. */
s32 wrapAngle(s32 angle, s32 delta) {
    angle += delta;
    while (angle < 0 || angle >= 360) {
        if (angle >= 360) {
            angle -= 360;
        } else if (angle < 0) {
            angle += 360;
        }
    }
    return angle;
}

/* Empties the task list: only its first and last tasks, which do nothing, take
 * a slot. Written on the slots by name, not through pointers: mwcc then reads
 * the next id and the free slots' top only once. */
void initTasks(void) {
    s32 i;

    for (i = 0; i < 80; i++) {
        FREE_TASK_SLOTS[i] = &TASK_SLOTS[i].task;
    }
    FREE_TASK_SLOTS[0]          = NULL;
    TASK_SLOTS[0].task.run      = tickEmptyTask;
    TASK_SLOTS[0].task.priority = 0;
    TASK_SLOTS[0].task.prev     = NULL;
    TASK_SLOTS[0].task.next     = &TASK_SLOTS[1].task;
    TASK_SLOTS[0].task.id       = NEXT_TASK_ID++;
    FREE_TASK_SLOTS[1]          = NULL;
    FREE_TASK_SLOTS_TOP += 2;
    TASK_SLOTS[1].task.run      = tickEmptyTask;
    TASK_SLOTS[1].task.priority = 0xFFFF;
    TASK_SLOTS[1].task.prev     = &TASK_SLOTS[0].task;
    TASK_SLOTS[1].task.next     = NULL;
    TASK_SLOTS[1].task.id       = NEXT_TASK_ID++;
    CURRENT_TASK                = &TASK_SLOTS[0].task;
}

/* Runs the tasks once, then removes the ended ones and counts the others. */
void runTasks(void) {
    for (CURRENT_TASK = getTaskList()->next; CURRENT_TASK->next != NULL; CURRENT_TASK = CURRENT_TASK->next) {
        if (CURRENT_TASK->ended == 0) {
            CURRENT_TASK->run();
        }
    }
    removeEndedTasks();
    countTasks();
}

/* Unlinks the ended tasks, calls their onEnd, clears their slots and frees
 * them. */
void removeEndedTasks(void) {
    struct Task *next;

    for (CURRENT_TASK = getTaskList()->next; CURRENT_TASK->next != NULL; CURRENT_TASK = next) {
        next = CURRENT_TASK->next;
        if (CURRENT_TASK->ended == TRUE) {
            CURRENT_TASK->prev->next = next;
            CURRENT_TASK->next->prev = CURRENT_TASK->prev;
            if (CURRENT_TASK->onEnd != NULL) {
                CURRENT_TASK->onEnd(CURRENT_TASK);
            }
            func_020e23c0(CURRENT_TASK, 0, sizeof(struct TaskSlot));
            *--FREE_TASK_SLOTS_TOP = CURRENT_TASK;
        }
    }
}

/* Counts the tasks in the list, but not the first and last. */
void countTasks(void) {
    TASK_COUNT = 0;
    for (CURRENT_TASK = getTaskList()->next; CURRENT_TASK->next != NULL; CURRENT_TASK = CURRENT_TASK->next) {
        TASK_COUNT++;
    }
}

/* Starts a task: takes a free slot and links it in before the first task of a
 * higher priority. The game stops if no slot is free. Ids go on from 2 once
 * they wrap: the first and last tasks keep theirs. */
void *createTask(void (*run)(void), u32 priority) {
    struct Task *task;
    struct Task *list = getTaskList();

    if (FREE_TASK_SLOTS_TOP == &FREE_TASK_SLOTS[80]) {
        func_020e6250();
    }
    /* Cleared through the old top before it moves, as the code does. */
    task                 = *FREE_TASK_SLOTS_TOP;
    *FREE_TASK_SLOTS_TOP = NULL;
    FREE_TASK_SLOTS_TOP++;
    task->run      = run;
    task->priority = priority;
    task->id       = NEXT_TASK_ID++;
    if (NEXT_TASK_ID == 0) {
        NEXT_TASK_ID = 2;
    }
    for (;;) {
        if (list->priority > priority) {
            task->next       = list;
            task->prev       = list->prev;
            list->prev->next = task;
            list->prev       = task;
            return task;
        }
        list = list->next;
    }
}

/* Ends a task: it is removed from the list at the end of the frame. */
void endTask(void *task) {
    if (task != NULL) {
        ((struct Task *) task)->ended = TRUE;
    }
}

/* Ends the task of an id, but not the first or last. */
void endTaskById(u32 id) {
    if (id <= 1) {
        return;
    }
    endTask(findTask(id));
}

/* Ends the tasks whose priority is from min to max. The loops test at the
 * top: written as while loops, mwcc moves their tests to the bottom. */
void endTasksInRange(u32 min, u32 max) {
    struct Task *task = getTaskList()->next;

    for (;;) {
        if (task->priority >= min) {
            break;
        }
        task = task->next;
    }
    for (;;) {
        if (task->priority > max || task->next == NULL) {
            break;
        }
        task->ended = TRUE;
        task        = task->next;
    }
}

/* Ends the tasks of a priority. */
void endTasksOfPriority(u32 priority) {
    endTasksInRange(priority, priority);
}

/* The task running. */
struct Task *getCurrentTask(void) {
    return CURRENT_TASK;
}

/* The task list: its first task. */
struct Task *getTaskList(void) {
    return &TASK_SLOTS[0].task;
}

/* The task of an id, or NULL. */
void *findTask(s32 id) {
    struct Task *task = getTaskList()->next;
    struct Task *next;

    for (next = task->next; next != NULL; next = next->next) {
        if (task->id == id) {
            return task;
        }
        task = next;
    }
    return NULL;
}

/* A task's id, 0 for none. */
s32 getTaskId(void *task) {
    if (task != NULL) {
        return ((struct Task *) task)->id;
    }
    return 0;
}
