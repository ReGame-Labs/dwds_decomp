#ifndef ENGINE_SCRIPT_CMD_THREAD_H
#define ENGINE_SCRIPT_CMD_THREAD_H

/* The script engine's thread commands (start, children, waits), palette fade
 * ins, random numbers and global variable tests. */

#include "engine/data.h"
#include "types.h"

/* A task that wakes a script thread once something is over. */
struct ThreadWaitTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 wait;
    /* 0x24 */ s16 thread;
};

/* func_0208fae8's and func_0208fa98's task: shows a sprite for some frames,
 * then frees it and wakes its thread. */
struct TimedSpriteTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 wait;
    /* 0x24 */ s16 thread;
    /* 0x26 */ s16 frames;
    /* 0x28 */ s16 sprite;
};

void func_0208f788(s16 interval, s16 step);
void func_0208f7f8(s16 interval, s16 step);
s32 func_0208f868(struct ScriptThread *thread);
s32 func_0208f888(struct ScriptThread *thread);
s32 cmdWaitForChildSlot(struct ScriptThread *thread);
s32 func_0208fa20(struct ScriptThread *thread);
void func_0208fa98(void);
void func_0208fae8(void);
void func_0208fc90(void);
s32 func_0208f720(struct ScriptThread *thread);
s32 func_0208f754(struct ScriptThread *thread);
s32 func_0208f8a8(struct ScriptThread *thread);
s32 func_0208fdd8(struct ScriptThread *thread);
s32 cmdStartChildThread(struct ScriptThread *thread);
s32 cmdStartThread(struct ScriptThread *thread);
s32 func_0208fe94(struct ScriptThread *thread);
s32 func_0208ff08(struct ScriptThread *thread);
s32 func_0208fccc(struct ScriptThread *thread);
s32 func_0208fd5c(struct ScriptThread *thread);
s32 func_0208fe14(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_CMD_THREAD_H */
