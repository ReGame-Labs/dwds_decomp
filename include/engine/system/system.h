#ifndef ENGINE_SYSTEM_SYSTEM_H
#define ENGINE_SYSTEM_SYSTEM_H

#include "engine/data.h"
#include "engine/libs.h"
#include "engine/ui/buttons.h"
#include "types.h"

/* The game's systems: the tasks, the random numbers, the pads, the sound,
 * the screens' fades, the loading of files, the VRAM and the heaps. */

struct NNSG2dPaletteData;
struct Pad;
struct ScreenData;
struct Task;

s32 getTaskId(void *task);
struct Task *getTaskList(void);
void endTasksOfPriority(u32 priority);
void endTasksInRange(u32 min, u32 max);
void endTask(void *task);
void tickEmptyTask(void);
void countTasks(void);
void removeEndedTasks(void);
void runTasks(void);
void initTasks(void);
u16 getRandom(u32 range);
u16 getPadDoubleTap(void);
u16 getPadRepeat(void);
u16 getPadFastRepeat(void);
u16 getPadReleased(void);
u16 getPadPressed(void);
void setPadDisabled(s32 off);
void clearGamePad(void);
void clearRawPad(void);
void updatePad(struct Pad *pad, u16 keys);
void tickPads(void);
void clearPads(void);
void tickSound(void);
void initSound(void);
BOOL isMainFading(void);
s32 loadTempScreenFile();
void *loadScreenFile(struct ScreenData **screen, const char *path);
s32 loadTempPaletteFile();
void *loadPaletteFile(struct NNSG2dPaletteData **palette, const char *path);
s32 loadTempCharFile();
void *loadCharFile(void **chars, const char *path);
void disableVramBanks(void);
void clearSprites(void);
void clearVram(void);
s32 getHeapUsedSize(void);
s32 getHeapBlockCount(void);
void countHeapBlockFreed(void);
void countHeapBlockAllocated(void);
void endTaskById(); /* (u32 id), left open for a caller that passes none */
void *createTask();
void initHeaps(void);
struct Task *getCurrentTask(void);
void tickSubFade(void);
void startSubFadeIn(s32 frames);
void endSubFade(void);
void startMainFadeIn(s32 frames);
void endMainFade(void);
void tickMainFade(void);
s32 getRandomSigned(u32 range);
u16 getPadHeld(void);
void *findTask(s32 id);
s32 wrapAngle(s32 angle, s32 delta);

/* Allocates a block of the main heap and counts it among the blocks in use
 * (countHeapBlockAllocated); while isFieldOverlayLoaded is set it also keeps the most the heap
 * has had in use. The game inlines it wherever it allocates. */
static inline void *heapAlloc(u32 size, s32 align) {
    void *block;
    u32 used;

    block = (void *) func_020b9018(MAIN_HEAP, size, align);
    if (block != NULL) {
        countHeapBlockAllocated();
    }
    if (isFieldOverlayLoaded()) {
        used          = getHeapUsedSize();
        HEAP_PEAK_USE = used > HEAP_PEAK_USE ? used : HEAP_PEAK_USE;
    }
    return block;
}

/* Frees a block of the main heap and counts it off the blocks in use
 * (countHeapBlockFreed). The game inlines it wherever it frees, so a caller that
 * tests the pointer first tests it twice. */
static inline void heapFree(void *block) {
    if (block != NULL) {
        countHeapBlockFreed();
    }
    func_020b8fd8(MAIN_HEAP, block);
}

#endif /* ENGINE_SYSTEM_SYSTEM_H */
