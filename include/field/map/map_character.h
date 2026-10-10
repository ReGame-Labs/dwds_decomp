#ifndef FIELD_MAP_MAP_CHARACTER_H
#define FIELD_MAP_MAP_CHARACTER_H

/* Map characters on each screen: loading and releasing them, the task of their
 * sprites, and the map's scrolling. */

#include "types.h"

BOOL isSubMapScrollDone(void);
BOOL isMainMapScrollDone(void);
void stopMainMapScroll(void);
void startSubMapSpriteTask(void);
void startMainMapSpriteTask(void);
void stopSubMapSpriteTask(void);
void stopMainMapSpriteTask(void);
void func_ov000_021fb830();
void loadSubMapCharacter(u16 character, s32 slot);
void initMapSprites(void);
void releaseSubMapCharacter(s32 character);
void releaseMainMapCharacter(s32 character);
void func_ov000_021fb95c(s16 x, s16 y, s16 value);
void scrollSubMap(s16 x, s16 y, s16 value);

#endif /* FIELD_MAP_MAP_CHARACTER_H */
