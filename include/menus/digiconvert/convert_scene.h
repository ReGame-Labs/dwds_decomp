#ifndef MENUS_DIGICONVERT_CONVERT_SCENE_H
#define MENUS_DIGICONVERT_CONVERT_SCENE_H

#include "engine/data.h"
#include "types.h"

/* The conversion scene: the converter screen (menus/digiconvert/digiconvert.c) turns a species
 * scanned to 100% into a new Digimon. The scene clears the species' scan
 * percentage and makes the Digimon (createConvertedDigimon). Its task, its setup and
 * its teardown. */

/* The scene's block of the heap. */
struct ConvertWork {
    /* 0x000 */ struct BgGraphics bg;
    /* 0x018 */ u8 unk18[0x180];
};

/* The scene's task (tickConvert), started by startConvertTask. */
struct ConvertTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct ConvertWork *work;
    /* 0x20 */ u16 state;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u16 unk26;
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u16 unk2A; /* from the species' stage */
    /* 0x2C */ s32 unk2C; /* func_020a31d8's, of the species */
    /* 0x30 */ s32 species; /* the scanned species it converts */
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 windows[3]; /* 0xFF for none */
    /* 0x4C */ s32 unk4C;     /* freed by stopSubPaletteEffectsButFades */
};

void clearScanPercent(s32 species);
void closeConvertStatus(void);
void freeConvertText(void);
void initConvertText(void);
void freeSubWindowFrame(void);
void loadSubWindowFrame(void);
void freeConvertBg(struct ConvertTask *task);
void closeConvert(struct ConvertTask *task);
void endConvertTask(void);
void startConvertTask(s32 species);
void loadConvertBg(struct ConvertTask *task);

#endif /* MENUS_DIGICONVERT_CONVERT_SCENE_H */
