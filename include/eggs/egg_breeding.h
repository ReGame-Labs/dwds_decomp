#ifndef EGGS_EGG_BREEDING_H
#define EGGS_EGG_BREEDING_H

/* DigiEggs: making them from two parents, the DigiEgg gallery and the
 * conditions to hatch. */

#include "engine/data.h"
#include "types.h"

/* The DigiEgg gallery's task (func_02098ea0), as far as the code in C reads
 * it. */
struct EggGallery {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ s8 unk20; /* freed with stopMainPaletteEffects */
    /* 0x21 */ s8 unk21; /* freed with stopSubPaletteEffects */
    /* 0x22 */ u16 unk22; /* freed with func_0208577c */
    /* 0x24 */ u16 unk24; /* freed with func_02085710 */
};

BOOL func_02099534(s32 species, struct Digimon *digimon);
BOOL func_02099578(s32 species, struct Digimon *digimon);
void func_02098e08(void);
void func_02098ea0(void);
void func_0209928c(void);
void func_020993a4(s32 id, s32 unk2D, s32 unk30);
BOOL func_02098e7c(void);
s32 createEgg(s8 kind, s16 size, struct Digimon *parentA, u16 *tamerA, struct Digimon *parentB, u16 *tamerB);
BOOL func_020995a4(s32 condition, s32 value, struct Digimon *egg, s32 arg3);
s32 func_020993dc(struct Digimon *digimon);

#endif /* EGGS_EGG_BREEDING_H */
