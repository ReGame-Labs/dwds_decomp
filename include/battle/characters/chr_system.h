#ifndef BATTLE_CHARACTERS_CHR_SYSTEM_H
#define BATTLE_CHARACTERS_CHR_SYSTEM_H

/* Starting each screen's battle characters, the tile offset of the main
 * screen's effects, and the effects' ends. */

#include "types.h"

void clearBattleChrState(void);
void disableEffectTileOffset(void);
void enableEffectTileOffset(void);
void setEffectTileOffset(s16 x, s16 y);
void freeSubBgEffects(void);
void freeMainBgEffects(void);
void endAllSubBgEffects(void);
void endAllMainBgEffects(void);
void endSubBgEffect(u32 slot);
void endMainBgEffect(u32 slot);
void initMainBattleChrs(s32 size);
void initSubBattleChrs(s32 size);
void tickSubBgEffects(void);
void tickMainBgEffects(void);
u8 isSubBgEffectDone(s32 slot);
u8 isMainBgEffectDone(s32 slot);
void requestEndSubBgEffect(u32 slot);
void requestEndMainBgEffect(u32 slot);
u16 getSubBgEffectPalette(s32 effect);
u16 getMainBgEffectPalette(s32 effect);
void freeBgEffectFiles(s32 effect);

#endif /* BATTLE_CHARACTERS_CHR_SYSTEM_H */
