#ifndef MENUS_FIELD_MENU_PANEL_H
#define MENUS_FIELD_MENU_PANEL_H

#include "types.h"

/* The panels of menus/field_menu/panel.c's: 10 by 4 tile areas of a window with two
 * images and a sprite. */

#define PANEL_WIDTH 10 /* in tiles */
#define PANEL_HEIGHT 4

void freePanelSprite(s16 index);
void closePanel(s16 index);

#endif /* MENUS_FIELD_MENU_PANEL_H */
