#ifndef ENGINE_WINDOW_WINDOW_H
#define ENGINE_WINDOW_WINDOW_H

#include "types.h"

struct GfxSlot;
struct Window;

void func_020a8e3c(u32 index, s16 x, s16 y);
void func_020a8e04(u32 index, s16 x, s16 y, s16 width, s16 height);
void *getWindow(u32 index);
void func_020a917c(void);
struct GfxSlot *getGfxSlot(s32 index);
BOOL func_020a8dcc(u32 index);
s32 closeWindow();
s32 func_020a90dc();
u16 *func_020a9134(s32 size, s32 flags);
void closeAllWindows(void);
s8 func_020a91c4();
void func_020a95c0();

#endif /* ENGINE_WINDOW_WINDOW_H */
