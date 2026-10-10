#ifndef ITEMS_EQUIPMENT_H
#define ITEMS_EQUIPMENT_H

/* Numbers of three digit sprites, and whether a Digimon can equip a piece of
 * equipment. */

#include "types.h"

BOOL canEquip(s32 digimonId, s32 id);
void placeDigitSprites(s16 x, s16 y, s32 left, s32 middle, s32 right, u8 subScreen);

#endif /* ITEMS_EQUIPMENT_H */
