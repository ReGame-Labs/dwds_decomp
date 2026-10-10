#include "engine/script/cmd_farm.h"
#include "engine/data.h"
#include "engine/script/cmd_battle.h"
#include "engine/script/cmd_core.h"
#include "engine/script/interpreter.h"
#include "engine/script/operand.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/text/text_banks.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "farm/data.h"
#include "farm/farm_screen.h"
#include "farm/farms.h"
#include "field/actors/actor_save_flash.h"

/* Command 0xBA: moves the thread's sprites by an offset. */
s32 func_0208d818(struct ScriptThread *thread) {
    s16 dx = readOperand(thread);
    s16 dy = readOperand(thread);
    struct Sprite *sprite;

    if (thread->mainSprite != 0xFFFF) {
        sprite = getMainSprite(thread->mainSprite);
        setMainSpritePos(thread->mainSprite, sprite->x + dx, sprite->y + dy);
    }
    if (thread->subSprite != 0xFFFF) {
        sprite = getSubSprite(thread->subSprite);
        setSubSpritePos(thread->subSprite, sprite->x + dx, sprite->y + dy);
    }
    return 1;
}

/* Command 0xBB: frees the thread's sprites. The sub screen's is freed by the
 * main sprite's index, as in the original. */
s32 func_0208d7c8(struct ScriptThread *thread) {
    if (thread->mainSprite != 0xFFFF) {
        freeMainSprite(thread->mainSprite);
        thread->mainSprite = 0xFFFF;
    }
    if (thread->subSprite != 0xFFFF) {
        freeSubSprite(thread->mainSprite);
        thread->subSprite = 0xFFFF;
    }
    return 1;
}

/* Command 0xBE: waits while the thread has a main sprite. Both tests read
 * mainSprite in the original; the second was probably meant for subSprite. */
s32 func_0208d628(struct ScriptThread *thread) {
    if (thread->mainSprite != 0xFFFF || thread->mainSprite != 0xFFFF) {
        thread->pc -= 1;
        return 0;
    }
    return 1;
}

/* Command 0xBF: lets go of the thread's sprites without freeing them. */
s32 func_0208d610(struct ScriptThread *thread) {
    thread->mainSprite = 0xFFFF;
    thread->subSprite  = 0xFFFF;
    return 1;
}

/* Commands 0xC1's and 0x106's task: opens func_020a85a0's choice with two
 * texts, then puts the choice into global variable 10 and wakes its
 * thread. */
void func_0208d3e0(void) {
    s16 choice;
    void *text;
    struct ChoiceTask *task;

    task = (struct ChoiceTask *) getCurrentTask();
    switch (task->state) {
        case 0:
            loadTextBank(task->bank);
            text = func_0209d6f8(task->text);
            func_020a85a0(task->kind, text, func_0209d6f8(task->text2));
            task->state = task->state + 1;
            return;
        case 1:
            choice = data_021e33d0;
            if (choice == 0) {
                return;
            }
            if ((s32) choice > 0) {
                choice -= 1;
            }
            setScriptGlobal(SCRIPT_GLOBAL(10), choice);
            wakeScriptThread(task->thread);
            freeTextBank();
            endTask(task);
            return;
    }
}

/* Command 0xD7: while event flag 0x66 is set, sets flag 0x61 and waits; then
 * calls closeFarmScreen and sleeps for 16 frames. */
s32 func_0208d258(struct ScriptThread *thread) {
    if (getGameFlag(0x66) != 0) {
        setGameFlag(0x61);
        thread->pc -= 1;
        return 0;
    }
    closeFarmScreen();
    sleepScriptThread(thread->index, 16);
    return 0;
}

/* Command 0xD8: does nothing. */
s32 func_0208d250(struct ScriptThread *thread) {
    return 1;
}

/* Command 0xD9: does nothing. */
s32 func_0208d248(struct ScriptThread *thread) {
    return 1;
}

/* Command 0x135: plays an animation on the first sprite of the farm screen's
 * window. */
s32 func_0208d20c(struct ScriptThread *thread) {
    s16 anim                  = readOperand(thread);
    struct FarmScreen *screen = getFarmScreen();

    if (screen == NULL) {
        return 1;
    }
    setMainSpriteAnim(((struct Window *) getWindow(screen->window))->sprites[0], anim, -1);
    return 1;
}

/* Command 0x141: createFarm with the operand as the kind. */
s32 func_0208d1e8(struct ScriptThread *thread) {
    createFarm((s8) readOperand(thread));
    return 1;
}

/* Command 0xDA: func_020c2d0c with the operand and 0x421. */
s32 func_0208d1c4(struct ScriptThread *thread) {
    func_020c2d0c(readOperand(thread), 0x421);
    return 1;
}

/* Command 0xDB: func_020c2c74 with the operand and 0x421, unless event flag
 * 1001 is set. */
s32 func_0208d18c(struct ScriptThread *thread) {
    s16 value = readOperand(thread);

    if (getGameFlag(1001) == 0) {
        func_020c2c74(value, 0x421);
    }
    return 1;
}

/* Command 0xDC: reads an operand, drops it and calls func_020c2bec. */
s32 func_0208d170(struct ScriptThread *thread) {
    readOperand(thread);
    func_020c2bec();
    return 1;
}

/* Command 0xDD: func_020c2b64 with the operand, unless event flag 1001 is
 * set. */
s32 func_0208d140(struct ScriptThread *thread) {
    s16 value = readOperand(thread);

    if (getGameFlag(1001) == 0) {
        func_020c2b64(value);
    }
    return 1;
}

/* Command 0xDE: func_020c2d0c with two operands. */
s32 func_0208d108(struct ScriptThread *thread) {
    s16 value;

    value = readOperand(thread);
    func_020c2d0c(value, (u16) readOperand(thread));
    return 1;
}

/* Command 0xE1: returns to the field (func_0208ce74) and ends the thread's
 * frame. */
s32 func_0208d084(struct ScriptThread *thread) {
    struct StateTask *task;

    task        = createTask(&func_0208ce74, 0x107);
    task->state = 0;
    task->wait  = 0;
    return 0;
}
