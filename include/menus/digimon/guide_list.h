#ifndef MENUS_DIGIMON_GUIDE_LIST_H
#define MENUS_DIGIMON_GUIDE_LIST_H

/* The Digimon guide's list: its rows and their buttons, and the arrows and
 * page buttons that scroll it. */

#include "types.h"

struct ButtonGroup;
struct DigimonGuide;

void func_ov006_0229ac6c(struct DigimonGuide *guide);
void func_ov006_0229ae8c(struct DigimonGuide *guide);
void func_ov006_0229b1c8(struct DigimonGuide *guide);
void func_ov006_0229ad58(s16 button, s16 cursor, struct ButtonGroup *group);
void func_ov006_0229afb4(s16 button, s16 cursor, struct ButtonGroup *group);
void func_ov006_0229b29c(struct DigimonGuide *guide);
void func_ov006_0229ac94(struct DigimonGuide *guide);
void func_ov006_0229aec4(struct DigimonGuide *guide);
void func_ov006_0229b1f0(struct DigimonGuide *guide);

#endif /* MENUS_DIGIMON_GUIDE_LIST_H */
