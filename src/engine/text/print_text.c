#include "engine/text/print_text.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/text/expand_text.h"
#include "engine/text/text_labels.h"
#include "engine/text/window_text.h"

#define MAIN_SCREEN_BGS 4 /* the backgrounds below 4 are the main screen's */
#define PALETTE_COLORS 0x10
#define SUB_PALETTES 0x900
#define NUMBER_IN_USE 1 /* NumberSprite flags */
#define NUMBER_UNK2 2
#define NO_LIMIT 9999

/* Clears flag 0x80 of the text flags (data_021e33cc). */
void func_020a5830(void) {
    data_021e33cc &= ~0x80;
}

/* Sets flag 0x400 of the text flags. */
void func_020a5818(void) {
    data_021e33cc |= 0x400;
}

/* Clears flag 0x400 of the text flags. */
void func_020a5800(void) {
    data_021e33cc &= ~0x400;
}

/* Sets the text flags. */
void func_020a57f0(s16 flags) {
    data_021e33cc = flags;
}

/* Sets data_021e33c8. */
void func_020a57e0(s16 value) {
    data_021e33c8 = value;
}

/* Prints a text, as func_0209e344 gives it, into a text canvas
 * (func_020a5338). */
u16 func_020a5304(void *canvas, void *text) {
    return func_020a5338(canvas, func_0209e344(text), 0, NO_LIMIT);
}

/* The same, with the text flags cleared. */
u16 func_020a52c0(void *canvas, void *text) {
    data_021e33cc = 0;
    return func_020a5338(canvas, func_0209e344(text), 0, NO_LIMIT);
}

/* The same, with func_0209e238 on the text first. */
u16 func_020a5268(void *canvas, void *text, s32 value) {
    void *handle;

    data_021e33cc = 0;
    handle        = func_0209e344(text);
    func_0209e238(handle, canvas, value);
    return func_020a5338(canvas, handle, 0, NO_LIMIT);
}

/* Prints a text as it is into a text canvas, after func_020a6a40. */
u16 func_020a522c(void *canvas, s32 text) {
    func_020a6a40();
    return func_020a5338(canvas, text, 0, NO_LIMIT);
}

/* Sets up a number drawn with sprites: its tiles, unless it has some, and
 * its palette. */
void func_020a5134(void *sprite) {
    struct NumberSprite *number = sprite;
    u16 vram;
    s32 size;

    if (number->unk01 < MAIN_SCREEN_BGS) {
        vram = number->palette * PALETTE_COLORS;
    } else {
        vram = number->palette * PALETTE_COLORS + SUB_PALETTES;
    }
    number->flags = 0;
    if (number->unk02 == 0xFFFF) {
        if (number->unk01 < MAIN_SCREEN_BGS) {
            size          = number->digits;
            number->unk02 = allocMainVram(number->unk01, (s16) size);
        } else {
            size          = (number->digits + 1) / 2;
            number->unk02 = func_02085670(number->unk01, (s16) size);
        }
        number->flags |= NUMBER_IN_USE;
    }
    switch (number->unk00) {
        case 0:
        case 1:
            loadMainPalette(vram, PALETTE_COLORS, (s32) data_02127144);
            break;
        case 2:
        case 3:
        case 4:
            loadMainPalette(vram, PALETTE_COLORS, (s32) data_02127164);
            break;
    }
}

/* The same as func_020a5134, with the other tiles (NUMBER_UNK2). */
void func_020a503c(void *sprite) {
    struct NumberSprite *number = sprite;
    u16 vram;
    s32 size;

    if (number->unk01 < MAIN_SCREEN_BGS) {
        vram = number->palette * PALETTE_COLORS;
    } else {
        vram = number->palette * PALETTE_COLORS + SUB_PALETTES;
    }
    number->flags = NUMBER_UNK2;
    if (number->unk02 == 0xFFFF) {
        if (number->unk01 < MAIN_SCREEN_BGS) {
            size          = number->digits;
            number->unk02 = allocSubVram(number->unk01, (s16) size);
        } else {
            size          = (number->digits + 1) / 2;
            number->unk02 = func_020855f8(number->unk01, (s16) size);
        }
        number->flags |= NUMBER_IN_USE;
    }
    switch (number->unk00) {
        case 0:
        case 1:
            loadSubPalette(vram, PALETTE_COLORS, (s32) data_02127144);
            break;
        case 2:
        case 3:
        case 4:
            loadSubPalette(vram, PALETTE_COLORS, (s32) data_02127164);
            break;
    }
}
