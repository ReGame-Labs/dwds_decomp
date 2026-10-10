#ifndef EGGS_FAMILY_TREE_H
#define EGGS_FAMILY_TREE_H

/* A Digimon's family tree: the Digimon, its two parents and its four
 * grandparents (func_020985d0). */

#include "engine/data.h"
#include "types.h"

#define FAMILY_TREE_SPRITES 7

/* The family tree's task (func_02098914), started by openFamilyTree. */
struct FamilyTree {
    struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ s16 unk20;
    /* 0x24 */ struct Digimon *digimon;
    /* 0x28 */ u16 flags;    /* bit 0: leave the graphics set up on close */
    /* 0x2A */ s8 palette;   /* of its first graphics (func_020aa220) */
    /* 0x2B */ s8 palette2;  /* of the other two (func_020aa1a4) */
    /* 0x2C */ s8 unk2C;     /* passed to createLoopingSubSprite */
    /* 0x2D */ u8 unk2D;     /* passed to func_02097f0c */
    /* 0x2E */ s8 gfxSlots[3];
    /* 0x31 */ u8 windows[3];
    /* 0x34 */ s16 unk34;
    /* 0x38 */ s32 buttons;  /* touch buttons (createButtonGroup) */
    /* 0x3C */ u16 sprites[FAMILY_TREE_SPRITES]; /* 0xFFFF for none */
    /* 0x4A */ u8 unk4A[0x16];
    /* 0x60 */ s16 selected; /* the sprite func_020c2b64 gets on close */
};

s32 func_02098914();
void openFamilyTree(struct Digimon *digimon, s8 palette, s8 palette2, s8 unk2C, u8 unk2D, u16 flags);

#endif /* EGGS_FAMILY_TREE_H */
