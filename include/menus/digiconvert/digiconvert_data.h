#ifndef MENUS_DIGICONVERT_DIGICONVERT_DATA_H
#define MENUS_DIGICONVERT_DIGICONVERT_DATA_H

/* The Digiconvert screen ("Use scan data and Digiconvert ...?", system text
 * 0x17): its task and work block, and the lists of species it shows. */

#include "engine/data.h"
#include "types.h"

/* The Digiconvert screen's work block: its backgrounds, the species ids in
 * five orders and a copy of each species' data. */
struct DigiconvertWork {
    /* 0x0000 */ struct BgGraphics bg02[2]; /* m_bg02 (bg file 0xF), loaded twice */
    /* 0x0030 */ u8 unk30[0x30];
    /* 0x0060 */ struct BgGraphics kaiten;  /* m_kaiten (bg file 0xE) */
    /* 0x0078 */ void *names;               /* the species' names, func_0204bef8's */
    /* 0x007C */ u16 *list;                 /* the order shown, one of lists */
    /* 0x0080 */ u8 nameRows[0x140];        /* createTextList's, for the names */
    /* 0x01C0 */ u16 lists[5][SPECIES_COUNT];
    /* 0x1264 */ u16 *scanTexts[8];         /* each row's scan data, as "999%" */
    /* 0x1284 */ s16 scanRows[8];
    /* 0x1294 */ u8 scanRowsList[0x140];    /* createTextList's, for the scan data */
    /* 0x13D4 */ struct TextWindow message;
    /* 0x13FC */ u8 unk13FC[0x180];
    /* 0x157C */ struct SpeciesData species[SPECIES_COUNT];
};

/* The 16-byte block the task's order points to. */
struct DigiconvertOrder {
    /* 0x0 */ u8 unk0[0xC];
    /* 0xC */ s16 order; /* -1 to 3: which of the work's lists is shown */
    /* 0xE */ u8 unkE[2];
};

/* Which rows of the list are shown, 8 at a time. */
struct DigiconvertScroll {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 top;    /* the first row shown */
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 maxTop; /* the species listed, less the rows */
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 rows;
};

/* The Digiconvert screen's task, DIGICONVERT (openDigiconvert makes it). */
struct Digiconvert {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ s32 species; /* the one picked, -1 for none */
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ struct DigiconvertWork *work;
    /* 0x2C */ struct DigiconvertOrder *order;
    /* 0x30 */ struct DigiconvertScroll *scroll;
    /* 0x34 */ void *unk34; /* 12 bytes */
    /* 0x38 */ s32 scrollBar;
    /* 0x3C */ s32 buttons;
    /* 0x40 */ s32 unk40;         /* openDial's */
    /* 0x44 */ s32 choiceButtons; /* the prompt's two (data_02116880) */
    /* 0x48 */ s32 nameList;
    /* 0x4C */ s32 scanList;
    /* 0x50 */ s32 arrowButtons; /* data_02116890 */
    /* 0x54 */ u8 unk54[0xC];
    /* 0x60 */ u32 scrollBarSprite;
    /* 0x64 */ u32 arrowSprites[2];
    /* 0x6C */ u8 unk6C[0x28];
    /* 0x94 */ u8 windows[5];
    /* 0x99 */ u8 unk99[5];
    /* 0x9E */ s8 unk9E; /* set by func_0205d8f0 */
    /* 0x9F */ u8 unk9F;
    /* 0xA0 */ s32 unkA0; /* freed by stopSubPaletteEffectsButFades */
    /* 0xA4 */ s32 unkA4; /* freed by stopMainPaletteEffectsButFades */
};

extern struct Digiconvert *DIGICONVERT;
/* The rects of the prompt's two buttons and of the two arrows: x, y, width
 * and height, read as a flat array (i * 4 + n). */
extern s16 data_02116880[];
extern s16 data_02116890[];

struct SpeciesData *getDigiconvertSpecies(s32 index);
void func_0205d8f0(void);
void clearSpeciesList(u16 *list);
void freeDigiconvertChoice(struct Digiconvert *digiconvert);
void loadDigiconvertSpecies(struct Digiconvert *digiconvert);
s32 func_0205d9e0();
s16 countListedSpecies(void);
void makeScanTexts();
void onDigiconvertChoice();
void createDigiconvertChoice(struct Digiconvert *digiconvert);

#endif /* MENUS_DIGICONVERT_DIGICONVERT_DATA_H */
