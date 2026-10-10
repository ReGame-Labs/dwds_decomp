#ifndef EGGS_EGG_PANEL_H
#define EGGS_EGG_PANEL_H

/* The DigiEgg panel: a window that shows one DigiEgg (func_0209661c), and
 * the start of the menu around it (func_02095c4c). */

#include "engine/data.h"
#include "types.h"

/* The menu func_02095c4c runs (engine/script/interpreter.c), started by func_020964ec
 * under UI flag 0xE; it opens the DigiEgg panel on egg, with unk20 for the
 * panel's palette and unk22 for its unk21. */
struct EggMenu {
    struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ s8 unk20;
    /* 0x21 */ s8 palette; /* of its graphics (func_020aa1a4) */
    /* 0x22 */ s8 unk22;
    /* 0x23 */ s8 unk23;   /* passed to createLoopingMainSprite for its sprites */
    /* 0x24 */ u16 egg;
};

/* The DigiEgg panel task (func_02096a9c), under UI flag 0xC. */
struct EggPanel {
    struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ s8 palette;   /* of its graphics (func_020aa220) */
    /* 0x21 */ s8 unk21;     /* passed to createLoopingSubSprite for its sprites */
    /* 0x22 */ s8 egg;       /* the DigiEgg shown */
    /* 0x23 */ s8 nextEgg;   /* the one showEggOnPanel asked for */
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 window;
    /* 0x27 */ s8 gfxSlot;
    /* 0x28 */ s32 unk28;    /* freed by func_020c7060; -1 for none */
};

void closeEggPanel(void);
void showEggOnPanel(s8 egg);
void func_020964ec(s8 unk20, s8 palette, s8 unk22, s8 unk23, u16 egg);
void func_02096a9c();
void openEggPanel(s8 egg, s8 palette, s8 unk21, s16 unk24);

#endif /* EGGS_EGG_PANEL_H */
