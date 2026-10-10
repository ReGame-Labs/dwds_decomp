#include "engine/bg/bg_load.h"
#include "engine/data.h"
#include "engine/system/system.h"

/* Does nothing. */
void func_02042f44(void) {}
/* Does nothing. */
void func_02042e78(void) {}

/* Frees a block of the main heap at the next frame, by a task of its own
 * (tickFreeLater). */
void freeLater(void *block) {
    struct FreeLaterTask *task;

    if (block == NULL) {
        return;
    }
    task             = createTask(&tickFreeLater, 0x101);
    task->task.onEnd = NULL;
    task->block      = block;
}

/* data_021e33c4. */
s8 func_02042f58(void) {
    return data_021e33c4;
}

/* data_021e33b8. */
s8 func_02042f48(void) {
    return data_021e33b8;
}

/* The same for the main screen (func_02042918). */
s32 func_02042aa8(void *unk0, s32 unk1, s32 unk2, s32 unk3) {
    return func_02042918(unk0, unk1, unk2, unk3, 0, 0, 0, 0, 0x20, 0x20, 0x20, 0x20);
}

/* Loads a background of the sub screen from the table of func_0204871c, with
 * func_020427c4's other arguments at their defaults. */
void func_02042a6c(void *unk0, s32 unk1, s32 unk2, s32 unk3) {
    func_020427c4(unk0, unk1, unk2, unk3, 0, 0, 0, 0, 0x20, 0x20, 0x20, 0x20);
}
