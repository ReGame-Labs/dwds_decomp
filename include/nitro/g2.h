#ifndef NITRO_G2_H
#define NITRO_G2_H

#include "engine/data.h"
#include "engine/libs.h"
#include "types.h"

/* The parts of NitroSDK's 2D graphics API that are inline functions, so that
 * their code is compiled into the game's. G2x_SetBlendAlpha_ is func_020db8cc. */

#define REG_BLDCNT (*(vu16 *) 0x04000050)
#define REG_DB_BLDCNT (*(vu16 *) 0x04001050)
#define REG_DB_BLDALPHA (*(vu16 *) 0x04001052)
#define REG_BG0OFS (*(vu32 *) 0x04000010)
#define REG_BG1OFS (*(vu32 *) 0x04000014)
#define REG_BG2OFS (*(vu32 *) 0x04000018)
#define REG_BG3OFS (*(vu32 *) 0x0400001C)
#define REG_DB_BG0OFS (*(vu32 *) 0x04001010)
#define REG_DB_BG1OFS (*(vu32 *) 0x04001014)
#define REG_DB_BG2OFS (*(vu32 *) 0x04001018)
#define REG_DB_BG3OFS (*(vu32 *) 0x0400101C)

/* Turns off the main screen's blending. */
static inline void G2_BlendNone(void) {
    REG_BLDCNT = 0;
}

/* Turns off the sub screen's blending. */
static inline void G2S_BlendNone(void) {
    REG_DB_BLDCNT = 0;
}

static inline void G2_SetBlendAlpha(s32 plane1, s32 plane2, s32 ev1, s32 ev2) {
    func_020db8cc(&REG_BLDCNT, plane1, plane2, ev1, ev2);
}

static inline void G2S_SetBlendAlpha(s32 plane1, s32 plane2, s32 ev1, s32 ev2) {
    func_020db8cc(&REG_DB_BLDCNT, plane1, plane2, ev1, ev2);
}

static inline void G2S_ChangeBlendAlpha(s32 ev1, s32 ev2) {
    REG_DB_BLDALPHA = (u16) (ev1 | (ev2 << 8));
}

#define GX_OAM_MODE_NORMAL 0
#define GX_OAM_EFFECT_NONE 0
#define GX_OAM_EFFECT_AFFINE 0x100
#define GX_OAM_EFFECT_AFFINE_DOUBLE 0x300
#define GX_OAM_EFFECT_FLIP_H 0x10000000
#define GX_OAM_EFFECT_FLIP_V 0x20000000
#define GX_OAM_EFFECT_FLIP_HV 0x30000000
#define GX_OAM_COLORMODE_256 1

/* Writes an OAM entry's first three attributes. effect and shape are already
 * in place, as the SDK's enums give them. The arms differ by a cast, so mwcc
 * keeps both even when a zero rsParam compiles them the same. */
static inline void G2_SetOBJAttr(union OamAttr *oam, s32 x, s32 y, s32 priority, s32 mode, BOOL mosaic, u32 effect, u32 shape,
                                 s32 color, s32 charName, s32 cParam, s32 rsParam) {
    if (effect == GX_OAM_EFFECT_AFFINE || effect == GX_OAM_EFFECT_AFFINE_DOUBLE) {
        oam->words[0] = (y & 0xFF) | (mode << 10) | (mosaic << 12) | (color << 13) | shape | ((x & 0x1FF) << 16) |
                        (rsParam << 25) | effect;
    } else {
        oam->words[0] =
            (u32) ((y & 0xFF) | (mode << 10) | (mosaic << 12) | (color << 13) | shape | ((x & 0x1FF) << 16) | effect);
    }
    oam->attr[2] = (s16) (charName | (priority << 10) | (cParam << 12));
}

#endif /* NITRO_G2_H */
