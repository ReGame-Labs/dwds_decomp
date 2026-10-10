#ifndef MENUS_DIGIMON_OV006_0228666C_H
#define MENUS_DIGIMON_OV006_0228666C_H

/* The Digimon menu's unk5C buttons and unk340 sprites. */

#include "types.h"

struct ButtonGroup;
struct DigimonMenu;

u8 func_ov006_0228666c(struct DigimonMenu *menu);
void func_ov006_022866dc(struct DigimonMenu *menu);
void func_ov006_02286688(struct DigimonMenu *menu);
void func_ov006_022869cc(s16 button, s16 cursor, struct ButtonGroup *group);

#endif /* MENUS_DIGIMON_OV006_0228666C_H */
