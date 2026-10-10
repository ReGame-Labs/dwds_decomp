#ifndef MENUS_WIDGETS_COMPARE_COLORS_H
#define MENUS_WIDGETS_COMPARE_COLORS_H

#include "types.h"

/* The colors of a comparison's rows. */

#define RGB15(r, g, b) ((r) | ((g) << 5) | ((b) << 10))

#define COMPARE_YELLOW RGB15(31, 24, 0)
#define COMPARE_RED RGB15(31, 10, 4)
#define COMPARE_CYAN RGB15(6, 26, 31)
#define COMPARE_BLUE RGB15(0, 8, 31)

void colorCompareRows(s32 cool, s32 row0, s32 row1, s32 row2, s32 row3, s32 row4, s32 palette, u8 unk7);
s32 func_0204d8fc();

#endif /* MENUS_WIDGETS_COMPARE_COLORS_H */
