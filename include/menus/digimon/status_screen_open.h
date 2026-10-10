#ifndef MENUS_DIGIMON_STATUS_SCREEN_OPEN_H
#define MENUS_DIGIMON_STATUS_SCREEN_OPEN_H

/* The status screen's opening and end, and the trait learning menu's questions
 * (FARM_TEXTS's 0x74 to 0x77) and the callback of its buttons. */

#include "types.h"

struct LearnTraitMenu;

u8 isStatusScreenClosed(void);
void onStatusScreenEnd(void);
void func_ov006_0228e550(struct LearnTraitMenu *menu, s16 state0, s16 state1);
void func_ov006_0228e690(void);
void func_ov006_0228e590(struct LearnTraitMenu *menu);
void func_ov006_0228e648(struct LearnTraitMenu *menu);
void func_ov006_0228e5d8(struct LearnTraitMenu *menu);
void func_ov006_0228e418();

#endif /* MENUS_DIGIMON_STATUS_SCREEN_OPEN_H */
