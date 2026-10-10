#ifndef MENUS_DIGIMON_GUIDE_TABS_H
#define MENUS_DIGIMON_GUIDE_TABS_H

/* The Digimon guide's tab buttons, the buttons of sprites 12 and 13 and the
 * rows' callback. */

#include "types.h"

struct ButtonGroup;
struct DigimonGuide;

void func_ov006_0229a228(struct DigimonGuide *guide);
void func_ov006_0229a5d8(struct DigimonGuide *guide);
void func_ov006_0229a260(struct DigimonGuide *guide);
void func_ov006_0229a3b0(s16 touched, s16 cursor, struct ButtonGroup *group);
void func_ov006_0229a600(struct DigimonGuide *guide);
void func_ov006_0229a6d4(s16 touched, s16 cursor, struct ButtonGroup *group);

#endif /* MENUS_DIGIMON_GUIDE_TABS_H */
