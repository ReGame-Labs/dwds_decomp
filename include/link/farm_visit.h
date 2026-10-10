#ifndef LINK_FARM_VISIT_H
#define LINK_FARM_VISIT_H

/* The visit of another DS's farm, with the data the exchange brought
 * (data_021da40c), and the DigiEggs' table. */

#include "engine/data.h"
#include "types.h"

/* The task of a farm visit (func_0209b11c), as far as the code in C reads it. */
struct FarmVisit {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ u8 unk20[0x3E];
    /* 0x5E */ s8 gfxSlot;
};

/* The task of func_0209a694, as far as func_0209aa2c sets it. */
struct Task0209a694 {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ s16 unk20;
    /* 0x24 */ s32 unk24;
};

struct FarmGoods *func_0209a524(s32 index);
void func_0209abf8(void);
BOOL isFarmVisitRunning(void);
void func_0209ad9c(void);
void func_0209adfc(void);
void *func_0209a560();
struct Digimon *func_0209a5d8(s32 id);
struct Farm *func_0209a628(s32 id);
void func_0209a694(void);
void func_0209aa2c(s16 unk20, s32 unk24);
s32 func_0209ae38(struct Digimon *digimon);
s32 func_0209ae68(struct Digimon *digimon);
void func_0209b11c(void);
struct DigiEgg *getDigiEgg(s16 kind);

#endif /* LINK_FARM_VISIT_H */
