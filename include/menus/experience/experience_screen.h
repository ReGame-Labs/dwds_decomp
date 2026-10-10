#ifndef MENUS_EXPERIENCE_EXPERIENCE_SCREEN_H
#define MENUS_EXPERIENCE_EXPERIENCE_SCREEN_H

/* The screen of the experience gained ("Check experience gained") and the
 * system texts of data_02119350. */

#include "engine/data.h"
#include "types.h"

/* The task of the experience screen (func_0209f2b0), as far as the code in C
 * reads it. */
struct ExpScreen {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 unk20;    /* set by func_0209f980 */
    /* 0x24 */ s8 gfxSlots[3];
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u16 unk28;     /* freed with func_0208577c */
    /* 0x2A */ u16 unk2A;     /* freed with func_02085710 */
    /* 0x2C */ u8 windows[5];
    /* 0x31 */ s8 unk31;      /* freed with stopMainPaletteEffectsButFades */
    /* 0x32 */ s8 unk32;      /* freed with stopSubPaletteEffectsButFades */
};

void *func_0209ec68(s16 index);
BOOL func_0209ed64(void);
void func_0209f2b0(void);
void func_0209ec80(void);

#endif /* MENUS_EXPERIENCE_EXPERIENCE_SCREEN_H */
