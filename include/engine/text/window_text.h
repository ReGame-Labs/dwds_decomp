#ifndef ENGINE_TEXT_WINDOW_TEXT_H
#define ENGINE_TEXT_WINDOW_TEXT_H

/* Text boxes: a window with a text drawn as sprites and three sprites, a task
 * of their own (func_020a6f10, func_020a725c, func_020a78a4). */

#include "engine/data.h"
#include "types.h"

struct TextBox {
    struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s8 gfxSlot;
    /* 0x25 */ u8 window;
    /* 0x26 */ u16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ u16 sprites[3]; /* 0xFFFF for none */
    /* 0x38 */ s32 spriteText; /* a struct SpriteText's task id, or 0 */
    /* 0x3C */ s32 unk3C;
};

s32 func_020a6990();
void func_020a6ae8(void *tiles, s32 color, s32 count);
s32 func_020a68cc();
s32 func_020a6f10();
s32 func_020a6808();
void func_020a6a40();
void func_020a6b10();
void func_020a6e54(void);

#endif /* ENGINE_TEXT_WINDOW_TEXT_H */
