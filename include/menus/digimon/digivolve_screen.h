#ifndef MENUS_DIGIMON_DIGIVOLVE_SCREEN_H
#define MENUS_DIGIMON_DIGIVOLVE_SCREEN_H

/* The digivolution screen's forms and buttons, the questions it asks
 * (FARM_TEXTS's 0x72 and 0x73) and its task's per-frame update. */

#include "types.h"

struct DigimonHistory;
struct DigivolveScreen;

struct DigimonHistory *func_ov006_02294684(struct DigivolveScreen *screen);
void func_ov006_022948f4(struct DigivolveScreen *screen);
void askDegenerate(struct DigivolveScreen *screen);
void func_ov006_022949ac(struct DigivolveScreen *screen);
void askDigivolve(struct DigivolveScreen *screen);
void func_ov006_02294d78(struct DigivolveScreen *screen);
void func_ov006_022953e4(struct DigivolveScreen *screen);
void func_ov006_022953f4(struct DigivolveScreen *screen);
void func_ov006_02295404(struct DigivolveScreen *screen);
void func_ov006_02295034(struct DigivolveScreen *screen);
void func_ov006_02294614(struct DigivolveScreen *screen);
void func_ov006_02294830(struct DigivolveScreen *screen);
void func_ov006_02294894(struct DigivolveScreen *screen);
void func_ov006_022948c8(s32 *next, s32 species);
void func_ov006_02294fb8(struct DigivolveScreen *screen);

#endif /* MENUS_DIGIMON_DIGIVOLVE_SCREEN_H */
