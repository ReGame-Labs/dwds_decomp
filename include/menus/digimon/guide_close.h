#ifndef MENUS_DIGIMON_GUIDE_CLOSE_H
#define MENUS_DIGIMON_GUIDE_CLOSE_H

/* The Digimon guide's closing. */

#include "types.h"

struct DigimonGuide;

u8 isDigimonGuideClosed(void);
void closeDigimonGuide(struct DigimonGuide *guide);

#endif /* MENUS_DIGIMON_GUIDE_CLOSE_H */
