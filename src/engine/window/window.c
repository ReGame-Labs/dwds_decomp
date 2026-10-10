#include "engine/window/window.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/sprite/sprite_create.h"

/* Returns one of the 24 graphics slots that windows draw with. */
struct GfxSlot *getGfxSlot(s32 index) {
    return &GFX_SLOTS[index];
}

/* Empties both stacks of window maps, each down to its 0x1000-byte buffer. */
void func_020a917c(void) {
    s32 i;

    i = 0;
    do {
        data_021e33f8[i] = NULL;
        data_021e3438[i] = NULL;
        i++;
    } while (i < 16);
    data_021e33f8[0] = data_021e4ad8;
    data_021e3438[0] = data_021e3ad8;
}

/* Takes a map of size tiles for a window from the stack that bit 0 of its
 * flags picks: returns the top of the stack and pushes the end of the map. */
u16 *func_020a9134(s32 size, s32 flags) {
    u16 **maps;
    u16 *map;
    s32 i;

    i = 15;
    if (flags & 1) {
        maps = data_021e33f8;
    } else {
        maps = data_021e3438;
    }
    do {
        if (maps[i] != NULL) {
            break;
        }
    } while (--i >= 0);
    map = maps[i];
    if (i < 15) {
        maps[i + 1] = map + size;
    }
    return map;
}

/* Closes the 8 windows. */
void closeAllWindows(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        closeWindow((u8) i);
    }
}

/* Returns one of the 8 windows, or NULL for an index out of range. */
void *getWindow(u32 index) {
    if (index >= 8) {
        return NULL;
    }
    return &WINDOWS[index];
}

/* Sets a window's unk16-unk1C rectangle to (x, y) with no size, and flags
 * 0xC200: 0xC000 redraws it (redrawWindow), 0x200 is what func_020a8dcc
 * tests. */
void func_020a8e3c(u32 index, s16 x, s16 y) {
    struct Window *window = getWindow(index);

    window->unk16 = x;
    window->unk18 = y;
    window->unk1A = 0;
    window->unk1C = 0;
    window->flags |= 0xC200;
}

/* The same as func_020a8e3c, with a size. */
void func_020a8e04(u32 index, s16 x, s16 y, s16 width, s16 height) {
    struct Window *window = getWindow(index);

    window->unk16 = x;
    window->unk18 = y;
    window->unk1A = width;
    window->unk1C = height;
    window->flags |= 0xC200;
}

/* Returns whether a window has flag 0x200 (func_020a8e3c sets it). */
BOOL func_020a8dcc(u32 index) {
    struct Window *window;

    window = getWindow(index);
    if (window == NULL || !(window->flags & 0x200)) {
        return FALSE;
    }
    return TRUE;
}
