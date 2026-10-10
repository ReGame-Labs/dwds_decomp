#ifndef ENGINE_SPRITE_SPRITE_RESOURCES_H
#define ENGINE_SPRITE_SPRITE_RESOURCES_H

#include "types.h"

/* The lookup of the sprite resources: palettes, cells and characters. */

s16 findSpritePalette(s16 id);
s16 findFreeSpritePalette(void);
s16 findSpriteCells(s16 id);
s16 findSpriteChars(s16 id);

#endif /* ENGINE_SPRITE_SPRITE_RESOURCES_H */
