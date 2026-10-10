#ifndef FARM_FARM_QUERIES_H
#define FARM_FARM_QUERIES_H

/* Farm queries: a farm's kind, layout, name and goods capacity, and the farm a
 * digimon lives in. */

#include "types.h"

struct Farm;
struct FarmKind;
struct FarmLayout;

u16 *getFarmName(s32 place);
void *getFarmLayout(s32 index);
void *getFarmKindById(s32 id);
s32 getFarmFoodProducedById(s32 id);
/* Takes a digimon id; func_020a01d8 is still written calling it with no
 * arguments (its binary passes data_021df5f8 + 0x43C). */
s32 getDigimonFarmId();
struct FarmKind *getFarmKind(s32 kind);
struct Farm *func_ov005_02294be4(s16 index);
s32 countFarmGoods(s32 id);
u16 getFarmLayoutIndex(s32 slot);
struct FarmLayout *getFarmLayoutById(s32 id);
struct FarmLayout *getFarmLayoutBySlot(s32 slot);
s16 getFarmGoodsCapacity(s32 id);
s32 makeTempFarm(s8 kind, struct Farm *farm);
void setFarmName(s32 id, u16 *name);
struct Farm *findDigimonFarm(s32 id);
s32 getDigimonFarmPlace(s32 id);
s32 func_ov005_02294d4c(s32 id);
s32 func_ov005_02294d9c(s32 id, s32 value);
s32 countFarms(void);
void countFarmDigimonByStage(s32 id, s32 *counts);

#endif /* FARM_FARM_QUERIES_H */
