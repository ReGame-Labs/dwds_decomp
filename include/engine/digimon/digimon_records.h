#ifndef ENGINE_DIGIMON_DIGIMON_RECORDS_H
#define ENGINE_DIGIMON_DIGIMON_RECORDS_H

#include "types.h"

struct Digimon;

u16 func_020a2c9c(struct Digimon *digimon);
void func_020a2d34(void *record, u16 bits);
s32 func_020a2b94();
u16 func_020a2ca8(s32 id);
void func_020a2cc0(void *record, u16 bits);
s32 func_020a2d98(s32 slot);
void func_020a2f04(s32 slot, s32 id);
void func_020a2d1c(s32 id, u16 bits);
void func_020a2d48(s32 id, u16 bits);
s32 func_020a2c6c(void);
s32 func_020a2d60(s32 id);
s32 func_020a2da8(s32 id);
void func_020a2f14(void);
u8 func_020a2f3c(s32 mask);
void func_020a29c4(s32 species, struct Digimon *digimon);
s32 addDigimon(s32 species);
void func_020a2e18();

#endif /* ENGINE_DIGIMON_DIGIMON_RECORDS_H */
