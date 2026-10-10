#include "engine/window/window_draw.h"
#include "engine/data.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/window/window.h"

/* The same as func_020a8e3c, at (x, y) from the window's own place. */
void func_020a8d80(u32 index, s32 x, s32 y) {
    struct Window *window;

    window        = getWindow(index);
    window->unk16 = window->x + x;
    window->unk18 = window->y + y;
    window->unk1A = 0;
    window->unk1C = 0;
    window->flags |= 0xC200;
}

/* Redraws an open window (flags 0xC000). */
void redrawWindow(u32 index) {
    struct Window *window;
    u16 flags;

    window = getWindow(index);
    flags  = window->flags;
    if (flags != 0) {
        window->flags = flags | 0xC000;
    }
}

/* Frees one of a window's sprites, on the screen of the window. */
void func_020a8704(u32 index, s32 slot) {
    struct Window *window;
    u8 sprite;

    window = getWindow(index);
    sprite = window->sprites[slot];
    if (sprite == 0xFF) {
        return;
    }
    if (window->flags & 1) {
        freeSubSprite(sprite);
        return;
    }
    freeMainSprite(sprite);
}

/* Places one of a window's sprites at (x, y). */
void func_020a869c(u32 index, s32 slot, s32 x, s32 y) {
    struct Window *window;
    u8 sprite;

    window = getWindow(index);
    sprite = window->sprites[slot];
    if (sprite == 0xFF) {
        return;
    }
    if (window->flags & 1) {
        setSubSpritePos(sprite, x, y);
        return;
    }
    setMainSpritePos(sprite, x, y);
}

/* Sets the animation of one of a window's sprites. */
void func_020a8638(u32 index, s32 slot, s16 anim) {
    struct Window *window;
    u8 sprite;

    window = getWindow(index);
    sprite = window->sprites[slot];
    if (sprite == 0xFF) {
        return;
    }
    if (window->flags & 1) {
        setSubSpriteAnim(sprite, anim, -1);
        return;
    }
    setMainSpriteAnim(sprite, anim, -1);
}

/* Returns data_021e33d0 - 1, or -1 while data_021e33d8 is set. */
s32 func_020a8610(void) {
    if (data_021e33d8 != 0) {
        return -1;
    }
    return data_021e33d0 - 1;
}
