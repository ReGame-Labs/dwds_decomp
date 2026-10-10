#ifndef EGGS_EGG_HATCH_H
#define EGGS_EGG_HATCH_H

#include "types.h"

struct Digimon;

s32 func_0209a38c(s32 place);
s16 func_0209a408(s32 id);
void func_0209a1b8(s32 id, s32 gfxSlot);
void func_0209a1f8(s32 id);
s16 *func_0209a3dc(s32 id);
s32 func_0209a2d8(void);
s16 rollEggSpecies(s16 kind);
BOOL isEggReadyToHatch(struct Digimon *egg);
void *func_0209a220(s32 place);
s8 func_0209a31c(s32 id);

#endif /* EGGS_EGG_HATCH_H */
