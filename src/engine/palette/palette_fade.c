#include "engine/palette/palette_fade.h"
#include "engine/data.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_upload.h"

/* Loads count colors from the address src into the main screen's palettes at
 * index, which may carry PALETTE_LOAD_KEEP_COLOR0 and PALETTE_LOAD_QUIET. */
void loadMainPalette(s32 index, s32 count, s32 src) {
    loadPalette(index, count, src, MAIN_PALETTES);
}

/* Loads count colors from the address src into the sub screen's palettes at
 * index, which may carry PALETTE_LOAD_KEEP_COLOR0 and PALETTE_LOAD_QUIET. */
void loadSubPalette(s32 index, s32 count, s32 src) {
    loadPalette(index, count, src, SUB_PALETTES);
}

/* Marks the part of the palettes that color index is in as changed. */
void markPaletteDirty(s32 index, struct PaletteSet *palettes) {
    if (((index >= PALETTE_BG_EXT) && (index < PALETTE_OBJ)) ||
        ((index >= PALETTE_OBJ_EXT) && (index < PALETTE_COLOR_COUNT))) {
        palettes->dirty = (u16) (palettes->dirty | PALETTE_DIRTY_EXTENDED);
        return;
    }
    palettes->dirty = (u16) (palettes->dirty | PALETTE_DIRTY_STANDARD);
}

/* Fades count of the main screen's colors from start to colors, step a frame
 * every interval frames, and lets the palettes upload again. */
void startMainPaletteFade(s32 start, s32 count, u16 *colors, s32 interval, s16 step) {
    unlockMainPalettes();
    startPaletteFade(start, count, colors, interval, (s32) step, MAIN_PALETTE_EFFECTS);
}

/* Fades count of the sub screen's colors from start to colors, step a frame
 * every interval frames, and lets the palettes upload again. */
void startSubPaletteFade(s32 start, s32 count, u16 *colors, s32 interval, s16 step) {
    unlockSubPalettes();
    startPaletteFade(start, count, colors, interval, (s32) step, SUB_PALETTE_EFFECTS);
}

/* Whether the main screen's effect index is still going, or with -1 whether
 * any of its fades is. */
s32 isMainPaletteEffectRunning(s32 index) {
    return isPaletteEffectRunning(index, MAIN_PALETTE_EFFECTS);
}

/* Whether the sub screen's effect index is still going, or with -1 whether
 * any of its fades is. */
s32 isSubPaletteEffectRunning(s32 index) {
    return isPaletteEffectRunning(index, SUB_PALETTE_EFFECTS);
}

/* Stops one of the effects, or with -1 all of them. */
void stopPaletteEffects(s32 index, struct PaletteEffect *effects) {
    s32 i;

    if (index == -1) {
        i = 0;
        do {
            i++;
            effects->kind = PALETTE_EFFECT_NONE;
            effects++;
        } while (i < PALETTE_EFFECT_COUNT);
        return;
    }
    effects[index].kind = PALETTE_EFFECT_NONE;
}

/* Pauses one of the effects, or with 0xFF all of them. */
void pausePaletteEffects(s32 index, struct PaletteEffect *effects) {
    s32 i;
    u8 kind;

    if (index == 0xFF) {
        for (i = 0; i < PALETTE_EFFECT_COUNT; i++, effects++) {
            kind = effects->kind;
            if (kind != PALETTE_EFFECT_NONE) {
                effects->kind = kind | PALETTE_EFFECT_PAUSED;
            }
        }
        return;
    }
    kind = effects[index].kind;
    if (kind != PALETTE_EFFECT_NONE) {
        effects[index].kind = kind | PALETTE_EFFECT_PAUSED;
    }
}

/* Resumes one of the effects, or with -1 all of them. */
void resumePaletteEffects(s32 index, struct PaletteEffect *effects) {
    s32 i;
    u8 kind;

    if (index == -1) {
        for (i = 0; i < PALETTE_EFFECT_COUNT; i++, effects++) {
            kind = effects->kind;
            if (kind != PALETTE_EFFECT_NONE) {
                effects->kind = kind & ~PALETTE_EFFECT_PAUSED;
            }
        }
        return;
    }
    kind = effects[index].kind;
    if (kind != PALETTE_EFFECT_NONE) {
        effects[index].kind = kind & ~PALETTE_EFFECT_PAUSED;
    }
}
