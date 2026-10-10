#include "engine/gfx/gfx_files.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "engine/ui/dial.h"
#include "nitro/g2d.h"

/* Rearranges a background's screen data in place: func_02044220 copies its
 * tiles, in blocks of 32 by 32, into a block of the heap, which is copied back
 * over them. width and height are passed on the stack and func_02044220 may
 * change the width, which goes back in the screen data; the other arguments
 * are not read. */
void rearrangeScreenData(s32 bg, struct ScreenData *screen, s32 unk2, s32 unk3, s32 unk4, s32 unk5, s32 unk6, u16 width,
                         s32 height) {
    void *buffer;

    buffer = heapAlloc(screen->size, -8);
    func_02044220(screen->data, buffer, &width, &height);
    screen->width = width;
    func_020e22f4(buffer, screen->data, screen->size);
    heapFree(buffer);
}

/* Expands 4-bit pixels to a byte each, adding base to every one but 0. */
void expandPixels(u8 *src, u8 *dst, s32 base, u32 count) {
    u32 i;
    u8 lo;
    u8 hi;

    for (i = 0; i < count; i++) {
        lo     = *src & 0xF;
        hi     = *src >> 4;
        dst[0] = lo;
        if (lo != 0) {
            dst[0] += base;
        }
        dst[1] = hi;
        if (hi != 0) {
            dst[1] += base;
        }
        src++;
        dst += 2;
    }
}

/* Starts the task func_02043ae4 and runs it once. */
void func_02043c40(void) {
    struct Task *task = createTask(func_02043ae4, 0x101);

    task->onEnd = NULL;
    func_02043ae4();
}

/* The size in bytes of a palette file's colors: for a compressed one, its
 * count of palettes of 16 colors, or of 256 (format 4, GX_TEXFMT_PLTT256). The
 * file stays an s32 and the palette a void * for the callers that pass them
 * so (menus/digimon/item_menu_icons.c passes a u8 *). */
u32 getPaletteSize(s32 file, void *data) {
    struct NNSG2dPaletteData *palette = data;
    u16 *compressInfo; /* NNSG2dPaletteCompressInfo, its count of palettes first */
    s32 colors;

    compressInfo = NULL;
    if (func_020b9d30(file, &compressInfo) != 0) {
        colors = 16;
        if (palette->fmt == 4) {
            colors = 256;
        }
        return *compressInfo * colors * 2;
    }
    return palette->szByte;
}

/* Closes every dial's slot. */
void initDials(void) {
    s32 i;

    for (i = 0; i < DIAL_COUNT; i++) {
        DIAL_TASK_IDS[i] = -1;
    }
}
