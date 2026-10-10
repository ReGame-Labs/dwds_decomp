#ifndef MENUS_DIGIMON_TAMER_SCREEN_H
#define MENUS_DIGIMON_TAMER_SCREEN_H

/* The Tamer screen, the field menu's "Check info for <name>": its task, its
 * three buttons and its backgrounds. */

#include "types.h"

struct TamerScreen;

void func_ov006_0227c088(void);
void freeTamerScreenBgs(struct TamerScreen *screen);
u8 isTamerScreenClosed(void);
void func_ov006_0227cb7c(struct TamerScreen *screen);
void func_ov006_0227bebc(struct TamerScreen *screen);

#endif /* MENUS_DIGIMON_TAMER_SCREEN_H */
