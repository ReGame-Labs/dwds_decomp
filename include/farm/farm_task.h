#ifndef FARM_FARM_TASK_H
#define FARM_FARM_TASK_H

/* The farm's task, tickFarmTask, and the game's small helpers before it in
 * the same object: the farms' group ids, zeroed blocks of the main heap,
 * the buffer the link's received data goes into, the Shift JIS names and
 * the sub screen sprite handles. The link code (link/wifi.c) calls the heap
 * and receive helpers. */

#include "types.h"

void setReceiveBuffer(void *dest, u32 size);
BOOL func_020b296c(void);
BOOL func_020b2990(void);
void copyReceivedData(void *data, u32 size);
void func_020b29f0(void);
void func_020b2a04(char *dest, const u16 *src, u16 length);
void heapFreeBlock(void *block);
void tickFarmTask(void);
void freeSubSpriteHandle(u16 *handle);
s32 getGroupId(s32 slot);
void *heapAllocZeroed(u32 size, s32 align);

#endif /* FARM_FARM_TASK_H */
