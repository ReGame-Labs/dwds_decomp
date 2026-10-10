#ifndef MENUS_DIGIMON_DIGIMON_MENU_STATUS_H
#define MENUS_DIGIMON_DIGIMON_MENU_STATUS_H

/* The Digimon menu's status displays, fonts and backgrounds, and the clearing
 * of its screens. */

#include "types.h"

struct DigimonMenu;

void func_ov006_02287ca4(void);
void func_ov006_02287d5c(void);
void redrawDigimonMenuStatus(void);
void func_ov006_02287e54(void);
void unloadDigimonMenuFonts(void);
void loadDigimonMenuFonts(void);
void func_ov006_02288020(void);
void freeDigimonMenuBgs(struct DigimonMenu *menu);
void func_ov006_022880d0(struct DigimonMenu *menu);
void func_ov006_02287cc4(struct DigimonMenu *menu);
void func_ov006_02287dc4(struct DigimonMenu *menu);
void func_ov006_02287e74(struct DigimonMenu *menu);

#endif /* MENUS_DIGIMON_DIGIMON_MENU_STATUS_H */
