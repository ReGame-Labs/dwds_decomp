#ifndef NITRO_TP_H
#define NITRO_TP_H

#include "types.h"

/* TP_WaitRawResult and TP_RequestSamplingAsync, as main/libs.h declares
 * them. */
s32 func_020e7610();
s32 func_020e7668();

/* NitroSDK's touch panel sample: the point, whether the screen is touched and
 * which coordinates the panel could not read. */
struct TPData {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
};

#define TP_VALIDITY_VALID 0
#define TP_VALIDITY_INVALID_X 1
#define TP_VALIDITY_INVALID_Y 2
#define TP_VALIDITY_INVALID_XY 3

/* Asks the ARM7 for a sample and waits for it: TP_RequestSamplingAsync and
 * TP_WaitRawResult. Nonzero if the sampling failed. */
static inline u32 TP_RequestRawSampling(struct TPData *data) {
    func_020e7668();
    return func_020e7610(data);
}

#endif /* NITRO_TP_H */
