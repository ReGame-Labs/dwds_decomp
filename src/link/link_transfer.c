#include "link/link_transfer.h"
#include "engine/data.h"

/* Ends any transfer: called once at boot. */
s32 resetLinkTransfer(void) {
    LINK_TRANSFER.type       = 0;
    LINK_TRANSFER.size       = 0;
    LINK_TRANSFER.chunkSize  = 0;
    LINK_TRANSFER.offset     = 0;
    LINK_TRANSFER.chunkCount = 0;
    LINK_TRANSFER.chunk      = 0;
    LINK_TRANSFER.data       = 0;
    return 0;
}

/* Starts sending size bytes of data to the other DS in packets of the given
 * type, 64 bytes at a time (tickLinkTransfer sends one a frame). FALSE while a
 * transfer is still going. The data is an s32 because the callers pass it as
 * one. */
BOOL startLinkTransfer(s32 data, u32 size, s32 type) {
    struct LinkTransfer *transfer = &LINK_TRANSFER;

    if (transfer->type != 0) {
        return FALSE;
    }
    transfer->type       = type;
    transfer->size       = size;
    transfer->offset     = 0;
    transfer->chunkCount = (size / LINK_CHUNK_SIZE) + ((size % LINK_CHUNK_SIZE) ? 1 : 0);
    transfer->chunk      = 0;
    transfer->chunkSize  = LINK_CHUNK_SIZE;
    if (transfer->chunkCount == 1) {
        transfer->chunkSize = size;
    }
    transfer->data = data;
    return TRUE;
}

/* Whether a transfer is going. */
BOOL isLinkTransferBusy(void) {
    if (LINK_TRANSFER.type != 0) {
        return TRUE;
    }
    return FALSE;
}
