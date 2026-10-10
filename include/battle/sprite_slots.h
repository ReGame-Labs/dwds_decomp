#ifndef BATTLE_SPRITE_SLOTS_H
#define BATTLE_SPRITE_SLOTS_H

#include "types.h"

/* The battle's sprite table (struct SpriteSlot): sprites that forward their
 * changes once a frame to the sprite they own in a screen's sprite pool. */

/* A handle from this one is a sub screen pool sprite's index plus it; one below
 * it is a main screen pool sprite's index. */
#define SUB_SPRITE_HANDLE 0x80

struct Sprite;
struct SpriteSlot;
union Fixed16;

void applySlotSpriteAnimation(struct SpriteSlot *slot);
void func_0207c664(struct SpriteSlot *slot);
void applySlotSpritePriority(struct SpriteSlot *slot);
void createSlotPoolSprite(struct SpriteSlot *slot);
struct Sprite *getSlotPoolSprite(u32 handle);
u16 getSlotSpriteAnimation(s32 handle);
struct SpriteSlot *getSpriteSlot(s32 index);
s32 isSlotSpriteCreated(s32 handle);
s32 releaseSlotSprite(s32 handle);
void updateSpriteSlots(void);
void applySlotSpritePalette(struct SpriteSlot *slot);
void setSlotSpriteAnimation(s32 handle, u16 animation);
void moveSlotSprite(s32 release, s32 handle, union Fixed16 dx, union Fixed16 dy, u16 frames, u16 delay);
void setSlotSpritePosition(s32 handle, s16 x, s16 y);
void setSlotSpriteAnimationByIndex(u16 index, u16 animation);
void func_0207c890(s32 index, u8 unk29);
void func_0207c8b8(s32 handle, u8 unk29);
void setSlotSpritePriorityByIndex(u16 index, u8 priority);
void setSlotSpritePriority(s32 handle, u8 priority);
void setSlotSpritePalette(s32 handle, u16 palette, u16 unk12);
void hideSlotSprite(s32 handle);
void showSlotSprite(s32 handle);
u32 createSlotSprite(u16 spriteId, s16 x, s16 y, u16 palette, u16 unk12, u32 handle);
s32 queueSlotSprite(s16 spriteId, s16 x, s16 y, s16 palette, u16 unk12, s32 handle);
void showSlotSpriteByIndex(s32 index);
struct SpriteSlot *findSpriteSlot(s32 handle);
s32 initSpriteSlots(void);

#endif /* BATTLE_SPRITE_SLOTS_H */
