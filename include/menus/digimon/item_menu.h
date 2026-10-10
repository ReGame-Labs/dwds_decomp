#ifndef MENUS_DIGIMON_ITEM_MENU_H
#define MENUS_DIGIMON_ITEM_MENU_H

/* The item menu's backgrounds and its task's run function
 * (tickItemMenu). */

#include "types.h"

struct ItemMenu;

void freeItemMenuBgs(struct ItemMenu *menu);
void loadItemMenuBgs(struct ItemMenu *menu);

#endif /* MENUS_DIGIMON_ITEM_MENU_H */
