#ifndef ENGINE_BG_BG_AFFINE_H
#define ENGINE_BG_BG_AFFINE_H

#include "types.h"

/* The affine (rotated and scaled) backgrounds: BG2 and BG3 of both screens,
 * and the start of the digivolution scene from the Digimon menu. */

#define REG_DISPCNT_ADDR 0x04000000
#define REG_BG2PA_ADDR 0x04000020
#define REG_BG3PA_ADDR 0x04000030
#define REG_DB_DISPCNT_ADDR 0x04001000
#define REG_DB_BG3PA_ADDR 0x04001030

#define BG_AFFINE_COUNT 2 /* BG2 and BG3 */
#define BG_AFFINE_TASK_PRIORITY 0x122

void endMenuDigivolveTask(void);
void setSubBg3Center(s32 x, s32 y);
void setMainBg3Center(s32 x, s32 y);
void scrollSubBg3(s32 x, s32 y);
void scrollMainBg3(s32 x, s32 y);
void *func_0204871c(s32 index);
void tickSubBgAffine(void);
void tickMainBgAffine(void);
void func_02048034(s32 species, s32 target);
void startMenuDigivolveTask(s32 species, s32 target);
void func_0204801c(s32 species, s32 target);
void startMenuDigivolve(s32 species, s32 target);
s32 isSubBg3Affine(void);
s32 isMainBg3Affine(void);
void rotateSubBg3(s32 divisor, s32 angle);
s32 isSubBg2Affine(void);
s32 isMainBg2Affine(void);
void rotateMainBg3(s32 angle);
void initBgAffine(void);
void flushSubBgAffine(void);
void flushMainBgAffine(void);

#endif /* ENGINE_BG_BG_AFFINE_H */
