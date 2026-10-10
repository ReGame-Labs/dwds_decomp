#ifndef FARM_FARM_SCREEN_H
#define FARM_FARM_SCREEN_H

/* The farm screen: its map, view and actors, the farm day and its events, the
 * food the farms gather and eat, and what the goods give the digimon. */

#include "types.h"

struct Farm;
struct FarmScreen;
struct FarmDayTimer;
struct FarmEffect;

s32 func_ov005_02285034(void);
void func_ov005_02286424(void);
struct FarmScreen *getFarmScreen(void);
s32 func_ov005_02286010(s32 id);
s32 rollFarmFoodProduced(s32 id);
s32 getFarmFoodProduced(s32 id);
s16 rollFarmEffect(struct FarmEffect *effect);
s32 func_ov005_02286198();
void closeFarmScreen(void);
void drawFarmName(void);
void func_ov005_02284fd4(u16 actor, s32 digimon, s32 farm, s16 event);
void tickFarmScreen(void);
void openFarmScreen(s32 id);
void func_ov005_02287dc8(s32 type, s8 amount, s32 *rates);
void func_ov005_022880e0(s32 *rates, struct Farm *farm);
void func_ov005_02288e20(void);
void func_ov005_022867bc(struct FarmScreen *screen);
void func_ov005_02288d08(u16 slot, s16 x, s16 y);
void func_ov005_02286514(s32 index);
void func_ov005_0228622c(struct FarmScreen *screen);
void func_ov005_022862d4(struct FarmScreen *screen);
s32 pickFarmGoods(struct Farm *farm);
void func_ov005_022863c4(s32 percent);
void func_ov005_022874f8(struct FarmDayTimer *timer);
void tickFarmDayTimer(void);
s32 getFoodProduced(void);
s32 func_ov005_02287070(s32 id, s32 *digimon);
u16 func_ov005_022871bc(s32 id, s32 item, s32 digimon, s32 owner);
void func_ov005_022872c0(struct FarmScreen *screen);
s32 getFoodConsumed(void);
s32 getFarmFoodConsumed(s32 id);
void func_ov005_022883e0(s32 digimon, s32 id, s32 item);
void giveFarmGoodsEffects(s32 id, s32 digimon);
void func_ov005_02288e40();

#endif /* FARM_FARM_SCREEN_H */
