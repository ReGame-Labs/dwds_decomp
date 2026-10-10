#include "engine/script/cmd_message.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"
#include "engine/script/cmd_core.h"
#include "engine/script/cmd_window.h"
#include "engine/script/interpreter.h"
#include "engine/script/message.h"
#include "engine/script/operand.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "farm/open_results.h"
#include "farm/results.h"
#include "field/actors/actor_save_flash.h"
#include "field/actors/actor_tasks.h"
#include "field/map/map.h"
#include "field/map/map_character.h"
#include "field/map/map_files.h"
#include "field/map/ov000_021fbb2c.h"

/* Command 0x111: calls func_ov000_02201524. */
s32 func_0208a744(struct ScriptThread *thread) {
    func_ov000_02201524();
    return 1;
}

/* Command 0x112: calls func_ov000_0220150c. */
s32 func_0208a72c(struct ScriptThread *thread) {
    func_ov000_0220150c();
    return 1;
}

/* Command 0x113: starts func_0208a3c0's task with global variable 10 and
 * ends the thread's frame. */
s32 func_0208a6ec(struct ScriptThread *thread) {
    struct FarmResultsTask *task;

    task        = createTask(&func_0208a3c0, 0x107);
    task->state = 0;
    task->wait  = 0;
    task->unk64 = getScriptGlobal(SCRIPT_GLOBAL(10));
    return 0;
}

/* Leaves the field for the farm results: fades both screens out, ends the
 * map, its actors and the sprites, pauses the scripts and shows the results
 * (func_ov005_0227d914 when unk64 is set, else openResults until
 * isResultsOpen says they are done); then loads the overlays 2, 1 and
 * 4 again, fades in, resumes the scripts and sets global variable 9 to 1. */
void func_0208a3c0(void) {
    s32 wait;
    struct FarmResultsTask *task;

    task = (struct FarmResultsTask *) getCurrentTask();
    wait = task->wait;
    if (wait > 0) {
        task->wait = wait - 1;
        return;
    }
    switch (task->state) {
        case 0:
            fadeOutMainPalette(0, 0x100, 0, 0, 4);
            fadeOutMainPalette(0x900, 0x100, 0, 0, 4);
            fadeOutMainPalette(0xA00, 0x800, 0, 0, 4);
            fadeOutSubPalette(0, 0x100, 0, 0, 4);
            fadeOutSubPalette(0x900, 0x100, 0, 0, 4);
            fadeOutSubPalette(0xA00, 0x800, 0, 0, 4);
            task->wait  = 0x20;
            task->state = task->state + 1;
            return;
        case 1:
            func_ov000_021fbdf8();
            func_020c28a4();
            task->state = task->state + 1;
            return;
        case 2:
            freeMainSprites();
            freeSubSprites();
            endSubActorTask();
            stopSubMapSpriteTask();
            stopSubMapTask();
            task->state = task->state + 1;
            return;
        case 3:
            pauseScripts();
            if (task->unk64 != 0) {
                func_ov005_0227d914();
                task->wait  = 8;
                task->state = 0x2710;
                return;
            }
            openResults();
            task->state = 0x1F4;
            return;
        case 0x1F4:
            if (isResultsOpen() == 0) {
                task->state = 0x2710;
            }
            return;
        case 0x2710:
            loadOverlay(2);
            loadOverlay(1);
            loadOverlay(4);
            task->state = task->state + 1;
            return;
        case 0x2711:
            restoreSubMap();
            fadeInMainPalette(0, 0x100, 0, 0, 4);
            fadeInMainPalette(0x900, 0x100, 0, 0, 4);
            fadeInMainPalette(0xA00, 0x800, 0, 0, 4);
            fadeInSubPalette(0, 0x100, 0, 0, 4);
            fadeInSubPalette(0x900, 0x100, 0, 0, 4);
            fadeInSubPalette(0xA00, 0x800, 0, 0, 4);
            task->wait  = 0x20;
            task->state = task->state + 1;
            return;
        case 0x2712:
            resumeScripts();
            func_ov000_021fbef8();
            setScriptGlobal(SCRIPT_GLOBAL(9), 1);
            endTask(task);
            return;
    }
}

/* Command 0xAC: prints a text (three operands, as func_0208ed28's task
 * takes them) in the sub message window and sleeps until it ends. */
s32 func_0208a31c(struct ScriptThread *thread) {
    struct MessageWindowTask *window;
    s16 text;
    s16 nameText;
    s16 unk2A;
    struct MessageTask *task;

    window         = findTask(data_021e33d8);
    text           = readOperand(thread);
    nameText       = readOperand(thread);
    unk2A          = readOperand(thread);
    task           = createTask(&func_0208ed28, 0x107);
    task->state    = 0;
    task->wait     = 0;
    task->flags    = 0;
    task->text     = text;
    task->nameText = nameText;
    task->unk2A    = unk2A;
    task->window   = window->window;
    task->unk30    = window->unk2E;
    task->unk64    = window->unk26;
    task->thread   = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0xAD: prints a text (three operands, as func_0208ebb4's task
 * takes them) in the main message window and sleeps until it ends. */
s32 func_0208a278(struct ScriptThread *thread) {
    struct MessageWindowTask *window;
    s16 text;
    s16 nameText;
    s16 unk2A;
    struct MessageTask *task;

    window         = findTask(data_021e33dc);
    text           = readOperand(thread);
    nameText       = readOperand(thread);
    unk2A          = readOperand(thread);
    task           = createTask(&func_0208ebb4, 0x107);
    task->state    = 0;
    task->wait     = 0;
    task->flags    = 0;
    task->text     = text;
    task->nameText = nameText;
    task->unk2A    = unk2A;
    task->window   = window->window;
    task->unk30    = window->unk2E;
    task->unk64    = window->unk26;
    task->thread   = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x11A: slides in the window of data_021d8cb0 (mode 0-3), if there is
 * one, and sleeps until it is in place. */
s32 func_02089fec(struct ScriptThread *thread) {
    s16 mode;
    struct WindowSlideTask *task;

    mode = readOperand(thread);
    if (data_021d8cb0 != -1) {
        task = createTask(func_02089f28, 0x107);
        if (mode == 0) {
            task->state = 500;
        }
        if (mode == 1) {
            task->state = 600;
        }
        if (mode == 2) {
            task->state = 700;
        }
        if (mode == 3) {
            task->state = 800;
        }
        task->thread = thread->index;
        suspendScriptThread(thread->index);
        unlockMainPalettes();
        markMainPalettesDirty();
        return 0;
    }
    return 1;
}

/* Command 0x11B: slides in the window of data_021d8c9c (mode 0-3), if there is
 * one, and sleeps until it is in place. */
s32 func_02089f48(struct ScriptThread *thread) {
    s16 mode;
    struct WindowSlideTask *task;

    mode = readOperand(thread);
    if (data_021d8c9c != -1) {
        task = createTask(func_02089f08, 0x107);
        if (mode == 0) {
            task->state = 500;
        }
        if (mode == 1) {
            task->state = 600;
        }
        if (mode == 2) {
            task->state = 700;
        }
        if (mode == 3) {
            task->state = 800;
        }
        task->thread = thread->index;
        suspendScriptThread(thread->index);
        unlockSubPalettes();
        markSubPalettesDirty();
        return 0;
    }
    return 1;
}
