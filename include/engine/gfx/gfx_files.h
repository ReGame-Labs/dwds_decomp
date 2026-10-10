#ifndef ENGINE_GFX_GFX_FILES_H
#define ENGINE_GFX_GFX_FILES_H

#include "types.h"

/* The graphics file helpers (palette sizes, pixel expansion, paths, screen
 * data) and the dials' setup. */

struct ScreenData;

u32 getPaletteSize(s32 file, void *palette); /* a struct NNSG2dPaletteData */
s32 func_02043ae4();
void func_02043c40(void);
void initDials(void);
s32 func_02043cdc();
s32 func_02043da0();
void expandPixels(u8 *src, u8 *dst, s32 base, u32 count);
void joinPath();
void func_02043fc4();
s32 func_020440ec();
void *func_0204414c(const char *path);
void func_02044220();
void rearrangeScreenData(s32 bg, struct ScreenData *screen, s32 unk2, s32 unk3, s32 unk4, s32 unk5, s32 unk6, u16 width,
                         s32 height);

#endif /* ENGINE_GFX_GFX_FILES_H */
