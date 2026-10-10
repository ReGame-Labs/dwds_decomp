#ifndef FARM_RESULTS_FOOD_H
#define FARM_RESULTS_FOOD_H

/* The "Food Information" windows and the food window of the results of the
 * farm day. */

#include "types.h"

struct Results;

void setFarmFoodInfoFarm(s32 owner);
void drawFarmFoodInfo(u8 window, u8 consumedWindow, s32 owner);
void closeFarmFoodInfo(void);
void func_ov005_0227d0c4(void);
void openFoodWindow(s8 unk24, s16 unk26, struct Results *results);
void tickFarmFoodInfo(void);
void closeFoodWindow(void);
void openStatsCompare(s32 digimon, s8 palette, s8 unk2D, s16 unk2E);
void drawFoodWindow(u8 window, struct Results *results);

#endif /* FARM_RESULTS_FOOD_H */
