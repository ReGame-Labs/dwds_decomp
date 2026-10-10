#ifndef FARM_PANEL_DIGIMON_H
#define FARM_PANEL_DIGIMON_H

/* The digimon panels (FARM_PANEL_DIGIMON and FARM_PANEL_DIGIMON_B): a
 * digimon's actor and its view. */

#include "types.h"

struct ActorView;
struct Digimon;

void func_ov005_0227f688(void);
void func_ov005_0227fbb8(s32 owner, s16 scroll, s16 cursor, s8 palette, s8 unk33, u16 unk2C);
void func_ov005_0227fd00(void);
void func_ov005_0227fda8(struct Digimon *digimon);
void func_ov005_0227fdd8(struct Digimon *digimon);
void func_ov005_0227fe54(s32 digimon);
void func_ov005_0227fe6c(s32 digimon);
void func_ov005_0227fc64(void);
void func_ov005_0227fe08(s32 digimon);
void func_ov005_0227fe84(struct ActorView *view);

#endif /* FARM_PANEL_DIGIMON_H */
