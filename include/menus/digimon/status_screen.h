#ifndef MENUS_DIGIMON_STATUS_SCREEN_H
#define MENUS_DIGIMON_STATUS_SCREEN_H

/* The status screen's graphics: the Digimon's details, the backgrounds and the
 * fonts, and the clearing of both screens; its task's per-frame update. */

#include "types.h"

struct StatusScreen;

void func_ov006_0228caf4(void);
void func_ov006_0228cc70(void);
void unloadStatusScreenFonts(void);
void loadStatusScreenFonts(void);
void func_ov006_0228cd80(void);
void freeStatusScreenBgs(struct StatusScreen *screen);
void loadStatusScreenBgs(void);

#endif /* MENUS_DIGIMON_STATUS_SCREEN_H */
