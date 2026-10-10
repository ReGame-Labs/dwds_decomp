#include "engine/ui/captions.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/text/text_banks.h"
#include "engine/ui/buttons.h"

/* Closes a caption: frees its text and ends its task. */
void closeCaption(s32 id) {
    s32 slot;
    struct CaptionTask *task;

    slot = findCaption(id);
    if (slot == -1) {
        return;
    }
    task = findTask(id);
    func_0209d954(task->text);
    endTaskById(id);
    CAPTION_TASK_IDS[slot] = -1;
}

/* Whether a caption is closed. */
u8 isCaptionClosed(s32 id) {
    u8 closed;

    if (findCaption(id) == -1) {
        closed = TRUE;
    } else {
        closed = FALSE;
    }
    return closed;
}

/* Empties a list of count resources and ends it. */
void initResources(struct Resource *resource, u32 count) {
    u32 i;

    if (resource == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        resource->onFree = NULL;
        resource->data   = NULL;
        resource->id     = RESOURCE_FREE;
        resource->unkC   = 0;
        resource++;
    }
    resource->id     = RESOURCE_END;
    resource->onFree = NULL;
    resource->data   = NULL;
    resource->unkC   = 0;
}

/* Adds a resource to the first free entry of a list, with a block of the heap
 * of size bytes if it asks for one. FALSE if the list is full or the heap is. */
s32 addResource(struct Resource *resource, s32 id, struct Resource **added, void **data, s32 size, ResourceCallback onFree) {
    void *block;

    if (resource != NULL) {
        while (resource->id != RESOURCE_FREE) {
            if (resource->id == RESOURCE_END) {
                return FALSE;
            }
            resource++;
        }
        if (data != NULL && size != 0) {
            block = heapAlloc(size, 4);
            if (block == NULL) {
                return FALSE;
            }
            resource->data = block;
            *data          = resource->data;
        } else {
            resource->data = NULL;
        }
        resource->id     = id;
        resource->onFree = onFree;
        if (added != NULL) {
            *added = resource;
        }
    }
    return TRUE;
}

/* Frees every resource of a list: calls its onFree, then frees its block. */
s32 freeResources(struct Resource *resource) {
    ResourceCallback onFree;
    void *data;

    if (resource != NULL) {
        while (resource->id != RESOURCE_END) {
            if (resource->id != RESOURCE_FREE) {
                onFree = resource->onFree;
                if (onFree != NULL) {
                    onFree(resource, resource->data);
                    resource->onFree = NULL;
                }
                data = resource->data;
                if (data != NULL) {
                    heapFree(data);
                }
                resource->data = NULL;
                resource->id   = RESOURCE_FREE;
            }
            resource++;
        }
    }
    return TRUE;
}

/* Frees a resource: calls its onFree, then frees its block. */
void freeResource(struct Resource *resource) {
    ResourceCallback onFree;
    void *data;

    if (resource == NULL) {
        return;
    }
    onFree = resource->onFree;
    if (onFree != NULL) {
        onFree(resource, resource->data);
        resource->onFree = NULL;
    }
    data = resource->data;
    if (data != NULL) {
        heapFree(data);
    }
    resource->data = NULL;
    resource->id   = RESOURCE_FREE;
}
