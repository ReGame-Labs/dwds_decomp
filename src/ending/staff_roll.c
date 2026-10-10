#include "ending/staff_roll.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/palette/palette_buffers.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/window/message_box.h"
#include "engine/window/window.h"

/* Starts the staff roll: its two picture tasks and its text task. */
void startStaffRoll(void) {
    startStaffRollPictures();
    startStaffRollText();
}

/* Returns whether the staff roll has ended: none of its tasks is left. */
s32 isStaffRollDone(void) {
    if (data_021f5c80 != 0 || data_021f5c7c != 0) {
        return FALSE;
    }
    return TRUE;
}

/* Starts the staff roll's two picture tasks, func_020c94e4 and func_020c9738,
 * the first of which ends the second. */
s32 startStaffRollPictures(void) {
    s32 id;
    struct StaffRollPictures *first;
    struct StaffRollPictures *second;

    first          = createTask(&func_020c94e4, 0x113);
    first->state   = 0;
    first->wait    = 0;
    second         = createTask(&func_020c9738, 0x113);
    second->state  = 0;
    second->wait   = 0;
    first->otherId = getTaskId(second);
    id             = getTaskId(first);
    data_021f5c80  = id;
    return id;
}

/* Asks the staff roll's picture task id to end. */
void func_020c9954(s32 id) {
    struct StaffRollPictures *pictures;

    pictures        = findTask(id);
    pictures->state = STAFF_ROLL_END;
}

/* Starts the staff roll's text task, func_020c8e7c, which shows
 * /dat/msg/staff.sdb. */
s32 startStaffRollText(void) {
    s32 id;
    struct StaffRoll *roll;

    roll          = createTask(&func_020c8e7c, 0x113);
    roll->state   = 0;
    roll->wait    = 0;
    id            = getTaskId(roll);
    data_021f5c7c = id;
    return id;
}

/* Returns whether the staff roll's text task is running. */
s32 isStaffRollTextRunning(void) {
    if (data_021f5c7c != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Ends the staff roll's text task: frees its window and what it took, and
 * the text. */
void endStaffRollText(void) {
    struct StaffRoll *roll;

    roll = findTask(data_021f5c7c);
    closeWindow(roll->window);
    stopSubPaletteEffectsButFades(roll->unk2C);
    func_02085710(3, roll->unk2A);
    func_020a9610(roll->unk28);
    func_020a9844(2);
    func_020a9844(0);
    func_020a9844(6);
    func_020a9844(1);
    freeTextBank();
    func_020ac1cc();
    endTask(roll);
    data_021f5c7c = 0;
}
