#ifndef ENGINE_UI_GAUGE_H
#define ENGINE_UI_GAUGE_H

/* The game flags and the UI flags, ids, a new game, and numbers drawn into
 * windows. */

#include "types.h"

struct NumberSprite;

void func_020a45c0(void);
s32 getGameFlag(s32 flag);
void clearGameFlag(s32 flag);
void setGameFlag(s32 flag);
s32 func_020a4670(void);
s32 func_020a4694();
void func_020a472c();
s32 getUiFlag(s32 flag);
void clearUiFlag(s32 flag);
void setUiFlag(s32 flag);
s32 func_020a4c9c(void *number); /* a struct NumberSprite; callers pass bytes */
s32 func_020a4980();
void func_020a4ad4(struct NumberSprite *number, s16 x, s16 y);
u32 takeNextId(void);
void initNewGame(void);
void func_020a4bf4(struct NumberSprite *number, s16 x, s16 y, u8 index);
void func_020a4d18();

#endif /* ENGINE_UI_GAUGE_H */
