#ifndef MENUS_DIGIMON_ITEM_MENU_OPEN_H
#define MENUS_DIGIMON_ITEM_MENU_OPEN_H

/* The item menu's task, made by openItemMenu, and its end; the Digimon
 * menu's icons and what shows or hides them. */

#include "types.h"

struct ItemMenu;

u8 isItemMenuClosed(void);
void func_ov006_02281c18(void);
void func_ov006_02281c58(void);
void func_ov006_02281c98(void);
void onItemMenuEnd(void);
void func_ov006_02281b38(struct ItemMenu *menu);
void func_ov006_02281dd8(u8 flag0, u8 flag1, u8 flag2, u8 flag3, u8 flag4, u8 mode);

#endif /* MENUS_DIGIMON_ITEM_MENU_OPEN_H */
