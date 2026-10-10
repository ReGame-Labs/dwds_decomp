#include "engine/text/font.h"
#include "engine/data.h"
#include "engine/window/window.h"

/* Loads a graphics file into a slot through func_020aa068, on the
 * background func_020aa340 set last (data_021e33bc). */
s32 func_020aa2c0(void *file, s32 slot, s32 tiles, s32 palette) {
    return func_020aa068(file, slot, tiles, palette, data_021e33bc);
}

/* The same through func_020a9f28, on the background func_020aa308 set last
 * (data_021e33c0). */
s32 func_020aa29c(void *file, s32 slot, s32 tiles, s32 palette) {
    return func_020a9f28(file, slot, tiles, palette, data_021e33c0);
}

/* Returns the last of the 24 graphics slots not in use, or -1. */
s32 func_020a99dc(void) {
    s8 i;

    for (i = 23; i >= 0; i--) {
        if (!(getGfxSlot(i)->flags & 1)) {
            break;
        }
    }
    return i;
}

/* Releases a graphics slot, the same as releaseGfxSlot. */
void func_020a9838(s32 index) {
    releaseGfxSlot(index);
}

/* Releases a graphics slot, the same as releaseGfxSlot. */
void func_020a982c(s32 index) {
    releaseGfxSlot(index);
}

/* Releases a graphics slot, the same as releaseGfxSlot. */
void func_020a9610(s32 index) {
    releaseGfxSlot(index);
}
