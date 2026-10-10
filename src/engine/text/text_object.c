#include "engine/text/text_object.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"

/* Frees what a window picture owns and empties it. */
void freeWindowImage(void *picture) {
    struct WindowImage *image = picture;
    u32 flags;
    void *map;
    void *pixels;

    flags = image->flags;
    if (flags & WINDOW_IMAGE_TILES) {
        if (flags & 1) {
            func_02085710((u8) image->bg, image->tiles);
        } else {
            func_0208577c((u8) image->bg, image->tiles);
        }
    }
    if (image->flags & WINDOW_IMAGE_MAP) {
        map = image->map;
        heapFree(map);
    }
    if (image->flags & WINDOW_IMAGE_PIXELS) {
        pixels = image->pixels;
        heapFree(pixels);
    }
    image->flags = 0;
}

/* Sets a window picture's unk10. */
void func_020a6120(void *picture, s16 value) {
    struct WindowImage *image = picture;

    image->unk10 = value;
}

/* Sets a window picture's unk8. */
void func_020a6118(void *picture, s16 value) {
    struct WindowImage *image = picture;

    image->unk8 = value;
}

/* Sets a window picture's unk6. */
void func_020a6110(void *picture, s16 value) {
    struct WindowImage *image = picture;

    image->unk6 = value;
}

/* Sets the graphics file of a window picture, and takes unk6, unkE and
 * unk10 from the slot that holds it. */
void func_020a60bc(void *picture, s16 file) {
    struct WindowImage *image = picture;
    struct GfxSlot *slot;

    if (image->flags & 1) {
        slot = func_020a9764(file);
    } else {
        slot = func_020a97c8(file);
    }
    image->file  = file;
    image->unk6  = slot->palette;
    image->unkE  = slot->unkC;
    image->unk10 = slot->unkE;
}

/* Returns a frame of a graphics file held in a slot with flag 4 clear. */
u16 *func_020a5ecc(s32 file, s32 index) {
    struct GfxSlot *slot = func_020a97c8(file);
    u16 *data            = slot->unk18;

    return &data[index * ((u16) (data[2] >> 3) * (u16) (data[3] >> 3) * TILE_HALFWORDS + 1) + FILE_HEADER];
}

/* The same, in a slot with flag 4 set. */
u16 *func_020a5e88(s32 file, s32 index) {
    struct GfxSlot *slot = func_020a9764(file);
    u16 *data            = slot->unk18;

    return &data[index * ((u16) (data[2] >> 3) * (u16) (data[3] >> 3) * TILE_HALFWORDS + 1) + FILE_HEADER];
}

/* Puts a window picture's map at (x, y) of its background and loads its
 * tiles. */
void func_020a5d1c(s32 x, s32 y, void *picture) {
    struct WindowImage *image = picture;

    if (image->flags & 1) {
        func_020865b4((u8) image->bg, x, y, image->width, (s32) image->height, (s32) image->map);
        putSubBgChars((u8) image->bg, image->tiles, (s16) (image->width * image->height), (s32) image->pixels);
        return;
    }
    func_02086608((u8) image->bg, x, y, image->width, (s32) image->height, (s32) image->map);
    putMainBgChars((u8) image->bg, image->tiles, (s16) (image->width * image->height), (s32) image->pixels);
}

/* Puts a window picture into a window at (x, y), on the window's unk3
 * background, and redraws the window. */
void func_020a5c6c(void *picture, s32 x, s32 y, u32 index) {
    struct WindowImage *image = picture;
    struct Window *window;

    window = getWindow(index);
    func_020a8ce0(index, x, y, image->width, image->height, image->map);
    if (window->flags & 1) {
        putSubBgChars(window->unk3, image->tiles, (s16) (image->width * image->height), (s32) image->pixels);
    } else {
        putMainBgChars(window->unk3, image->tiles, (s16) (image->width * image->height), (s32) image->pixels);
    }
    redrawWindow(index);
}

/* The same, on the window's unk2 background (func_020a8c40). */
void func_020a5bbc(void *picture, s32 x, s32 y, u32 index) {
    struct WindowImage *image = picture;
    struct Window *window;

    window = getWindow(index);
    func_020a8c40(index, x, y, image->width, image->height, image->map);
    if (window->flags & 1) {
        putSubBgChars(window->unk2, image->tiles, (s16) (image->width * image->height), (s32) image->pixels);
    } else {
        putMainBgChars(window->unk2, image->tiles, (s16) (image->width * image->height), (s32) image->pixels);
    }
    redrawWindow(index);
}

/* Sets flag 0x20 of the text flags (data_021e33cc). */
void func_020a58a8(void) {
    data_021e33cc |= 0x20;
}

/* Clears flag 0x20 of the text flags. */
void func_020a5890(void) {
    data_021e33cc &= ~0x20;
}

/* Sets flag 0x40 of the text flags. */
void func_020a5878(void) {
    data_021e33cc |= 0x40;
}

/* Clears flag 0x40 of the text flags. */
void func_020a5860(void) {
    data_021e33cc &= ~0x40;
}

/* Sets flag 0x80 of the text flags. */
void func_020a5848(void) {
    data_021e33cc |= 0x80;
}
