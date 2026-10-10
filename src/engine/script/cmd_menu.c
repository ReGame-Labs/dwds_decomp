#include "engine/script/cmd_menu.h"
#include "engine/data.h"
#include "engine/script/cmd_core.h"
#include "engine/script/interpreter.h"
#include "engine/system/system.h"
#include "engine/ui/digimon_list.h"
#include "engine/ui/gauge.h"
#include "engine/window/message_box.h"

/* The task command 0x10E starts: asks a question with two answers
 * (openFarmMessage), puts 0 in global variable 26 for the first and 1 for the
 * second or a cancel (9999), then wakes its thread. */
void func_0208ae40(void) {
    s32 answer;
    s32 flags;
    struct QuestionTask *task;

    task = (struct QuestionTask *) getCurrentTask();
    switch (task->state) {
        case 0:
            if (task->unk68 == 0) {
                flags = 0;
            } else {
                flags = 2;
            }
            openFarmMessage(task->text, task->unk66, -1, 0xC, 4, flags);
            task->state = 0x12C;
            return;
        case 0x12C:
            answer = func_020ac6b8();
            switch (answer) {
                case -1:
                    return;
                case 0:
                    setScriptGlobal(SCRIPT_GLOBAL(26), 0);
                    task->state = 0x2710;
                    return;
                case 9999:
                case 1:
                    setScriptGlobal(SCRIPT_GLOBAL(26), 1);
                    task->state = 0x2710;
                    return;
            }
            break;
        case 0x2710:
            wakeScriptThread(task->thread);
            endTask(task);
            return;
    }
}

/* Command 0x10F: calls func_020ac6f8. */
s32 func_0208ae28(struct ScriptThread *thread) {
    func_020ac6f8();
    return 1;
}

/* Command 0x110: opens the list menu (func_0208a948) and sleeps until it
 * wakes the thread. */
s32 func_0208ade0(struct ScriptThread *thread) {
    struct ListMenuTask *task;

    task         = createTask(&func_0208a948, 0x107);
    task->state  = 0;
    task->thread = thread->index;
    suspendScriptThread(thread->index);
    setUiFlag(6);
    return 0;
}

/* Fills the list menu with the entries 0-16 whose event flag (0x20C on) is
 * set; entry 16 also needs one of the flags 0x27F, 0x286 and 0x204. */
void func_0208a8b0(struct ListMenuTask *task) {
    s32 i;
    s32 count;

    count = 0;
    for (i = 0; i < LIST_MENU_ENTRY_COUNT; i++) {
        if ((i != 16 || getGameFlag(0x27F) || getGameFlag(0x286) || getGameFlag(0x204)) && getGameFlag(i + 0x20C)) {
            task->entries[count++] = i;
        }
    }
    task->unk66 = 0;
    task->count = count;
}
