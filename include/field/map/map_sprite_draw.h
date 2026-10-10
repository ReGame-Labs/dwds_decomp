#ifndef FIELD_MAP_MAP_SPRITE_DRAW_H
#define FIELD_MAP_MAP_SPRITE_DRAW_H

/* Drawing the map sprites: their sprite VRAM, their order, their animations
 * and the tasks that draw them. */

#include "types.h"

struct MapAnimFrame;

void freeSubMapSpriteVram(s16 block);
s16 allocSubMapSpriteVram(s16 count);
void freeMainMapSpriteVram(s16 block);
s16 allocMainMapSpriteVram(s16 count);
void sortSubMapSprites(void);
void sortMainMapSprites(void);
void tickSubMapSprites(void);
void tickMainMapSprites(void);
s16 findMapAnimFrame(struct MapAnimFrame **frame, u16 animation, s16 *frameTime);

#endif /* FIELD_MAP_MAP_SPRITE_DRAW_H */
