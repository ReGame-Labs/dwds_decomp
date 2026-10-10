#ifndef FARM_ITEM_INFO_H
#define FARM_ITEM_INFO_H

/* The window that describes the item under the item list's cursor, and opening
 * that list. */

#include "types.h"

void func_ov005_0227c184(s32 item);
void func_ov005_0227c23c(u8 window, s16 item);
void func_ov005_0227c140(void);
void func_ov005_0227bcec(void);
void func_ov005_0227c0c4(s32 owner, s16 scroll, s16 cursor, s8 palette, s8 unk2D, u16 unk2E);
s16 func_ov005_0227c1bc(s32 owner, s8 *entries);
void func_ov005_0227c364(void);
void func_ov005_0227c4c4(s32 item, s8 palette, s16 unk2A);

#endif /* FARM_ITEM_INFO_H */
