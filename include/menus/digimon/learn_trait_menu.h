#ifndef MENUS_DIGIMON_LEARN_TRAIT_MENU_H
#define MENUS_DIGIMON_LEARN_TRAIT_MENU_H

/* The trait learning menu's choice, windows and buttons, its backgrounds and
 * fonts, and its task's per-frame update. */

#include "types.h"

struct LearnTraitMenu;

void func_ov006_0228eb90(struct LearnTraitMenu *menu);
void func_ov006_0228eda0(void);
void unloadLearnTraitMenuFonts(void);
void loadLearnTraitMenuFonts(void);
void freeLearnTraitMenuBgs(struct LearnTraitMenu *menu);
void loadLearnTraitMenuBgs(struct LearnTraitMenu *menu);
void func_ov006_0228ea88(struct LearnTraitMenu *menu);
void func_ov006_0228e900(struct LearnTraitMenu *menu);
void func_ov006_0228e9bc(struct LearnTraitMenu *menu);
void tickLearnTraitMenu(void);

#endif /* MENUS_DIGIMON_LEARN_TRAIT_MENU_H */
