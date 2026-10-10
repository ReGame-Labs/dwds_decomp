#ifndef FARM_PANEL_STATUS_H
#define FARM_PANEL_STATUS_H

/* The status of the digimon shown in the digimon panels (FARM_PANEL_DIGIMON
 * and FARM_PANEL_DIGIMON_B). */

#include "types.h"

struct Digimon;
struct DigimonPanel;

void func_ov005_02280704(void);
void func_ov005_022809f4(void);
void func_ov005_022804c0(struct DigimonPanel *panel, struct Digimon *digimon);
void func_ov005_022805e0(struct DigimonPanel *panel, struct Digimon *digimon);

#endif /* FARM_PANEL_STATUS_H */
