#ifndef MENUS_DIGIMON_GUIDE_ORDERS_H
#define MENUS_DIGIMON_GUIDE_ORDERS_H

/* The Digimon guide's lists of species in each order, the touch test of its
 * buttons, the battle character's button and the callback of the buttons of
 * sprites 12 and 13. */

#include "types.h"

struct ButtonGroup;
struct DigimonGuide;

void func_ov006_02299c34(s16 touched, s16 cursor, struct ButtonGroup *group);
void func_ov006_02299cd0(struct DigimonGuide *guide);
s32 func_ov006_02299b64(s16 *rects, s32 count);
void func_ov006_02299c98(struct DigimonGuide *guide);
s16 func_ov006_02299b24(void);
void func_ov006_02299d3c(s16 touched, s16 cursor, struct ButtonGroup *group);
void func_ov006_02299a90(u16 *list);
void func_ov006_022999f8(u16 *list);

#endif /* MENUS_DIGIMON_GUIDE_ORDERS_H */
