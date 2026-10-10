#ifndef ENGINE_SPRITE_SPRITE_DRAW_H
#define ENGINE_SPRITE_SPRITE_DRAW_H

#include "types.h"

/* The sprites' drawing: the OAM of both screens built from their sprites,
 * and the sprites' BG priorities. */

void setSubSpritesBgPriority(u8 priority);
void setMainSpritesBgPriority(u8 priority);
void setSubSpriteBgPriority(u32 index, s32 priority);
void setMainSpriteBgPriority(u32 index, s32 priority);
s32 readMovieFile(void *dest, const char *path);
void func_0203e848(); /* (u32 index, u8 value): sets the sub sprite's unk1D */
void func_0203e878(); /* (u32 index, u8 value): sets the main sprite's unk1D */
s32 isMainSpriteAnimDone(u32 index);

#endif /* ENGINE_SPRITE_SPRITE_DRAW_H */
