#ifndef MENUS_DIGIMON_DIGIMON_MENU_TABS_H
#define MENUS_DIGIMON_DIGIMON_MENU_TABS_H

/* The Digimon menu's three tabs and the menu of three by a row of its
 * equipment. */

#include "types.h"

struct ButtonGroup;
struct DigimonMenu;

void pauseDigimonMenuTabs(struct DigimonMenu *menu);
void resumeEquipSlotRows(struct DigimonMenu *menu);
void pauseEquipSlotRows(struct DigimonMenu *menu);
void closeDigimonMenuTabs(struct DigimonMenu *menu);
void closeEquipSlotPopup(struct DigimonMenu *menu);
void func_ov006_02284744(s16 button, s16 cursor, struct ButtonGroup *group);
void openDigimonMenuTabs(struct DigimonMenu *menu);
void func_ov006_0228498c(s16 button, s16 cursor, struct ButtonGroup *group);
void openEquipSlotPopup(struct DigimonMenu *menu);

#endif /* MENUS_DIGIMON_DIGIMON_MENU_TABS_H */
