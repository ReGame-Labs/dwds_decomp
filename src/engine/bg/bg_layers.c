#include "engine/bg/bg_layers.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "nitro/g2.h"

/* Writes params's tiles to its BG layer of the main screen. */
struct BgData *copyMainBgScreen(u8 *params) {
    s32 screen;

    screen = getMainBgScreen(*params);
    return func_020868a0(params, screen, getMainBgScreenSize(*params));
}

/* Writes params's tiles to its BG layer of the sub screen. */
struct BgData *copySubBgScreen(u8 *params) {
    s32 screen;

    screen = getSubBgScreen(*params);
    return func_020868a0(params, screen, getSubBgScreenSize(*params));
}

/* Runs func_0208644c on the main screen's BG layer. */
void func_02086608(s32 layer, s32 arg1, s32 arg2, s32 arg3, s16 arg4, s32 arg5) {
    s32 screen;

    screen = getMainBgScreen();
    func_0208644c(arg1, arg2, arg3, arg4, arg5, screen, getMainBgScreenSize(layer));
}

/* Runs func_0208644c on the sub screen's BG layer. */
void func_020865b4(s32 layer, s32 arg1, s32 arg2, s32 arg3, s16 arg4, s32 arg5) {
    s32 screen;

    screen = getSubBgScreen();
    func_0208644c(arg1, arg2, arg3, arg4, arg5, screen, getSubBgScreenSize(layer));
}

/* The offset in bytes of tile (x, y) in a BG screen of the given size: the
 * screen is made of 32x32 tile blocks. */
s32 getBgScreenOffset(s32 size, s32 x, s32 y) {
    s32 offset;

    offset = ((x & 0x1F) + ((y & 0x1F) << 5)) * 2;
    if ((x & 0x3F) > 0x1F) {
        offset += BG_SCREEN_RIGHT_OFFSETS[size * 4];
    }
    if ((y & 0x3F) > 0x1F) {
        offset += BG_SCREEN_LOWER_OFFSETS[size * 4];
    }
    return offset;
}

/* As getBgScreenOffset, for a map whose rows are width tiles long. */
s32 getBgMapOffset(s32 size, s32 x, s32 y, s32 width) {
    s32 offset;

    offset = (((y & 0x1F) * width) + (x & 0x1F)) * 2;
    if ((x & 0x3F) > 0x1F) {
        offset += BG_SCREEN_RIGHT_OFFSETS[size * 4];
    }
    if ((y & 0x3F) > 0x1F) {
        offset += BG_SCREEN_LOWER_OFFSETS[size * 4];
    }
    return offset;
}

/* Loads a BG layer of the main screen (loadMainBg) and flushes its data. */
struct BgData *loadMainBgAndFlush(void *params) {
    struct BgData *data;

    data = loadMainBg(params);
    if (data != NULL) {
        func_020e4f58(data->data, data->unk0 * data->unk2);
    }
    return data;
}

/* Loads a BG layer of the sub screen (loadSubBg) and flushes its data. */
struct BgData *loadSubBgAndFlush(void *params) {
    struct BgData *data;

    data = loadSubBg(params);
    if (data != NULL) {
        func_020e4f58(data->data, data->unk0 * data->unk2);
    }
    return data;
}

/* Writes the BG layers' offsets to the registers, at VBlank; BG 2 and 3 only
 * when isMainBg2Affine and the like say so. */
void applyBgOffsets(void) {
    REG_BG0OFS = (MAIN_BG_OFFSETS[0].x & BG_OFFSET_MASK) | (0x01FF0000 & (MAIN_BG_OFFSETS[0].y << 0x10));
    REG_BG1OFS = (MAIN_BG_OFFSETS[1].x & BG_OFFSET_MASK) | (0x01FF0000 & (MAIN_BG_OFFSETS[1].y << 0x10));
    if (isMainBg2Affine() == 0) {
        REG_BG2OFS = (MAIN_BG_OFFSETS[2].x & BG_OFFSET_MASK) | (0x01FF0000 & (MAIN_BG_OFFSETS[2].y << 0x10));
    }
    if (isMainBg3Affine() == 0) {
        REG_BG3OFS = (MAIN_BG_OFFSETS[3].x & BG_OFFSET_MASK) | (0x01FF0000 & (MAIN_BG_OFFSETS[3].y << 0x10));
    }
    REG_DB_BG0OFS = (SUB_BG_OFFSETS[0].x & BG_OFFSET_MASK) | (0x01FF0000 & (SUB_BG_OFFSETS[0].y << 0x10));
    REG_DB_BG1OFS = (SUB_BG_OFFSETS[1].x & BG_OFFSET_MASK) | (0x01FF0000 & (SUB_BG_OFFSETS[1].y << 0x10));
    if (isSubBg2Affine() == 0) {
        REG_DB_BG2OFS = (SUB_BG_OFFSETS[2].x & BG_OFFSET_MASK) | (0x01FF0000 & (SUB_BG_OFFSETS[2].y << 0x10));
    }
    if (isSubBg3Affine() != 0) {
        return;
    }
    REG_DB_BG3OFS = (SUB_BG_OFFSETS[3].x & BG_OFFSET_MASK) | (0x01FF0000 & (SUB_BG_OFFSETS[3].y << 0x10));
}

/* Sets the bases of the main screen's VRAM stacks and empties them, then
 * empties its top stacks (initMainVramTopStacks). */
void initMainVramStacks(s16 base0, s16 base1, s16 base2, s16 base3, s16 base4) {
    MAIN_VRAM_STACKS[0].base  = base0;
    MAIN_VRAM_STACKS[1].base  = base1;
    MAIN_VRAM_STACKS[2].base  = base2;
    MAIN_VRAM_STACKS[3].base  = base3;
    MAIN_VRAM_STACKS[0].count = 0;
    MAIN_VRAM_STACKS[1].count = 0;
    MAIN_VRAM_STACKS[2].count = 0;
    MAIN_VRAM_STACKS[3].count = 0;
    MAIN_VRAM_STACKS[4].count = 0;
    MAIN_VRAM_STACKS[4].base  = base4;
    initMainVramTopStacks(VRAM_STACK_TOP, VRAM_STACK_TOP, VRAM_STACK_TOP, VRAM_STACK_TOP, VRAM_STACK_TOP);
}

/* Sets the bases of the sub screen's VRAM stacks and empties them, then
 * empties its top stacks (initSubVramTopStacks). */
void initSubVramStacks(s16 base0, s16 base1, s16 base2, s16 base3, s16 base4) {
    SUB_VRAM_STACKS[0].base  = base0;
    SUB_VRAM_STACKS[1].base  = base1;
    SUB_VRAM_STACKS[2].base  = base2;
    SUB_VRAM_STACKS[3].base  = base3;
    SUB_VRAM_STACKS[0].count = 0;
    SUB_VRAM_STACKS[1].count = 0;
    SUB_VRAM_STACKS[2].count = 0;
    SUB_VRAM_STACKS[3].count = 0;
    SUB_VRAM_STACKS[4].count = 0;
    SUB_VRAM_STACKS[4].base  = base4;
    initSubVramTopStacks(VRAM_STACK_TOP, VRAM_STACK_TOP, VRAM_STACK_TOP, VRAM_STACK_TOP, VRAM_STACK_TOP);
}

/* Sets the bases of the main screen's top VRAM stacks and empties them. */
void initMainVramTopStacks(s16 base0, s16 base1, s16 base2, s16 base3, s16 base4) {
    MAIN_VRAM_TOP_STACKS[0].count = 0;
    MAIN_VRAM_TOP_STACKS[0].base  = base0;
    MAIN_VRAM_TOP_STACKS[1].count = 0;
    MAIN_VRAM_TOP_STACKS[1].base  = base1;
    MAIN_VRAM_TOP_STACKS[2].count = 0;
    MAIN_VRAM_TOP_STACKS[2].base  = base2;
    MAIN_VRAM_TOP_STACKS[3].count = 0;
    MAIN_VRAM_TOP_STACKS[3].base  = base3;
    MAIN_VRAM_TOP_STACKS[4].count = 0;
    MAIN_VRAM_TOP_STACKS[4].base  = base4;
}

/* Sets the bases of the sub screen's top VRAM stacks and empties them. */
void initSubVramTopStacks(s16 base0, s16 base1, s16 base2, s16 base3, s16 base4) {
    SUB_VRAM_TOP_STACKS[0].count = 0;
    SUB_VRAM_TOP_STACKS[0].base  = base0;
    SUB_VRAM_TOP_STACKS[1].count = 0;
    SUB_VRAM_TOP_STACKS[1].base  = base1;
    SUB_VRAM_TOP_STACKS[2].count = 0;
    SUB_VRAM_TOP_STACKS[2].base  = base2;
    SUB_VRAM_TOP_STACKS[3].count = 0;
    SUB_VRAM_TOP_STACKS[3].base  = base3;
    SUB_VRAM_TOP_STACKS[4].count = 0;
    SUB_VRAM_TOP_STACKS[4].base  = base4;
}

/* Starts the sound task, loads sound group 0 and keeps the sound heap's level. */
void startSoundTask(void) {
    struct SoundTask *task;

    task = createTask(runSoundTask, 0xF000);
    func_020bcc74(&task->bgmHandle);
    func_020bcc74(&task->soundHandle);
    func_020bcc74(&task->groupSoundHandle);
    SOUND_TASK_ID    = task->task.id;
    task->state      = SOUND_TASK_RUN;
    task->bgm        = SOUND_NONE;
    task->nextBgm    = SOUND_NONE;
    task->sound      = SOUND_NONE;
    task->nextSound  = SOUND_NONE;
    task->soundGroup = SOUND_NONE;
    task->unk38      = 1;
    task->fadeTimer  = 0;
    task->fadeFrames = SOUND_FADE_FRAMES;
    task->baseLevel  = -1;
    task->bgmLevel   = -1;
    task->soundLevel = -1;
    func_020bea90(0, SOUND_HEAP);
    func_020bea58(0, SOUND_HEAP);
    task->baseLevel = func_020bddc8(SOUND_HEAP);
}

/* Plays a BGM, fading the one playing out first. */
void playBgm(s16 bgm) {
    struct SoundTask *task;

    task = getSoundTask();
    if (task->bgm == bgm) {
        return;
    }
    task->nextBgm = bgm;
    stopSound();
    unloadSoundGroup();
}

/* Fades the BGM out. */
void stopBgm(void) {
    struct SoundTask *task;

    task = getSoundTask();
    if (task->bgm == SOUND_NONE) {
        return;
    }
    task->nextBgm = SOUND_STOP;
    stopSound();
    unloadSoundGroup();
}

/* Has the sound task pass 1 to func_020bcc80. */
void func_02085160(void) {
    struct SoundTask *task;

    task        = getSoundTask();
    task->state = SOUND_TASK_SET_UNK38;
    task->unk38 = 1;
}

/* Has the sound task pass 0 to func_020bcc80. */
void func_02085130(void) {
    struct SoundTask *task;

    task        = getSoundTask();
    task->state = SOUND_TASK_SET_UNK38;
    task->unk38 = 0;
}

/* The BGM playing, or SOUND_NONE. */
s16 getBgm(void) {
    return getSoundTask()->bgm;
}

/* Plays a sound beside the BGM. */
void playSound(s16 sound) {
    getSoundTask()->nextSound = sound;
}

/* Stops the sound playing beside the BGM. */
void stopSound(void) {
    getSoundTask()->nextSound = SOUND_STOP;
}

/* Loads a sound's group into the sound heap, unloading the last one. */
void loadSoundGroup(s16 group) {
    s16 loaded;
    struct SoundTask *task;

    task   = getSoundTask();
    loaded = task->soundGroup;
    if (group == loaded) {
        return;
    }
    if (loaded != SOUND_NONE) {
        unloadSoundGroup();
    }
    func_020bea90(0, SOUND_HEAP);
    func_020bea58(group, SOUND_HEAP);
    task->soundLevel = func_020bddc8(SOUND_HEAP);
    task->soundGroup = group;
}

/* Unloads the sound's group from the sound heap. */
void unloadSoundGroup(void) {
    struct SoundTask *task;

    task = getSoundTask();
    if (task->soundGroup == SOUND_NONE) {
        return;
    }
    func_020bdcdc(SOUND_HEAP, task->soundLevel - 1);
    task->soundGroup = SOUND_NONE;
    task->soundLevel = -1;
}
