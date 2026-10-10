#ifndef FARM_OPEN_PICK_FARM_H
#define FARM_OPEN_PICK_FARM_H

/* The window with a digimon's name and icon, and opening panel
 * FARM_PANEL_PICK_FARM to pick a farm for it. */

#include "types.h"

struct DigimonNameWindow;

void func_ov005_022843e4(struct DigimonNameWindow *task);
void func_ov005_022844c8(struct DigimonNameWindow *task);
void func_ov005_0228478c(void);
void func_ov005_0228463c(struct DigimonNameWindow *task);
void openFarmChoice(s32 digimon, s16 flags);

#endif /* FARM_OPEN_PICK_FARM_H */
