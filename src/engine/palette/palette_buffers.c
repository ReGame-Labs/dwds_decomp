#include "engine/palette/palette_buffers.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"

/* Stops one of a screen's palette effects, or with -1 all but its fades. */
void stopPaletteEffectsButFades(s32 index, struct PaletteEffect *effects) {
    s32 i;

    if (index == -1) {
        for (i = 0; i < PALETTE_EFFECT_COUNT; i++, effects++) {
            if (effects->kind > PALETTE_FADE) {
                effects->kind = PALETTE_EFFECT_NONE;
            }
        }
        return;
    }
    effects[index].kind = PALETTE_EFFECT_NONE;
}

/* Makes count of the main screen's colors from start blink amount percent of
 * the way to color, times times (PALETTE_FOREVER for no end). */
void startMainPaletteBlink(s32 start, s32 count, s32 color, s32 amount, s16 interval, s16 times, s16 step) {
    startPaletteBlink(start, count, color, amount, interval, times, step, MAIN_PALETTES, MAIN_PALETTE_EFFECTS);
}

/* Returns how many of the effects come before the first free one. */
s32 countPaletteEffects(struct PaletteEffect *effects) {
    s32 i;

    for (i = 0; i < PALETTE_EFFECT_COUNT; i++, effects++) {
        if (effects->kind == PALETTE_EFFECT_NONE) {
            break;
        }
    }
    return i;
}

/* Puts count of the main screen's colors from index back to their loaded colors. */
void restoreMainPalette(s32 index, s32 count) {
    loadMainPalette((u16) index, (u16) count, (s32) getMainPaletteBase(index));
}

/* The main screen's color index, as it shows. */
u16 *getMainPaletteColor(s32 index) {
    return &MAIN_PALETTE_COLORS[index];
}

/* The sub screen's color index, as it shows. */
u16 *getSubPaletteColor(s32 index) {
    return &SUB_PALETTE_COLORS[index];
}

/* The main screen's color index, as a fade goes to it. */
u16 *getMainPaletteTarget(s32 index) {
    return &MAIN_PALETTE_TARGET[index];
}

/* The sub screen's color index, as a fade goes to it. */
u16 *getSubPaletteTarget(s32 index) {
    return &SUB_PALETTE_TARGET[index];
}

/* The main screen's color index, as it was loaded. */
u16 *getMainPaletteBase(s32 index) {
    return &MAIN_PALETTE_BASE[index];
}

/* The sub screen's color index, as it was loaded. */
u16 *getSubPaletteBase(s32 index) {
    return &SUB_PALETTE_BASE[index];
}

/* Starts the task that runs the name entry for a script, as script command
 * func_0208909c does. */
void func_02083754(void) {
    struct StateTask *task = createTask(func_0208365c, 0x117);

    task->state = 0;
    task->wait  = 0;
}

/* Whether the name entry was set up with 2 as its second value. */
s32 func_02083738(void) {
    if ((u8) data_021bc6a0 == 2) {
        return 1;
    }
    return 0;
}

/* Keeps a value from the name entry's script task (func_0208365c). */
void func_0208364c(s8 value) {
    data_021bc69c = value;
}

/* The flag func_02083628 sets. */
u8 func_0208363c(void) {
    return data_021bc6a4;
}

/* Sets a flag the scripts set before every name entry. */
void func_02083628(void) {
    data_021bc6a4 = 1;
}

/* The name entry's mode: 0 the player's name, 1 an own Digimon's, 2 a
 * Digimon's from a script variable, 4 none. */
u8 getNameEntryMode(void) {
    return NAME_ENTRY_MODE;
}

/* The longest name the name entry takes. */
u8 getNameEntryMaxLength(void) {
    return NAME_ENTRY_MAX_LENGTH;
}

/* Where the name entry writes the name, or NULL. */
void *getNameEntryName(void) {
    return NAME_ENTRY_NAME;
}

/* Sets up the name entry: its mode, a value the scripts leave 0, the longest
 * name it takes and where it writes the name. */
void setNameEntry(s8 mode, s8 arg1, s8 maxLength, void *name) {
    NAME_ENTRY_MODE       = mode;
    data_021bc6a0         = arg1;
    NAME_ENTRY_MAX_LENGTH = maxLength;
    NAME_ENTRY_NAME       = name;
}

/* The first of the two values func_0208357c keeps. */
u8 func_020835a8(void) {
    return data_021bc6a8;
}

/* The second of the two values func_0208357c keeps. */
u8 func_02083598(void) {
    return data_021bc6ac;
}

/* Keeps two values for the name entry; the scripts pass 8 and 0. */
void func_0208357c(s8 arg0, s8 arg1) {
    data_021bc6a8 = arg0;
    data_021bc6ac = arg1;
}

/* The own Digimon whose name the name entry changes in mode 1. */
s32 getNameEntryDigimon(void) {
    return NAME_ENTRY_DIGIMON;
}

/* Sets the own Digimon whose name the name entry changes in mode 1. */
void setNameEntryDigimon(s32 id) {
    NAME_ENTRY_DIGIMON = id;
}
