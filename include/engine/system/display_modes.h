#ifndef ENGINE_SYSTEM_DISPLAY_MODES_H
#define ENGINE_SYSTEM_DISPLAY_MODES_H

/* Species and where the Digimon kept are: the species table data_02111bf8,
 * the stages, and counts of the Digimon kept. */

#include "types.h"

/* The stages, as the texts 32 to 37 of data_0210b7f0 name them. */
#define STAGE_IN_TRAINING 0
#define STAGE_ROOKIE 1
#define STAGE_CHAMPION 2
#define STAGE_ULTIMATE 3
#define STAGE_MEGA 4
#define STAGE_ARMOR 5

/* Where a Digimon is (getDigimonPlace). */
#define PLACE_GROUP 0
#define PLACE_PARTY 1
#define PLACE_ELSEWHERE 2

s32 func_020a30d4();
s32 getSpeciesStage(s32 species);
s32 func_020a31e8(s32 key);
s32 func_020a331c();
s32 func_020a3418();
s32 func_020a3454();
s32 func_020a3360(s32 id);
s32 getDigimonPlace(s32 id);
s32 func_020a3098(s32 species);
u16 func_020a31b0(s32 species);
s32 func_020a31c4(s32 species);
s32 func_020a31d8(s32 species);
s32 func_020a3224(s32 species);
s32 countDigimonAtStage(u8 stage);
s32 func_020a3294(s32 value);
s32 func_020a32d8(s32 value);

#endif /* ENGINE_SYSTEM_DISPLAY_MODES_H */
