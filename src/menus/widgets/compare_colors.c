#include "menus/widgets/compare_colors.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"

/* Colors the rows of a comparison (of items, equipment or skills): for each
 * row set, colors 6 and 7, 8 and 9, ... 0xE and 0xF of palette `palette` in
 * red and yellow (cool 0) or in blue and cyan (cool set). unk7 picks the
 * palette buffer (getMainPaletteColor or getSubPaletteColor) and what flushes it. */
void colorCompareRows(s32 cool, s32 row0, s32 row1, s32 row2, s32 row3, s32 row4, s32 palette, u8 unk7) {
    if (unk7 == 0) {
        if (cool == 0) {
            if (row0 != 0) {
                func_0208448c(COMPARE_YELLOW, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x906)));
                func_0208448c(COMPARE_RED, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x907)));
            }
            if (row1 != 0) {
                func_0208448c(COMPARE_YELLOW, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x908)));
                func_0208448c(COMPARE_RED, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x909)));
            }
            if (row2 != 0) {
                func_0208448c(COMPARE_YELLOW, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90A)));
                func_0208448c(COMPARE_RED, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90B)));
            }
            if (row3 != 0) {
                func_0208448c(COMPARE_YELLOW, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90C)));
                func_0208448c(COMPARE_RED, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90D)));
            }
            if (row4 != 0) {
                func_0208448c(COMPARE_YELLOW, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90E)));
                func_0208448c(COMPARE_RED, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90F)));
            }
        } else {
            if (row0 != 0) {
                func_0208448c(COMPARE_CYAN, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x906)));
                func_0208448c(COMPARE_BLUE, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x907)));
            }
            if (row1 != 0) {
                func_0208448c(COMPARE_CYAN, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x908)));
                func_0208448c(COMPARE_BLUE, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x909)));
            }
            if (row2 != 0) {
                func_0208448c(COMPARE_CYAN, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90A)));
                func_0208448c(COMPARE_BLUE, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90B)));
            }
            if (row3 != 0) {
                func_0208448c(COMPARE_CYAN, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90C)));
                func_0208448c(COMPARE_BLUE, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90D)));
            }
            if (row4 != 0) {
                func_0208448c(COMPARE_CYAN, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90E)));
                func_0208448c(COMPARE_BLUE, 1, 0x10, getMainPaletteColor((s16) ((palette * 0x10) + 0x90F)));
            }
        }
        markMainPalettesDirty();
        return;
    }
    if (cool == 0) {
        if (row0 != 0) {
            func_0208448c(COMPARE_YELLOW, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x906)));
            func_0208448c(COMPARE_RED, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x907)));
        }
        if (row1 != 0) {
            func_0208448c(COMPARE_YELLOW, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x908)));
            func_0208448c(COMPARE_RED, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x909)));
        }
        if (row2 != 0) {
            func_0208448c(COMPARE_YELLOW, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90A)));
            func_0208448c(COMPARE_RED, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90B)));
        }
        if (row3 != 0) {
            func_0208448c(COMPARE_YELLOW, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90C)));
            func_0208448c(COMPARE_RED, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90D)));
        }
        if (row4 != 0) {
            func_0208448c(COMPARE_YELLOW, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90E)));
            func_0208448c(COMPARE_RED, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90F)));
        }
    } else {
        if (row0 != 0) {
            func_0208448c(COMPARE_CYAN, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x906)));
            func_0208448c(COMPARE_BLUE, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x907)));
        }
        if (row1 != 0) {
            func_0208448c(COMPARE_CYAN, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x908)));
            func_0208448c(COMPARE_BLUE, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x909)));
        }
        if (row2 != 0) {
            func_0208448c(COMPARE_CYAN, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90A)));
            func_0208448c(COMPARE_BLUE, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90B)));
        }
        if (row3 != 0) {
            func_0208448c(COMPARE_CYAN, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90C)));
            func_0208448c(COMPARE_BLUE, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90D)));
        }
        if (row4 != 0) {
            func_0208448c(COMPARE_CYAN, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90E)));
            func_0208448c(COMPARE_BLUE, 1, 0x10, getSubPaletteColor((s16) ((palette * 0x10) + 0x90F)));
        }
    }
    markSubPalettesDirty();
}
