#ifndef MENUS_DIGIMON_LEARN_TRAIT_MENU_OPEN_H
#define MENUS_DIGIMON_LEARN_TRAIT_MENU_OPEN_H

/* The trait learning menu's opening and closing; for the digivolution screen,
 * the m_win00 window frames, the text drawing flags, its windows
 * (func_ov006_022903a8) and the drawing of func_ov006_022905dc. */

#include "types.h"

struct Digimon;
struct LearnTraitMenu;

u8 isLearnTraitMenuClosed(void);
void closeLearnTraitMenu(struct LearnTraitMenu *menu);
void onLearnTraitMenuEnd(void);
void func_ov006_02290300(s32 mode);
void func_ov006_02290354(s32 mode);
void func_ov006_022905bc(void);
s32 loadSubWindowFrame00InSlot(s8 slot, s32 palette);
s32 loadMainWindowFrame00InSlot(s8 slot, s32 palette);
void unloadSubWindowFrame00(void);
void unloadMainWindowFrame00(void);
void openLearnTraitMenu(struct Digimon *digimon, s16 id);

#endif /* MENUS_DIGIMON_LEARN_TRAIT_MENU_OPEN_H */
