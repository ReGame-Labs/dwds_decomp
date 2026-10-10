#ifndef BATTLE_CHARACTERS_BG_EFFECT_FILES_H
#define BATTLE_CHARACTERS_BG_EFFECT_FILES_H

/* The effects of /dat/bgeff/: loading and unloading their files for each
 * screen. */

#include "types.h"

void stopSubBgEffectTask(void);
s16 getSubBgEffectVram(s32 effect, s32 vramSlot);
s16 getMainBgEffectVram(s32 effect, s32 vramSlot);
void loadSubBgEffectPalette(s32 effect, s32 palette);
void loadMainBgEffectPalette(s32 effect, s32 palette);
void func_ov001_021fdeec(s32 effect);
void func_ov001_021fdf6c();
void func_ov001_021fe034();
void loadSubBgEffectChars();
void loadMainBgEffectChars();
void func_ov001_021fe408(s32 effect);
void func_ov001_021fe44c(s32 effect);
void loadSubBgEffect(s32 effect, s32 vramSlot, s32 palette);
void loadMainBgEffect(s32 effect, s32 vramSlot, s32 palette);

#endif /* BATTLE_CHARACTERS_BG_EFFECT_FILES_H */
