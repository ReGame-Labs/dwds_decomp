#ifndef ENGINE_UI_CAPTIONS_H
#define ENGINE_UI_CAPTIONS_H

#include "engine/data.h"
#include "types.h"

/* The OAM's setup, the captions' slots and the lists of resources that the
 * field's characters keep. */

struct Resource;
typedef void (*ResourceCallback)(struct Resource *resource, void *data);

/* An entry of a list of resources: an id and, if it asked for one, a block
 * of the heap, freed with the entry after its onFree is called. */
struct Resource {
    /* 0x00 */ s32 id; /* RESOURCE_FREE, RESOURCE_END or the owner's */
    /* 0x04 */ ResourceCallback onFree;
    /* 0x08 */ void *data;
    /* 0x0C */ s32 unkC;
};

#define RESOURCE_FREE -1
#define RESOURCE_END 0

/* A caption's task, as far as its closing reads it. */
struct CaptionTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ s32 text; /* func_0209d954 frees it */
};

void freeResource(struct Resource *resource);
s32 findCaption(s32 id);
u8 isCaptionClosed(s32 id);
s32 freeResources(struct Resource *resource);
void initResources(struct Resource *resource, u32 count);
s32 addResource(struct Resource *resource, s32 id, struct Resource **added, void **data, s32 size, ResourceCallback onFree);
void closeCaption(s32 handle);
s32 func_0204514c();

#endif /* ENGINE_UI_CAPTIONS_H */
