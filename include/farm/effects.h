#ifndef FARM_EFFECTS_H
#define FARM_EFFECTS_H

/* Putting the effects of goods and events on a digimon, and the goods' icon. */

#include "types.h"

struct Digimon;
struct FarmEffect;

u16 func_ov005_0228f924(void);
void applyFarmEffect(struct Digimon *digimon, s32 *after, s32 *before, struct FarmEffect *effect);
void applyEventEffect(struct Digimon *digimon, s32 *after, s32 *before, u16 event, u16 n);
void applyGoodsEffect(struct Digimon *digimon, s32 *after, s32 *before, u32 id);
void tickFarmEventTask();
void func_ov005_0228f8a8(void);

#endif /* FARM_EFFECTS_H */
