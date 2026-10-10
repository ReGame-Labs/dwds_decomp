#ifndef NITRO_FS_H
#define NITRO_FS_H

#include "types.h"

/* The parts of NitroSDK's file system API that are inline functions. */

/* NitroSDK's file handle, 0x48 bytes: FS_InitFile (func_020d93bc) sets it up
 * and FS_OpenFile (func_020d906c) points prop.file at where the file lies in
 * its archive. */
struct FSFile {
    struct FSFile *prev;
    struct FSFile *next;
    struct FSArchive *arc;
    u32 stat; /* bit 0 while an asynchronous command runs */
    u32 command;
    s32 error;
    void *queue[2]; /* OSThreadQueue */
    union {
        struct {
            u32 own_id;
            u32 top;
            u32 bottom;
            u32 pos;
        } file;
    } prop;
    u8 arg[0x18];
};

static inline u32 FS_GetLength(struct FSFile *file) {
    return file->prop.file.bottom - file->prop.file.top;
}

#endif /* NITRO_FS_H */
