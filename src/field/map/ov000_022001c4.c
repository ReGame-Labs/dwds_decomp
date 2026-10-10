#include "field/map/ov000_022001c4.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "field/map/data.h"

/* Frees the main screen map's eight buffers of data_ov000_0220d930 and the
 * one of data_ov000_0220d908. */
void func_ov000_02200838(void) {
    s32 i;
    void *buffer;

    for (i = 0; i < 8; i++) {
        buffer = data_ov000_0220d930[i];
        if (buffer != NULL) {
            heapFree(buffer);
            data_ov000_0220d930[i] = NULL;
        }
    }
    buffer = data_ov000_0220d908;
    if (buffer != NULL) {
        heapFree(buffer);
        data_ov000_0220d908 = NULL;
    }
}

/* The same for the sub screen map's, data_ov000_0220d910 and
 * data_ov000_0220d90c. */
void func_ov000_022007a8(void) {
    s32 i;
    void *buffer;

    for (i = 0; i < 8; i++) {
        buffer = data_ov000_0220d910[i];
        if (buffer != NULL) {
            heapFree(buffer);
            data_ov000_0220d910[i] = NULL;
        }
    }
    buffer = data_ov000_0220d90c;
    if (buffer != NULL) {
        heapFree(buffer);
        data_ov000_0220d90c = NULL;
    }
}
