#ifndef ENGINE_PALETTE_PALETTE_FADE_H
#define ENGINE_PALETTE_PALETTE_FADE_H

#include "engine/data.h"
#include "types.h"

void resumePaletteEffects(s32 index, struct PaletteEffect *effects);
s32 resumeSubPaletteEffects();
s32 resumeMainPaletteEffects();
void pausePaletteEffects(s32 index, struct PaletteEffect *effects);
s32 pauseSubPaletteEffects();
s32 pauseMainPaletteEffects();
void stopPaletteEffects(s32 index, struct PaletteEffect *effects);
s32 stopSubPaletteEffects();
s32 isPaletteEffectRunning(s32 index, struct PaletteEffect *effects);
s32 isSubPaletteEffectRunning(s32 index);
s32 isMainPaletteEffectRunning(s32 index);
void startPaletteFade(s32 start, s32 count, u16 *colors, s32 interval, s32 step, struct PaletteEffect *effects);
void startSubPaletteFade(s32 start, s32 count, u16 *colors, s32 interval, s16 step);
void startMainPaletteFade(s32 start, s32 count, u16 *colors, s32 interval, s16 step);
s32 fadeInSubPalette(s16 start, s16 count, u16 color, s16 interval, s16 step);
s32 fadeInMainPalette(s16 start, s16 count, u16 color, s16 interval, s16 step);
void markPaletteDirty(s32 index, struct PaletteSet *palettes);
void loadPalette(s32 index, s32 count, s32 src, struct PaletteSet *palettes);
void loadSubPalette(s32 index, s32 count, s32 src);
void loadMainPalette(s32 index, s32 count, s32 src);
s32 func_0208448c();
s32 stopMainPaletteEffects();
s32 fadeOutSubPalette(s16 start, s16 count, u16 color, s16 interval, s16 step);
s32 fadeOutMainPalette(s16 start, s16 count, u16 color, s16 interval, s16 step);
void func_020846bc(s16 start, s16 count, s16 delta);
void func_020845e4(s16 arg0, s32 arg1, s32 arg2);

#endif /* ENGINE_PALETTE_PALETTE_FADE_H */
