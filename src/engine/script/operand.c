#include "engine/script/operand.h"
#include "battle/unit_panels.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/palette/palette_fade.h"
#include "engine/script/cmd_core.h"
#include "engine/script/interpreter.h"
#include "engine/script/message.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_save_flash.h"
#include "field/actors/actor_tasks.h"
#include "field/map/map.h"
#include "field/map/map_character.h"
#include "field/map/ov000_021fbb2c.h"
#include "menus/widgets/scroll_bar.h"

/* Command 0xF1: copies the position of getMainActor's actor into two local
 * variables. */
s32 func_0208c7a0(struct ScriptThread *thread) {
    s16 index;
    s16 varX;
    s16 varY;
    struct Actor *actor;

    index              = readOperand(thread);
    varX               = readOperand(thread);
    varY               = readOperand(thread);
    actor              = getMainActor(index);
    thread->vars[varX] = actor->x;
    thread->vars[varY] = actor->y;
    return 1;
}

/* Command 0xF2: the same with getSubActor's actor. */
s32 func_0208c748(struct ScriptThread *thread) {
    s16 index;
    s16 varX;
    s16 varY;
    struct Actor *actor;

    index              = readOperand(thread);
    varX               = readOperand(thread);
    varY               = readOperand(thread);
    actor              = getSubActor(index);
    thread->vars[varX] = actor->x;
    thread->vars[varY] = actor->y;
    return 1;
}

/* Command 0x100: copies unk1D of a Digimon record into a local variable. */
s32 func_0208c710(struct ScriptThread *thread) {
    s16 index;
    s16 var;

    index             = readOperand(thread);
    var               = readOperand(thread);
    thread->vars[var] = ((struct Digimon *) getDigimonAt(index))->unk1D;
    return 1;
}

/* Command 0x101: shows a message spoken by a Digimon, its name above it, in
 * the window of the message window task data_021e33d8, and sleeps until the
 * message ends. */
s32 func_0208c658(struct ScriptThread *thread) {
    s16 index;
    s16 text;
    struct Digimon *digimon;
    struct MessageWindowTask *messageWindow;
    struct MessageTask *task;

    task           = createTask(&func_0208ed28, 0x107);
    messageWindow  = findTask(data_021e33d8);
    index          = readOperand(thread);
    text           = readOperand(thread);
    digimon        = getDigimonAt(index);
    task->nameText = index + MESSAGE_ID_DIGIMON_NAME;
    task->unk2A    = func_020a31c4(digimon->unk4);
    task->state    = 0;
    task->wait     = 0;
    task->flags    = 0;
    task->text     = text;
    task->window   = messageWindow->window;
    task->unk30    = messageWindow->unk2E;
    task->unk64    = messageWindow->unk26;
    task->thread   = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x102: the same in the window of data_021e33dc. */
s32 func_0208c5a0(struct ScriptThread *thread) {
    s16 index;
    s16 text;
    struct Digimon *digimon;
    struct MessageWindowTask *messageWindow;
    struct MessageTask *task;

    task           = createTask(&func_0208ebb4, 0x107);
    messageWindow  = findTask(data_021e33dc);
    index          = readOperand(thread);
    text           = readOperand(thread);
    digimon        = getDigimonAt(index);
    task->nameText = index + MESSAGE_ID_DIGIMON_NAME;
    task->unk2A    = func_020a31c4(digimon->unk4);
    task->state    = 0;
    task->wait     = 0;
    task->flags    = 0;
    task->text     = text;
    task->window   = messageWindow->window;
    task->unk30    = messageWindow->unk2E;
    task->unk64    = messageWindow->unk26;
    task->thread   = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* The value of an operand: a local or global variable's for an operand in
 * their ranges (SCRIPT_*_VAR_*), else the operand itself. */
s16 resolveOperand(struct ScriptThread *thread, s16 value) {
    if (value <= SCRIPT_LOCAL_VAR_LAST) {
        value = thread->vars[value - SCRIPT_LOCAL_VAR_FIRST];
    } else if (value <= SCRIPT_GLOBAL_VAR_LAST) {
        value = SCRIPT_GLOBALS[value - SCRIPT_GLOBAL_VAR_FIRST];
    }
    return value;
}

/* Command 0xC8: reloads the field (func_0208c170) and ends the thread's frame. */
s32 func_0208c474(struct ScriptThread *thread) {
    struct StateTask *task;

    task        = createTask(&func_0208c170, 0x107);
    task->state = 0;
    task->wait  = 0;
    return 0;
}

/* Reloads the field: fades both screens out, ends the map, its actors and
 * the sprites, pauses the scripts, loads the map, script and farm overlays
 * again, starts the map, fades in, resumes the scripts and sets global 9. */
void func_0208c170(void) {
    s32 wait;
    struct StateTask *task;

    task = (struct StateTask *) getCurrentTask();
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
            openFieldMenu();
            task->state = 0x12C;
            return;
        case 0x12C:
            if (isFieldMenuOpen() == 0) {
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

/* Command 0x124: starts func_0207e6cc's task. */
s32 func_0208c0e4(struct ScriptThread *thread) {
    struct StateTask *task;

    task        = createTask(&func_0207e6cc, 0x117);
    task->state = 0;
    task->wait  = 0;
    return 1;
}
