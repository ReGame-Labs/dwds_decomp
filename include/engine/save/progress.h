#ifndef ENGINE_SAVE_PROGRESS_H
#define ENGINE_SAVE_PROGRESS_H

/* Save progress: the play time, the link battle records and the family
 * trees. */

#include "types.h"

struct Digimon;

void func_0209f9c4(s32 flag);
s32 func_0209fa00();
s32 func_0209fdf0();
void func_0209fe44(struct Digimon *digimon);
s16 addLinkLosses(s32 count);
s16 addLinkWins(s32 count);
s16 func_020a000c(void);
void setPlayTime(s32 hours, s32 minutes, s32 seconds);
void func_0209f980(s32 unk20);
s32 func_020a0130();
void *func_0209fc30(s32 id);
s32 func_0209fcb8();
s32 func_0209ff28(void);
s32 func_0209ff8c();
void func_020a001c();

#endif /* ENGINE_SAVE_PROGRESS_H */
