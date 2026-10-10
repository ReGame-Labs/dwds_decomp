#include "farm/farm_task.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "link/sjis.h"

/* The id of the group in the slot. */
s32 getGroupId(s32 slot) {
    return FARMS[slot].id;
}

/* Allocates a zeroed block from the main heap, counting the blocks and, in
 * the mode isFieldOverlayLoaded checks, keeping the most the heap has had in use. */
void *heapAllocZeroed(u32 size, s32 align) {
    void *block;

    block = heapAlloc(size, align);
    func_02030f18(block, 0, size);
    return block;
}

/* Frees a block of the main heap. */
void heapFreeBlock(void *block) {
    heapFree(block);
}

/* convertUnicodeToSjis, which converts Unicode text into Shift JIS. */
void func_020b2a04(char *dest, const u16 *src, u16 length) {
    convertUnicodeToSjis(dest, src, length);
}

/* Raises the flag func_020b2990 takes: a callback of func_020b5f0c. */
void func_020b29f0(void) {
    data_021e5c70 = 1;
}

/* Copies the data received into the buffer of setReceiveBuffer, if one is set,
 * and marks it received. The size handed in is ignored: the buffer's own size
 * is copied. */
void copyReceivedData(void *data, u32 size) {
    if (RECEIVE_BUFFER.dest == NULL) {
        return;
    }
    func_020e2454(data, RECEIVE_BUFFER.dest, RECEIVE_BUFFER.size);
    RECEIVE_BUFFER.received = 1;
}

/* Whether func_020b29f0 raised its flag since the last call, lowering it. */
BOOL func_020b2990(void) {
    if (data_021e5c70 == 1) {
        data_021e5c70 = 0;
        return TRUE;
    }
    return FALSE;
}

/* Whether data came into the buffer since the last call, clearing the mark. */
BOOL func_020b296c(void) {
    if (RECEIVE_BUFFER.received == 1) {
        RECEIVE_BUFFER.received = 0;
        return TRUE;
    }
    return FALSE;
}

/* Sets the buffer that copyReceivedData copies the data received into. */
void setReceiveBuffer(void *dest, u32 size) {
    RECEIVE_BUFFER.dest     = dest;
    RECEIVE_BUFFER.size     = size;
    RECEIVE_BUFFER.received = 0;
}

/* Frees the sub screen sprite *handle holds, if any. */
void freeSubSpriteHandle(u16 *handle) {
    if (*handle != 0xFFFF) {
        freeSubSprite(*handle);
    }
    *handle = 0xFFFF;
}
