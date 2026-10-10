#ifndef FARM_FARMS_H
#define FARM_FARMS_H

/* The farms and the goods in the save: making and deleting farms, their
 * levels, their digimon, and the goods, their stages and their data. */

#include "types.h"

struct Farm;
struct FarmGoods;
struct FarmGoodsData;
struct FarmEffect;

struct FarmGoodsData *getFarmGoodsData(u16 dataIndex);
s32 getFarmGoodsIdAt(s32 index);
struct FarmGoods *getFarmGoodsAt(s8 index);
s8 findFarmSlot(s32 id);
s16 getFarmGoodsDataById(u32 id);
s32 removeFarmDigimon(s32 id);
s8 getFarmPlaceById(s32 id);
struct FarmGoodsData *func_ov005_02293bf8(s32 id);
struct FarmGoodsData *func_ov005_02293c14(u32 id);
s32 createFarmGoods(s16 dataIndex);
s8 getFarmLevel(s32 slot, u32 level);
s32 raiseFarmLevel(s32 slot, u32 level);
s8 getFarmSlotAt(s8 place);
s32 getFarmIdAt(s8 place);
s32 raiseFarmLevelAt(s8 place, u32 level);
s8 getFarmLevelAt(s8 place, u32 level);
s32 countFarmLevelValuesAt(s8 place, u32 level);
s32 addFarmDigimonById(s32 farmId, s32 digimon);
s32 addFarmDigimonAt(s8 place, s32 digimon);
struct FarmEffect *getFarmGoodsEffect(u32 id, s32 index);
s32 getFarmGoodsId(s32 farmId, s32 index);
s32 findGoodsInFarm(s32 farmId, s32 id);
s32 findFarmGoodsIndex(s32 id);
struct FarmGoods *findFarmGoods(s32 id);
s32 countPlayerGoods(void);
s8 getFarmPlace(s8 slot);
void clearFarmScreenGlobals(void);
s8 growFarmGoods(s32 id);
s32 addFarmDigimon(s32 slot, s32 id);
s32 countFarmLevelValues(s32 slot, u32 level);
s32 createFarm(s8 kind);
s32 deleteFarm(s8 slot);
s32 makeTempFarmGoods(s16 dataIndex, struct FarmGoods *buf);
s32 deleteFarmGoods(s32 id);
s32 getFarmGoodsIdBySlot(s32 slot, s8 index);
s32 countFarmGoodsIcons(struct Farm *farm);

#endif /* FARM_FARMS_H */
