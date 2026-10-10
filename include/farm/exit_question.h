#ifndef FARM_EXIT_QUESTION_H
#define FARM_EXIT_QUESTION_H

/* The "Exit DigiFarm?" question of the farm screen. */

#include "types.h"

struct Task02292f48;

void askExitFarm(void);
s32 func_ov005_02292f48();
void func_ov005_02292cfc(struct Task02292f48 *task);
void func_ov005_02292d5c(u8 window, s32 text);

#endif /* FARM_EXIT_QUESTION_H */
