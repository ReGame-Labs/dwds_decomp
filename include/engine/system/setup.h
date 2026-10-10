#ifndef ENGINE_SYSTEM_SETUP_H
#define ENGINE_SYSTEM_SETUP_H

#include "types.h"

struct NNSG2dPaletteData;

/* A cell's scale and rotation, as the sprite drawing passes them: probably
 * NitroSystem's NNSG2dSRTControl. */
struct CellTransform {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 angle;  /* in 65536ths of a turn */
    /* 0x04 */ s32 scaleX; /* 20.12 fixed point */
    /* 0x08 */ s32 scaleY;
};

/* The flags of the systems set up once (isSystemSetUp), cleared when the game
 * starts. */
enum SystemFlag {
    SYSTEM_MAIN_MAP     = 0,
    SYSTEM_SUB_MAP      = 1,
    SYSTEM_MOVE_SCRIPTS = 8,
    SYSTEM_MOVIE_BUFFER = 9,
    SYSTEM_MOVIE_TASK   = 10,
};

void loadBgPalette(s32 bg, struct NNSG2dPaletteData *palette);
void clearSystemSetUp(s32 flag);
void setSystemSetUp(s32 flag);
void func_02044654(void);
s8 allocSubOamRotation(struct CellTransform *transform);
s8 allocMainOamRotation(struct CellTransform *transform);
s32 isSystemSetUp(s32 flag);
s8 allocSubOamAffine(struct CellTransform *transform);
s8 allocMainOamAffine(struct CellTransform *transform);
void setSubOamAffine(u8 index, s16 scaleX, s16 scaleY, u8 angle);
void setMainOamAffine(u8 index, s16 scaleX, s16 scaleY, u8 angle);
void initSystems(void);
void setSubOamRotation(s32 index, s32 angle);
void setMainOamRotation(s32 index, s32 angle);
void sortSubOam(void);
void sortMainOam(void);
void flushSubOam(void);
void flushMainOam(void);
void addSubOamEntry();

#endif /* ENGINE_SYSTEM_SETUP_H */
