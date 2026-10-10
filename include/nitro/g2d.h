#ifndef NITRO_G2D_H
#define NITRO_G2D_H

#include "types.h"

/* NitroSystem's palette data, which NNS_G2dGetUnpackedPaletteData finds in an
 * NCLR file. */
struct NNSG2dPaletteData {
    u32 fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void *pRawData;
};

#endif /* NITRO_G2D_H */
