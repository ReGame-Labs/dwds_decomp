#ifndef ENGINE_TEXT_TEXT_OBJECT_H
#define ENGINE_TEXT_TEXT_OBJECT_H

/* Window pictures (struct WindowImage): canvases texts are printed into,
 * put into windows; frames of graphics files; and the text flags. */

#include "types.h"

/* WindowImage flags: what it owns. */
#define WINDOW_IMAGE_TILES 0x20000000
#define WINDOW_IMAGE_MAP 0x40000000
#define WINDOW_IMAGE_PIXELS 0x80000000

#define TILE_HALFWORDS 0x10 /* a 4bpp 8x8 tile */
#define FILE_HEADER 4    /* u16s before a graphics file's frames */

void func_020a5848(void);
void func_020a5860(void);
void func_020a5878(void);
void func_020a5890(void);
void func_020a58a8(void);
void func_020a5d1c(s32 x, s32 y, void *picture);
void func_020a60bc(void *picture, s16 file);
void func_020a6110(void *picture, s16 value);
void func_020a6118(void *picture, s16 value);
void func_020a6120(void *picture, s16 value);
void freeWindowImage(void *picture);
void func_020a58c0(void *picture, s16 x, s16 y);
u16 *func_020a5e88(s32 file, s32 index);
u16 *func_020a5ecc(s32 file, s32 index);
void func_020a5bbc(void *picture, s32 x, s32 y, u32 index);
void func_020a5c6c(void *picture, s32 x, s32 y, u32 index);

#endif /* ENGINE_TEXT_TEXT_OBJECT_H */
