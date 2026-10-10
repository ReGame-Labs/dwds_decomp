#ifndef MENUS_DIGIMON_TAMER_PLAY_TIME_H
#define MENUS_DIGIMON_TAMER_PLAY_TIME_H

/* The Tamer screen's play time and friend count, and the reload of its mtm_top
 * backgrounds. */

#include "types.h"

struct TamerScreen;

void func_ov006_0227b6a0(void);
s16 countRosterFriends(void);
void drawPlayTime(struct TamerScreen *screen);

#endif /* MENUS_DIGIMON_TAMER_PLAY_TIME_H */
