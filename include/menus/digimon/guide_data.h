#ifndef MENUS_DIGIMON_GUIDE_DATA_H
#define MENUS_DIGIMON_GUIDE_DATA_H

/* The Digimon guide's data and texts: its copy of every species' data, the
 * texts of DigZknHelp.sdb, the fonts and its text windows. */

#include "types.h"

struct SpeciesData;
struct DigimonGuide;

void freeGuideTexts(void);
void loadGuideTexts(void);
struct SpeciesData *func_ov006_02299818(s32 species);
void func_ov006_02299840(u16 *list);
void func_ov006_0229972c(void);
void func_ov006_022997bc(struct DigimonGuide *guide);
void loadGuideFonts(void);
void func_ov006_0229914c(void);
void func_ov006_02299364(void);
void func_ov006_02299548(void);

#endif /* MENUS_DIGIMON_GUIDE_DATA_H */
