#ifndef MENUS_DIGIMON_ITEM_MENU_CHOICES_H
#define MENUS_DIGIMON_ITEM_MENU_CHOICES_H

/* The item menu's two choices, the displays of its lists, its fonts and the
 * clearing of its screens. */

#include "types.h"

struct ButtonGroup;
struct ItemMenu;

void func_ov006_0227f9b8(void);
void func_ov006_0227fa70(void);
void func_ov006_0227fb0c(void);
void func_ov006_0227fbe8(void);
void unloadItemMenuFonts(void);
void loadItemMenuFonts(void);
void func_ov006_0227fd6c(void);
void func_ov006_0227f8dc(struct ItemMenu *menu);
void func_ov006_0227f7e4(s16 button, s16 cursor, struct ButtonGroup *group);
void func_ov006_0227f904(struct ItemMenu *menu);

#endif /* MENUS_DIGIMON_ITEM_MENU_CHOICES_H */
