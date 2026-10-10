#ifndef NITRO_MI_H
#define NITRO_MI_H

#include "types.h"

/* The parts of NitroSDK's memory API that are inline functions: the fast
 * fill, a word at a time and eight words a store, is the internal
 * MIi_CpuClearFast (func_020e233c), which takes the value first. */

/* MIi_CpuClearFast, as main/libs.h declares it. */
s32 func_020e233c();

static inline void MI_CpuFillFast(void *dest, u32 data, u32 size) {
    func_020e233c(data, dest, size);
}

static inline void MI_CpuClearFast(void *dest, u32 size) {
    func_020e233c(0, dest, size);
}

#endif /* NITRO_MI_H */
