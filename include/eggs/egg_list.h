#ifndef EGGS_EGG_LIST_H
#define EGGS_EGG_LIST_H

/* The list of DigiEggs: three rows of a list of up to 10 eggs, with the
 * DigiEgg panel on the egg under the cursor. */

#include "engine/data.h"
#include "types.h"

#define EGG_LIST_ROWS 3
#define EGG_LIST_MAX_TOP 7 /* the last first row: 10 eggs in all */

/* The list's task (func_02097810), started by openEggList under UI flag
 * 0xD. */
struct EggList {
    struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ s8 gfxSlot;
    /* 0x21 */ u8 window; /* its sprites 0 and 1 scroll, 2 cancels */
    /* 0x22 */ u8 rowWindows[EGG_LIST_ROWS];
    /* 0x25 */ s8 top;    /* the egg on the first row */
    /* 0x26 */ s8 cursor; /* the row */
    /* 0x27 */ s8 palette; /* of its graphics (func_020aa1a4) */
    /* 0x28 */ u8 unk28;   /* passed to createLoopingMainSprite for its sprites */
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s8 eggs[12];
    /* 0x38 */ s32 rowSprites[EGG_LIST_ROWS][3]; /* -1 for none */
    /* 0x5C */ s32 buttons; /* touch buttons (createButtonGroup) */
    /* 0x60 */ s16 result;  /* -4 when cancelled */
    /* 0x62 */ s8 unk62;    /* from func_02083e78, freed with stopSubPaletteEffects */
};

void closeEggList(void);
BOOL isEggListOpen(void);
void func_02097810();
void func_02096e34();
void func_02096ef4();
void func_020975e4(s8 row);

#endif /* EGGS_EGG_LIST_H */
