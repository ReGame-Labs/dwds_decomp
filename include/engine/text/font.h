#ifndef ENGINE_TEXT_FONT_H
#define ENGINE_TEXT_FONT_H

#include "types.h"

void func_020a9610(s32 index);
void releaseGfxSlot(s32 index);
void *func_020a9764();
void *func_020a97c8();
void func_020a982c(s32 index);
void func_020a9838(s32 index);
s32 func_020a9844();
s32 func_020a98a8();
s32 func_020a9ae0();
s32 func_020a9c40();
s8 func_020aa1a4();
s8 func_020aa220();
s32 func_020aa29c(void *file, s32 slot, s32 tiles, s32 palette);
s32 func_020aa2c0(void *file, s32 slot, s32 tiles, s32 palette);
s32 func_020a99dc(void);
/* Load a graphics file into a slot: its tiles at tiles (-1 for anywhere), its
 * palette at palette, on background bg. */
s32 func_020a9f28(void *file, s32 slot, s32 tiles, s32 palette, u8 bg);
s32 func_020aa068(void *file, s32 slot, s32 tiles, s32 palette, u8 bg);

#endif /* ENGINE_TEXT_FONT_H */
