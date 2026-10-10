#ifndef MENUS_SAVE_SAVE_MENU_H
#define MENUS_SAVE_SAVE_MENU_H

/* The save menu: its play time, its Yes/No window and its end. */

#include "engine/save/save_data.h"
#include "types.h"

void drawSaveChoiceFrame(struct SaveMenu *menu);
u8 isSaveMenuClosed(void);
void freeSaveMenu(struct SaveMenu *menu);
void printPlayTime(struct SaveMenu *menu);
s32 getPlayTime(s32 *hours, s32 *minutes, s32 *seconds);

#endif /* MENUS_SAVE_SAVE_MENU_H */
