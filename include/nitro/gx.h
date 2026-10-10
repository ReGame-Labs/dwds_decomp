#ifndef NITRO_GX_H
#define NITRO_GX_H

#include "types.h"

/* The parts of NitroSDK's graphics API that are inline functions. */

#define REG_POWCNT1 (*(vu16 *) 0x04000304)
#define REG_DISPCNT (*(vu32 *) 0x04000000)
#define REG_DB_DISPCNT (*(vu32 *) 0x04001000)
#define REG_BG0CNT (*(vu16 *) 0x04000008)
#define REG_BG1CNT (*(vu16 *) 0x0400000A)
#define REG_BG2CNT (*(vu16 *) 0x0400000C)
#define REG_BG3CNT (*(vu16 *) 0x0400000E)
#define REG_DB_BG0CNT (*(vu16 *) 0x04001008)
#define REG_DB_BG1CNT (*(vu16 *) 0x0400100A)
#define REG_DB_BG2CNT (*(vu16 *) 0x0400100C)
#define REG_DB_BG3CNT (*(vu16 *) 0x0400100E)

#define REG_DISPCNT_DISPLAY_MASK 0x1F00 /* which of BG 0 to 3 and OBJ show */
#define REG_DISPCNT_DISPLAY_SHIFT 8
#define REG_BGCNT_PRIORITY_MASK 0x3

/* GXTexFmt's values for 16 and 256 color characters. */
#define GX_TEXFMT_PLTT16 3
#define GX_TEXFMT_PLTT256 4

#define REG_POWCNT1_DSEL_MASK 0x8000
#define REG_POWCNT1_DSEL_SHIFT 15

#define REG_MASTER_BRIGHT (*(vu16 *) 0x0400006C)
#define REG_DB_MASTER_BRIGHT (*(vu16 *) 0x0400106C)

/* GXx_SetMasterBrightness_, as main/libs.h declares it. */
void func_020d9e60(vu16 *reg, s32 brightness);

/* Which screen shows the main engine's picture: the top one with MAIN_SUB. */
enum GXDispSelect {
    GX_DISP_SELECT_SUB_MAIN = 0,
    GX_DISP_SELECT_MAIN_SUB = 1
};

static inline enum GXDispSelect GX_GetDispSelect(void) {
    return (enum GXDispSelect)((REG_POWCNT1 & REG_POWCNT1_DSEL_MASK) >> REG_POWCNT1_DSEL_SHIFT);
}

/* The new bit comes first in the OR: the other order allocates the registers
 * differently. */
static inline void GX_SetDispSelect(enum GXDispSelect sel) {
    REG_POWCNT1 = (u16) ((sel << REG_POWCNT1_DSEL_SHIFT) | (REG_POWCNT1 & ~REG_POWCNT1_DSEL_MASK));
}

/* Keeps the BG's priority and mosaic. */
static inline void G2S_SetBG0Control(s32 screenSize, s32 colorMode, s32 screenBase, s32 charBase, s32 bgExtPltt) {
    REG_DB_BG0CNT = (u16) ((REG_DB_BG0CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                           (charBase << 2) | (bgExtPltt << 13));
}

/* The brightness of each screen, from -16 (black) to 16 (white). */
static inline void GX_SetMasterBrightness(s32 brightness) {
    func_020d9e60(&REG_MASTER_BRIGHT, brightness);
}

static inline void GXS_SetMasterBrightness(s32 brightness) {
    func_020d9e60(&REG_DB_MASTER_BRIGHT, brightness);
}

#endif /* NITRO_GX_H */
