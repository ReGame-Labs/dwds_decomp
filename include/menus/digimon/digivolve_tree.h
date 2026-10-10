#ifndef MENUS_DIGIMON_DIGIVOLVE_TREE_H
#define MENUS_DIGIMON_DIGIVOLVE_TREE_H

/* The digivolution screen's tree: what the form selected is to the digimon,
 * the conditions it meets, the scroll toward the actor selected and the name
 * of the form selected. */

#include "types.h"

struct DigivolveScreen;

s32 func_ov006_022933fc(struct DigivolveScreen *screen, s16 index);
s32 func_ov006_02293418(struct DigivolveScreen *screen);
u8 func_ov006_02293484(struct DigivolveScreen *screen);
void func_ov006_02293920(struct DigivolveScreen *screen);
void func_ov006_022938f0(struct DigivolveScreen *screen);
void func_ov006_022937ec(struct DigivolveScreen *screen);
s32 func_ov006_0229336c(struct DigivolveScreen *screen);
void func_ov006_022934ec(struct DigivolveScreen *screen);
s32 func_ov006_0229376c(struct DigivolveScreen *screen);

#endif /* MENUS_DIGIMON_DIGIVOLVE_TREE_H */
