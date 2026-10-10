#ifndef ENGINE_PALETTE_PALETTE_BUFFERS_H
#define ENGINE_PALETTE_PALETTE_BUFFERS_H

#include "engine/data.h"
#include "types.h"

/* The two screens' palette buffers. */
#define MAIN_PALETTES ((struct PaletteSet *) MAIN_PALETTE_COLORS)
#define SUB_PALETTES ((struct PaletteSet *) SUB_PALETTE_COLORS)

void setNameEntryDigimon(s32 id);
s32 getNameEntryDigimon(void);
void func_0208357c(s8 arg0, s8 arg1);
u8 func_02083598(void);
u8 func_020835a8(void);
void setNameEntry(s8 mode, s8 arg1, s8 maxLength, void *name);
void *getNameEntryName(void);
u8 getNameEntryMaxLength(void);
u8 getNameEntryMode(void);
void func_02083628(void);
u8 func_0208363c(void);
void func_0208364c(s8 value);
s32 restoreSubPalette();
s32 countPaletteEffects(struct PaletteEffect *effects);
s8 func_020839c8();
void stopPaletteEffectsButFades(s32 index, struct PaletteEffect *effects);
s32 stopSubPaletteEffectsButFades();
s32 stopMainPaletteEffectsButFades();
s32 func_02083e78();
s32 func_02083ea8();
s32 func_0208365c();
void func_02083754(void);
s32 func_02083738(void);
void reversePaletteBlink(struct PaletteSet *palettes, struct PaletteEffect *effect);
void func_02083c0c(struct PaletteSet *palettes, struct PaletteEffect *effect);
void func_02083cd0(struct PaletteSet *palettes, struct PaletteEffect *effect);
u16 *getSubPaletteBase(s32 index);
u16 *getMainPaletteBase(s32 index);
u16 *getSubPaletteTarget(s32 index);
u16 *getMainPaletteTarget(s32 index);
u16 *getSubPaletteColor(s32 index);
u16 *getMainPaletteColor(s32 index);
void restoreMainPalette(s32 index, s32 count);
void startPaletteBlink();
void startMainPaletteBlink(s32 start, s32 count, s32 color, s32 amount, s16 interval, s16 times, s16 step);

#endif /* ENGINE_PALETTE_PALETTE_BUFFERS_H */
