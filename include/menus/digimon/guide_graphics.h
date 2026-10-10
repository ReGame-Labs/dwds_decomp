#ifndef MENUS_DIGIMON_GUIDE_GRAPHICS_H
#define MENUS_DIGIMON_GUIDE_GRAPHICS_H

/* The Digimon guide's backgrounds, the sprites placed by the screens' scroll
 * and the cursor's Digimon walking in as an actor. */

#include "types.h"

struct DigimonGuide;

void func_ov006_0229c04c(void);
void func_ov006_0229c104(void);
void func_ov006_0229c164(void);
void func_ov006_0229c4d4(void);
void func_ov006_0229c638(void);
void func_ov006_0229c6f4(struct DigimonGuide *guide);
void func_ov006_0229c7bc(struct DigimonGuide *guide);

#endif /* MENUS_DIGIMON_GUIDE_GRAPHICS_H */
