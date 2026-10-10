#ifndef MENUS_DIGIMON_ITEM_MENU_POPUPS_H
#define MENUS_DIGIMON_ITEM_MENU_POPUPS_H

/* The item menu's popups: the menu of three options by a row of the first list
 * and the dialog of two choices. */

#include "types.h"

struct ButtonGroup;
struct ItemMenu;

void func_ov006_0227e9a8(struct ItemMenu *menu);
void func_ov006_0227ec34(struct ItemMenu *menu);
void func_ov006_0227e520(struct ItemMenu *menu);
void func_ov006_0227e804(s16 button, s16 cursor, struct ButtonGroup *group);
void func_ov006_0227e9dc(struct ItemMenu *menu);
void func_ov006_0227eac4(s16 button, s16 cursor, struct ButtonGroup *group);
void func_ov006_0227ec68(struct ItemMenu *menu);

#endif /* MENUS_DIGIMON_ITEM_MENU_POPUPS_H */
