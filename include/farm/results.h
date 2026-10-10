#ifndef FARM_RESULTS_H
#define FARM_RESULTS_H

/* The results of the farm day: settling the food, aging the goods and the
 * digimon's stats before and after. */

#include "types.h"

struct Digimon;
struct Results;

struct Results *getResults(void);
s32 isResultsOpen(void);
void func_ov005_0227dad4(void);
void settleFarmFood(struct Results *results);
void closeResults(void);
void openFarmFoodInfo(s32 owner, s8 unk28, s16 unk2A);
void func_ov005_0227dd28(void);
void func_ov005_0227d914(void);
struct Digimon *getDigimonBeforeDay(s32 digimon);
void ageFarmGoods(void);

#endif /* FARM_RESULTS_H */
