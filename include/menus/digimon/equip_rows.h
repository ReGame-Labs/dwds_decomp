#ifndef MENUS_DIGIMON_EQUIP_ROWS_H
#define MENUS_DIGIMON_EQUIP_ROWS_H

/* The Digimon menu's rows of equipment and of traits. */

#include "types.h"

struct ButtonGroup;
struct DigimonMenu;

void closeEquipSlotRows(struct DigimonMenu *menu);
void func_ov006_02285154(s16 button, s16 cursor, struct ButtonGroup *group);
void closeTraitRows(struct DigimonMenu *menu);
void openTraitRows(struct DigimonMenu *menu);
void func_ov006_02285424(s16 button, s16 cursor, struct ButtonGroup *group);

#endif /* MENUS_DIGIMON_EQUIP_ROWS_H */
