#ifndef LINK_LINK_TRANSFER_H
#define LINK_LINK_TRANSFER_H

/* The transfer of data to the other DS of a local link, in packets of 64
 * bytes. */

#include "types.h"

#define LINK_CHUNK_SIZE 64

/* The transfer going on, LINK_TRANSFER. */
struct LinkTransfer {
    /* 0x00 */ s32 type; /* of the packets, 0 when no transfer is going */
    /* 0x04 */ u32 size;
    /* 0x08 */ s32 chunkSize; /* of the next packet */
    /* 0x0C */ s32 offset;    /* of the next packet in the data */
    /* 0x10 */ s32 chunkCount;
    /* 0x14 */ s32 chunk; /* the packets sent */
    /* 0x18 */ s32 data;  /* the address of the next packet's data */
};

BOOL isLinkTransferBusy(void);
s32 resetLinkTransfer(void);
BOOL startLinkTransfer(s32 data, u32 size, s32 type);

#endif /* LINK_LINK_TRANSFER_H */
