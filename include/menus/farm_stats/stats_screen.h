#ifndef MENUS_FARM_STATS_STATS_SCREEN_H
#define MENUS_FARM_STATS_STATS_SCREEN_H

/* The farm's "View Stats" screen: its task func_020cbde8 (still asm), opened by
 * openStatsScreen with a Digimon of the save, and its helpers. */

#include "engine/data.h"
#include "types.h"

/* The farm's View Stats screen, the task openStatsScreen starts. */
struct StatsScreen {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ s32 unk20; /* createMainSprite's, at (16, 168) */
    /* 0x24 */ s32 unk24; /* createSubSprite's */
    /* 0x28 */ s32 unk28; /* createMainSprite's, at (164, 176) */
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ struct Digimon *digimon;
    /* 0x34 */ u8 windows[10]; /* createMenuWindow's, 0xFF for none */
    /* 0x3E */ u8 unk3E[2];
    /* 0x40 */ s32 unk40;    /* freed by stopSubPaletteEffectsButFades */
    /* 0x44 */ s32 unk44;    /* freed by stopMainPaletteEffectsButFades */
    /* 0x48 */ s32 buttons;  /* the task id of the page's button group, -1 for none */
    /* 0x4C */ s16 unk4C;    /* the choice of func_020ca1a8's group, 0 to 3 */
    /* 0x4E */ s16 page;     /* of the ability pages (func_020c9b88) */
    /* 0x50 */ s32 flags;    /* enum StatsScreenFlag */
    /* 0x54 */ void *buffer; /* 0x50 bytes of the heap, freed by endStatsScreen */
    /* 0x58 */ s16 unk58;    /* allocSubVram's */
    /* 0x5A */ s16 unk5A;    /* allocMainVram's */
    /* 0x5C */ s16 unk5C;    /* allocSubVram's */
    /* 0x5E */ s16 unk5E;    /* allocSubVram's */
    /* 0x60 */ s16 unk60;    /* allocMainVram's */
    /* 0x62 */ s16 unk62;    /* allocMainVram's */
    /* 0x64 */ s16 unk64;    /* allocMainVram's */
};

enum StatsScreenFlag {
    STATS_SHOW_MODEL = 0x1, /* func_020cb538 draws the Digimon's battle model and clears it */
};

/* The state the ability pages leave the screen in when they close; no case of
 * func_020cbde8 handles it. */
#define STATS_STATE_ABILITIES_CLOSED 0x23FA

void func_020cb5ec(void);
void func_020cb61c(void);
void func_020cb66c(void);
void func_020cb6fc(void);
void freeStatsScreenBgs(struct StatsScreen *screen);
void loadStatsScreenBgs(void);

#endif /* MENUS_FARM_STATS_STATS_SCREEN_H */
