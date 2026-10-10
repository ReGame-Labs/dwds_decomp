#ifndef ENGINE_DIGIMON_GAME_DATA_H
#define ENGINE_DIGIMON_GAME_DATA_H

#include "types.h"

struct SpeciesData;

s32 *func_020a1238(void);
s32 *func_020a1244(void);
s32 func_020a1318(u32 item);
void *func_020a1410(u32 item);
struct SpeciesData *loadSpeciesData(); /* (s32 id), left open for a caller that passes none */
void *getDigimonAt(s32 index);
void *getDigimon(s32 id);
s32 func_020a1bac();
s32 findFreeDigimonIndex(void);
void *func_020a1250(u32 index);
void *func_020a1268(u32 index);
s32 findDigimonIndex(s32 id);
s32 func_020a11e0(s32 index);
u8 *func_020a128c(u32 id);
u8 *func_020a137c(s32 id);
u8 *func_020a142c(u32 id);
u8 *func_020a14e8(s32 id);

#endif /* ENGINE_DIGIMON_GAME_DATA_H */
