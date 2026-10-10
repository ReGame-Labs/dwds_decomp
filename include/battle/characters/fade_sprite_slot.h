#ifndef BATTLE_CHARACTERS_FADE_SPRITE_SLOT_H
#define BATTLE_CHARACTERS_FADE_SPRITE_SLOT_H

/* The fade of a range of colours, the lists of effect sprites and the effects'
 * tasks. */

#include "types.h"

void initBgEffects(void);
void freeListSprites(void);
void endAllMainListSprites(void);
void clearListSprites(void);
u8 isFadeDone(void);
void clearFadeTask(void);
u8 isMoveScriptDone(void);
void stopMainBgEffectTask(void);
void startSubBgEffectTask(void);
void startMainBgEffectTask(void);
void stopListSpriteTask(void);
void startListSpriteTask(void);
void tickFadeTask(void);
void startFadeTask(s16 start, s16 count, s16 level);
BOOL runMoveScriptCommand(void);
u8 isMainListSpriteDone(u32 index);
void tickListSprites(void);
void startMainListSprite(s32 kind, s32 palette, s16 x, s16 y, s16 seq, u32 index);
void endSubListSprite(s32 index);
void endMainListSprite(s32 index);

#endif /* BATTLE_CHARACTERS_FADE_SPRITE_SLOT_H */
