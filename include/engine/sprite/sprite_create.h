#ifndef ENGINE_SPRITE_SPRITE_CREATE_H
#define ENGINE_SPRITE_SPRITE_CREATE_H

#include "types.h"

/* The sprites' creation and freeing, and their kinds' resources and
 * characters in VRAM. */

struct SpriteChars;
struct SpriteCells;
struct SpritePalette;

void freeSubSprite(); /* (u32 index): freeMainLinkIcon calls it without */
void freeMainSprite(); /* (u32 index): freeSubLinkIcon calls it without */
void freeSubSprites(void);
void freeMainSprites(void);
s32 createSubSprite();
u32 createMainSprite();
struct SpritePalette *getSpritePalette(s32 index);
struct SpriteCells *getSpriteCells(s16 index);
struct SpriteChars *getSpriteChars(s16 index);
s16 getSpriteKindCells(s32 kind);
s16 getSpriteKindPalette(s32 kind);
s16 getSpriteKindChars(s32 kind);
void uploadSubSpriteChars(void);
void uploadMainSpriteChars(void);
void reslotSubSpriteChars(u32 slot);
void reslotMainSpriteChars(u32 slot);

#endif /* ENGINE_SPRITE_SPRITE_CREATE_H */
