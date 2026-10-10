#ifndef ENGINE_BG_BG_LOAD_H
#define ENGINE_BG_BG_LOAD_H

#include "engine/data.h"
#include "types.h"

/* The task of freeLater: frees its block of the heap and ends. */
struct FreeLaterTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ void *block;
};

s32 func_02042d58();
void func_02042e78();
s32 func_02042ee0();
void func_02042f44();
s8 func_02042f48(void);
s8 func_02042f58(void);
void freeLater(void *block);
s32 tickFreeLater();
void func_020427c4();
s32 func_02042918();
void func_02042a6c(void *unk0, s32 unk1, s32 unk2, s32 unk3);
s32 func_02042aa8(void *unk0, s32 unk1, s32 unk2, s32 unk3);

#endif /* ENGINE_BG_BG_LOAD_H */
