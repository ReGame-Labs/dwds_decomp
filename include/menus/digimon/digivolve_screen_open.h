#ifndef MENUS_DIGIMON_DIGIVOLVE_SCREEN_OPEN_H
#define MENUS_DIGIMON_DIGIVOLVE_SCREEN_OPEN_H

/* The digivolution screen's setting up and tearing down: its backgrounds,
 * fonts and palette effects, its making (openDigivolveScreen) and its end. */

#include "types.h"

struct DigivolveScreen;

void func_ov006_02296c3c(struct DigivolveScreen *screen);
void func_ov006_02296dbc(void);
void func_ov006_02296e1c(void);
void unloadDigivolveScreenFonts(void);
void loadDigivolveScreenFonts(void);
void loadDigivolveScreenBgs(struct DigivolveScreen *screen);
void onDigivolveScreenEnd(void);
u8 isDigivolveScreenClosed(void);
void func_ov006_02296fbc(struct DigivolveScreen *screen);
void freeDigivolveScreenBgs(struct DigivolveScreen *screen);
void func_ov006_022974fc(struct DigivolveScreen *screen);
void closeDigivolveScreen(struct DigivolveScreen *screen);

#endif /* MENUS_DIGIMON_DIGIVOLVE_SCREEN_OPEN_H */
