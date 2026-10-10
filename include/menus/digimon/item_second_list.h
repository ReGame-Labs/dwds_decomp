#ifndef MENUS_DIGIMON_ITEM_SECOND_LIST_H
#define MENUS_DIGIMON_ITEM_SECOND_LIST_H

/* The item menu's second list: its arrows and their callback, and its closing. */

#include "types.h"

struct ButtonGroup;
struct ItemMenu;

void func_ov006_0227cd80(struct ItemMenu *menu);
void func_ov006_0227cbd0(s16 button, s16 cursor, struct ButtonGroup *group);
void func_ov006_0227cdc4(struct ItemMenu *menu);
void func_ov006_0227d344(struct ItemMenu *menu);

#endif /* MENUS_DIGIMON_ITEM_SECOND_LIST_H */
