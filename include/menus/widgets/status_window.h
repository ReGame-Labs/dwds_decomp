#ifndef MENUS_WIDGETS_STATUS_WINDOW_H
#define MENUS_WIDGETS_STATUS_WINDOW_H

#include "types.h"

/* The status windows (struct StatusWindow): a Digimon's status, drawn by
 * drawStatusWindow. */

s32 func_02058590();
s32 func_020587fc();
s32 func_02058a24(void);
void drawStatusWindow();
void freeStatusWindowSprites(s16 index);

#endif /* MENUS_WIDGETS_STATUS_WINDOW_H */
