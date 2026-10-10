#ifndef MENUS_DIGIMON_ITEM_FIRST_LIST_H
#define MENUS_DIGIMON_ITEM_FIRST_LIST_H

/* The item menu's first list: its arrows and their callback, and its closing. */

#include "types.h"

struct ButtonGroup;
struct ItemMenu;

void func_ov006_0227ef34(struct ItemMenu *menu);
void func_ov006_0227ed84(s16 button, s16 cursor, struct ButtonGroup *group);
void func_ov006_0227ef78(struct ItemMenu *menu);
void func_ov006_0227f508(struct ItemMenu *menu);

#endif /* MENUS_DIGIMON_ITEM_FIRST_LIST_H */
