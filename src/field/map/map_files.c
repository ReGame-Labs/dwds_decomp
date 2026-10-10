#include "field/map/map_files.h"
#include "engine/data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "engine/ui/gauge.h"
#include "field/map/data.h"

/* Loads the main screen map's /dat/map/<n>.a file, if the map has one, and
 * clears the screen's characters and rectangles. */
void func_ov000_02202048(s32 map) {
    char path[64];

    data_ov000_0220d964 = 0;
    if (data_ov000_0220a860[map] != NULL) {
        joinPath(path, data_ov000_0220abb4, data_ov000_0220a860[map]);
        func_02043fc4(&data_ov000_0220d964, path);
    }
    func_02030f18(data_ov000_0220d968, -1, sizeof(data_ov000_0220d968));
    func_02030f18(MAIN_MAP_RECTS, -1, sizeof(MAIN_MAP_RECTS));
    data_ov000_0220d950 = 0;
}

/* The same for the sub screen's map. */
void func_ov000_02201fc0(s32 map) {
    char path[64];

    data_ov000_0220d960 = 0;
    if (data_ov000_0220a860[map] != NULL) {
        joinPath(path, data_ov000_0220aba8, data_ov000_0220a860[map]);
        func_02043fc4(&data_ov000_0220d960, path);
    }
    func_02030f18(SUB_MAP_CHARACTER_SLOTS, 0xFF, sizeof(SUB_MAP_CHARACTER_SLOTS));
    func_02030f18(SUB_MAP_RECTS, 0xFF, sizeof(SUB_MAP_RECTS));
    data_ov000_0220d954 = 0;
}

/* Sets one of the sub screen map's rectangles. */
void setSubMapRect(s32 index, s16 left, s16 top, s16 right, s16 bottom, u16 value) {
    SUB_MAP_RECTS[index].left   = left;
    SUB_MAP_RECTS[index].top    = top;
    SUB_MAP_RECTS[index].right  = right;
    SUB_MAP_RECTS[index].bottom = bottom;
    SUB_MAP_RECTS[index].unk8   = value;
}

/* Reads one of the main screen map's rectangles, into the pointers given. */
void getMainMapRect(s32 index, s16 *left, s16 *top, s16 *right, s16 *bottom, u16 *value) {
    if (left != NULL) {
        *left = MAIN_MAP_RECTS[index].left;
    }
    if (top != NULL) {
        *top = MAIN_MAP_RECTS[index].top;
    }
    if (right != NULL) {
        *right = MAIN_MAP_RECTS[index].right;
    }
    if (bottom != NULL) {
        *bottom = MAIN_MAP_RECTS[index].bottom;
    }
    if (value != NULL) {
        *value = MAIN_MAP_RECTS[index].unk8;
    }
}

/* The same for the sub screen map's. */
void getSubMapRect(s32 index, s16 *left, s16 *top, s16 *right, s16 *bottom, u16 *value) {
    if (left != NULL) {
        *left = SUB_MAP_RECTS[index].left;
    }
    if (top != NULL) {
        *top = SUB_MAP_RECTS[index].top;
    }
    if (right != NULL) {
        *right = SUB_MAP_RECTS[index].right;
    }
    if (bottom != NULL) {
        *bottom = SUB_MAP_RECTS[index].bottom;
    }
    if (value != NULL) {
        *value = SUB_MAP_RECTS[index].unk8;
    }
}

/* Sets the main screen map's flag data_ov000_0220d950 (a script command). */
void func_ov000_022016e0(void) {
    data_ov000_0220d950 = 1;
}

/* Sets the sub screen map's flag data_ov000_0220d954 and clears event flag
 * 0x5F (a script command). */
void func_ov000_022016c0(void) {
    data_ov000_0220d954 = 1;
    clearGameFlag(0x5F);
}

/* Clears the main screen map's flag data_ov000_0220d950. */
void func_ov000_022016ac(void) {
    data_ov000_0220d950 = 0;
}

/* Clears the sub screen map's flag data_ov000_0220d954 and sets event flag
 * 0x5F. */
void func_ov000_0220168c(void) {
    data_ov000_0220d954 = 0;
    setGameFlag(0x5F);
}

/* Keeps the sub screen map's rectangles in the save data, at 0x25B0. */
void saveSubMapRects(void) {
    func_02030f78((void *) ((s32) data_021e0cc8 + 0x25B0), SUB_MAP_RECTS, sizeof(SUB_MAP_RECTS));
}

/* Restores the sub screen map's rectangles from the save data. */
void restoreSubMapRects(void) {
    func_02030f78(SUB_MAP_RECTS, (void *) ((s32) data_021e0cc8 + 0x25B0), sizeof(SUB_MAP_RECTS));
}

/* Empties the halfword data_ov000_0220d95c (0xFFFF) and returns it. */
u16 *func_ov000_02201524(void) {
    data_ov000_0220d95c = 0xFFFF;
    return &data_ov000_0220d95c;
}

/* Empties the halfword data_ov000_0220d958 (0xFFFF) and returns it. */
u16 *func_ov000_0220150c(void) {
    data_ov000_0220d958 = 0xFFFF;
    return &data_ov000_0220d958;
}
