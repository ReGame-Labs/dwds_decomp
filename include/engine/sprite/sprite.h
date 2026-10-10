#ifndef ENGINE_SPRITE_SPRITE_H
#define ENGINE_SPRITE_SPRITE_H

#include "types.h"

/* The sprites of both screens, SPRITE_COUNT each: MAIN_SPRITES the main
 * screen's, SUB_SPRITES the sub screen's. */

struct Sprite;

struct Sprite *setSubSpritePos(u32 index, u16 x, u16 y);
void releaseSubSpriteKind(u16 kind, u16 set);
void releaseMainSpriteKind(u16 kind, u16 set);
void restartSubSpriteAnim(u32 index, s16 loops);
void restartMainSpriteAnim(u32 index, s16 loops);
u8 getMainSpriteAnim(u32 index);
void setSubSpriteAnim(u32 index, s16 anim, s16 loops);
void setMainSpriteAnim(u32 index, s16 anim, s16 loops);
struct Sprite *setMainSpritePos(u32 index, u16 x, u16 y);
void addSubSpriteFlags(u32 index, u16 flags);
void addMainSpriteFlags(u32 index, u16 flags);
struct Sprite *getSubSprite(u32 index);
struct Sprite *getMainSprite(u32 index);
void clearSubSpriteFlags(u32 index, u16 flags);
void clearMainSpriteFlags(u32 index, u16 flags);
void setSubSpriteFlags(u32 index, u16 flags);
void setMainSpriteFlags(u32 index, u16 flags);
void loadSubSpritePalette(u32 index, s32 slot);
void loadMainSpritePalette(u32 index, s32 slot);

#endif /* ENGINE_SPRITE_SPRITE_H */
