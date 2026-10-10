#ifndef ENGINE_BG_BG_LAYERS_H
#define ENGINE_BG_BG_LAYERS_H

#include "engine/data.h"
#include "engine/system/system.h"
#include "types.h"

/* What the screen writer func_020868a0 returns, and the BG layer loaders
 * with it: unk0 * unk2 bytes of data, which the callers flush to memory. */
/* The sound task (runSoundTask) plays the BGM and a sound beside it from the
 * requests it is given, loading what they need into the sound heap
 * SOUND_HEAP and keeping the heap's levels to unload it. */
struct SoundTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;      /* enum SoundTaskState */
    /* 0x1E */ s16 bgm;        /* playing, or SOUND_NONE */
    /* 0x20 */ s16 nextBgm;    /* to play, SOUND_NONE or SOUND_STOP */
    /* 0x22 */ s16 sound;      /* playing, or SOUND_NONE */
    /* 0x24 */ s16 nextSound;  /* to play, SOUND_NONE or SOUND_STOP */
    /* 0x26 */ s16 soundGroup; /* loaded for the sound, or SOUND_NONE */
    /* 0x28 */ s16 fadeTimer;
    /* 0x2A */ s16 fadeFrames;
    /* 0x2C */ s32 baseLevel;  /* the heap's level with group 0 loaded */
    /* 0x30 */ s32 soundLevel; /* with the sound's group loaded */
    /* 0x34 */ s32 bgmLevel;   /* with the BGM loaded */
    /* 0x38 */ s32 unk38;      /* passed to func_020bcc80, then flipped */
    /* 0x3C */ s32 bgmHandle;
    /* 0x40 */ s32 soundHandle;      /* for sounds with no group of their own */
    /* 0x44 */ s32 groupSoundHandle; /* for sounds with a group */
};

enum SoundTaskState {
    SOUND_TASK_RUN,        /* starts and stops what the requests say */
    SOUND_TASK_FADE_OUT,   /* waits for the BGM to fade out */
    SOUND_TASK_SET_UNK38,  /* passes unk38 to func_020bcc80 */
};

#define SOUND_NONE (-1)
#define SOUND_STOP (-2)
#define SOUND_FADE_FRAMES 16

static inline struct SoundTask *getSoundTask(void) {
    return findTask(SOUND_TASK_ID);
}

struct BgData {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u8 data[];
};

void unloadSoundGroup(void);
void loadSoundGroup(s16 group);
/* Takes nothing, but cmdPlaySound passes it an argument. */
void stopSound();
void playSound(s16 sound);
s16 getBgm(void);
void func_02085130(void);
void func_02085160(void);
void stopBgm(void);
void playBgm(s16 bgm);
s32 func_02085520();
s32 func_0208558c();
s32 func_02085710();
s32 func_0208577c();
void initSubVramTopStacks(s16 base0, s16 base1, s16 base2, s16 base3, s16 base4);
void initMainVramTopStacks(s16 base0, s16 base1, s16 base2, s16 base3, s16 base4);
void initSubVramStacks(s16 base0, s16 base1, s16 base2, s16 base3, s16 base4);
void initMainVramStacks(s16 base0, s16 base1, s16 base2, s16 base3, s16 base4);
s32 setSubBgOffset();
s32 setMainBgOffset();
void applyBgOffsets(void);
struct BgData *loadSubBg(void *params);
struct BgData *loadMainBg(void *params);
s16 func_02085f34();
struct BgData *loadSubBgAndFlush(void *params);
struct BgData *loadMainBgAndFlush(void *params);
s32 func_0208644c();
void func_020865b4(s32 layer, s32 arg1, s32 arg2, s32 arg3, s16 arg4, s32 arg5);
void func_02086608(s32 layer, s32 arg1, s32 arg2, s32 arg3, s16 arg4, s32 arg5);
s32 func_02086758();
s32 func_020867fc();
struct BgData *func_020868a0(u8 *params, s32 screen, s32 size);
s32 getSubBgScreenSize();
s32 getMainBgScreenSize();
s32 getSubBgScreen();
s32 getMainBgScreen();
struct BgData *copySubBgScreen(u8 *params);
struct BgData *copyMainBgScreen(u8 *params);
s32 runSoundTask();
void startSoundTask(void);
s16 allocMainVram();
s32 func_02085c84();
s16 allocSubVram();
void getSubBgOffset();
void getMainBgOffset();
s32 getBgMapOffset(s32 size, s32 x, s32 y, s32 width);
s32 getBgScreenOffset(s32 size, s32 x, s32 y);
s16 func_020855f8();
s16 func_02085670();

#endif /* ENGINE_BG_BG_LAYERS_H */
