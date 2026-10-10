#ifndef FARM_PANEL_PAGES_H
#define FARM_PANEL_PAGES_H

/* The farm's pages (FARM_PANEL_PAGES) and the tabs (FARM_PANEL_TABS) that turn
 * them. */

#include "types.h"

struct Digimon;
struct Window;

s32 func_ov005_02280d24();
void setFarmPage(s32 owner, s16 page);
void func_ov005_02281004(u16 flags, struct Window *window);
void closeFarmPages(void);
void openSecondDigimonPanel(struct Digimon *digimon, s8 palette, s16 mode);
void openDigimonPanel(struct Digimon *digimon, s8 palette, s16 mode);
void func_ov005_02281080(void);

#endif /* FARM_PANEL_PAGES_H */
