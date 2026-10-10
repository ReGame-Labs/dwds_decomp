#ifndef MENUS_WIDGETS_DIGIMON_DETAIL_H
#define MENUS_WIDGETS_DIGIMON_DETAIL_H

#include "types.h"

/* The Digimon details displays (struct DigimonDetail). */

struct Digimon;

s32 func_02059c50();
s32 func_02059d84(void);
void func_02059acc(s16 index, s16 unkCC, s16 unkCE, s16 unkD0, u16 unkD2, u16 unkD4);
void drawDigimonDetail();
void setDigimonDetailDigimon(s16 index, struct Digimon *digimon);
void freeDigimonDetailSprites(s16 index);

#endif /* MENUS_WIDGETS_DIGIMON_DETAIL_H */
