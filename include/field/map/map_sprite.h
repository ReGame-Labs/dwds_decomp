#ifndef FIELD_MAP_MAP_SPRITE_H
#define FIELD_MAP_MAP_SPRITE_H

/* The map sprites of each screen: getting them, ending them and loading their
 * characters' files. */

#include "types.h"

struct MapSprite;

void endAllSubMapSprites(void);
void endAllMainMapSprites(void);
void requestEndSubMapSprite(u32 index);
void requestEndMainMapSprite(u32 index);
struct MapSprite *getSubMapSprite(u32 index);
struct MapSprite *getMainMapSprite(u32 index);
void func_ov000_021fa444(s32 character);
void loadMapCharacterAnim(s32 character);
s16 func_ov000_021fa780(s32 character, u16 palette);
void func_ov000_021fa628(s32 character, u16 palette);
void endSubMapSprite(u32 index);
void endMainMapSprite(u32 index);

#endif /* FIELD_MAP_MAP_SPRITE_H */
