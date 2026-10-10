#include "battle/characters/bg_effect_files.h"
#include "battle/characters/chr_system.h"
#include "battle/characters/data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/system/system.h"

/* Ends the sub screen's effects task. */
void stopSubBgEffectTask(void) {
    endTask(SUB_BG_EFFECT_TASK);
}

/* Loads a main screen effect: its "d" file, its characters into the sprite
 * VRAM it reserves for vramSlot, its cells and its colours into palette. The
 * move script's command 0. */
void loadMainBgEffect(s32 effect, s32 vramSlot, s32 palette) {
    func_ov001_021fdeec(effect);
    loadMainBgEffectChars(effect, 0, vramSlot, data_ov001_02212df0[effect]);
    func_ov001_021fe034(effect, data_ov001_02212df0[effect]);
    loadMainBgEffectPalette(effect, palette);
}

/* Loads a sub screen effect: its "d" file, its characters into the sprite VRAM
 * it reserves for vramSlot, its cells and its colours into palette. The move
 * script's command 1. */
void loadSubBgEffect(s32 effect, s32 vramSlot, s32 palette) {
    func_ov001_021fdeec(effect);
    loadSubBgEffectChars(effect, 0, vramSlot, data_ov001_02212df0[effect]);
    func_ov001_021fdf6c(effect, data_ov001_02212df0[effect]);
    loadSubBgEffectPalette(effect, palette);
}

/* Unloads an effect: forgets the users of its files and frees them. The move
 * script's command 2; command 3 runs the same code, func_ov001_021fe408. */
void func_ov001_021fe44c(s32 effect) {
    BG_EFFECT_CHAR_USERS[effect]    = 0;
    data_ov001_02212574[effect]     = 0;
    BG_EFFECT_PALETTE_USERS[effect] = 0;
    data_ov001_022123c0[effect]     = 0;
    freeBgEffectFiles(effect);
}

/* Unloads an effect: forgets the users of its files and frees them. The move
 * script's command 3. */
void func_ov001_021fe408(s32 effect) {
    BG_EFFECT_CHAR_USERS[effect]    = 0;
    data_ov001_02212574[effect]     = 0;
    BG_EFFECT_PALETTE_USERS[effect] = 0;
    data_ov001_022123c0[effect]     = 0;
    freeBgEffectFiles(effect);
}

/* The main screen sprite VRAM reserved for an effect's characters in vramSlot. */
s16 getMainBgEffectVram(s32 effect, s32 vramSlot) {
    return MAIN_BG_EFFECT_VRAM[effect][vramSlot];
}

/* The sub screen sprite VRAM reserved for an effect's characters in vramSlot. */
s16 getSubBgEffectVram(s32 effect, s32 vramSlot) {
    return SUB_BG_EFFECT_VRAM[effect][vramSlot];
}

/* Loads an effect's "<n>d" file from /dat/bgeff/ unless it is in, and counts
 * one more user. */
void func_ov001_021fdeec(s32 effect) {
    char path[64];

    if (data_ov001_02212df0[effect] == NULL && data_ov001_022123c0[effect] == 0) {
        joinPath(path, data_ov001_02201390, data_ov001_02200570[effect][0]);
        func_02043fc4(&data_ov001_02212df0[effect], path);
    }
    data_ov001_022123c0[effect]++;
}
