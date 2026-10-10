#include "engine/save/save_data.h"
#include "engine/bg/bg_load.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/save/card_backup.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Does nothing. */
void func_02062888(void) {}

/* Clears the Yes/No window's tiles (func_02042ee0). */
void func_02062ea4(void) {
    func_02042ee0(3, 0x10, 0x1A, 4);
}

/* Makes the Yes/No window's two buttons, the cursor on No. */
void createSaveChoiceButtons(struct SaveMenu *menu) {
    s32 i;

    *menu->choice = 1;
    menu->buttons = createButtonGroup(0x20, *menu->choice, func_02062c60);
    for (i = 0; i < 2; i++) {
        addRectButton(SAVE_CHOICE_RECTS[i * 4], SAVE_CHOICE_RECTS[i * 4 + 1], SAVE_CHOICE_RECTS[i * 4 + 2],
                      SAVE_CHOICE_RECTS[i * 4 + 3], 0, menu->buttons);
    }
}

/* Frees the backgrounds' files. */
void freeSaveMenuBgs(struct SaveMenu *menu) {
    freeBgGraphics(&menu->work->bgs[0]);
    freeBgGraphics(&menu->work->bgs[2]);
    freeBgGraphics(&menu->work->bgs[1]);
    freeBgGraphics(&menu->work->bgs[3]);
}

/* Clears both screens' backgrounds, sprites and blending. */
void clearSaveMenuScreens(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    G2_BlendNone();
    MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    G2S_BlendNone();
}

/* Loads the save menu's fonts. */
void func_02062b48(void) {
    func_020a9c40(0, 3, 1);
    func_020a9c40(2, 2, 0);
}

/* Frees the save menu's fonts. */
void func_02062b28(void) {
    func_020a98a8(0);
    func_020a98a8(2);
}

/* Starts the task that saves the game for a script. */
void startSaveTask(void) {
    struct SaveTask *task;

    func_020878d4();
    task             = createTask(&runSaveTask, 0x123);
    SAVE_TASK        = &task->task;
    task->task.onEnd = onSaveTaskEnd;
    task->state      = 0;
    SAVE_TASK_RESULT = 0;
}

/* The save task's onEnd. */
void onSaveTaskEnd(void) {
    getCurrentTask();
    SAVE_TASK = NULL;
    func_020878ec();
}

/* The save task's result: 2 saved, 3 failed, else whether it has ended. */
u8 getSaveTaskResult(void) {
    u8 ended;

    if (SAVE_TASK_RESULT == 1) {
        return 2;
    }
    if (SAVE_TASK_RESULT == -1) {
        return 3;
    }
    if (SAVE_TASK == NULL) {
        ended = TRUE;
    } else {
        ended = FALSE;
    }
    return ended;
}

/* Resets the save writer and gives a new game's save its header ("DSDIGI",
 * data_02135714). */
void resetSaveWriter(void) {
    /* The writer is cleared a word at a time. */
    s32 *words = (s32 *) &SAVE_WRITER;

    words[0] = 0;
    words[1] = 0;
    words[2] = 0;
    words[3] = 0;
    writeSaveSignature((s32) &data_021db5f8, &data_02135714);
    func_0207bec8();
}

/* Asks the save writer for request 1, and request 3 when func_0207b82c says so. */
void func_0206267c(void) {
    struct SaveWriter *writer = &SAVE_WRITER;

    writer->requests[1] = 1;
    if (func_0207b82c() != 0) {
        writer->requests[3] = 1;
    }
    func_0208786c();
    func_020878d4();
}

/* Asks the save writer for request 0. */
void func_02062654(void) {
    SAVE_WRITER.requests[0] = 1;
    func_0208786c();
    func_020878d4();
}

/* Asks the save writer for request 2. */
void func_0206262c(void) {
    SAVE_WRITER.requests[2] = 1;
    func_0208786c();
    func_020878d4();
}

/* Whether the save writer has nothing to do. */
BOOL isSaveWriterIdle(void) {
    struct SaveWriter *writer = &SAVE_WRITER;

    if (writer->state != 0 || writer->requests[0] != 0 || writer->requests[1] != 0 || writer->requests[2] != 0 ||
        writer->requests[3] != 0) {
        return FALSE;
    }
    return TRUE;
}
