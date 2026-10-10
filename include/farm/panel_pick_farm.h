#ifndef FARM_PANEL_PICK_FARM_H
#define FARM_PANEL_PICK_FARM_H

/* The panel that picks a farm (FARM_PANEL_PICK_FARM). */

#include "types.h"

s32 isFarmTabsOpen(void);
s32 isFarmChoiceOpen(void);
void func_ov005_02282c58(void);
void openFarmTabs(s16 farm);
void func_ov005_02283048(void);
void closeFarmChoice(void);
s32 getChosenFarm(void);
void openFarmPages(s32 owner, s16 page, s8 palette);
void func_ov005_022833e4(void);
void func_ov005_02282a58(s32 touched, s32 selected, void *buttons);

#endif /* FARM_PANEL_PICK_FARM_H */
