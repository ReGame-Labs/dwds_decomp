#ifndef MENUS_FARM_STATS_STATS_OPEN_H
#define MENUS_FARM_STATS_STATS_OPEN_H

/* Opening and closing the View Stats screen (openStatsScreen opens it), then
 * the start of the farm goods shop's helpers. */

#include "types.h"

struct Shop;

u8 isStatsScreenClosed(void);
void endStatsScreen(void);
void func_020cd6ac(struct Shop *shop);

#endif /* MENUS_FARM_STATS_STATS_OPEN_H */
