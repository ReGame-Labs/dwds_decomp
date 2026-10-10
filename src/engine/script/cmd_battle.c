#include "engine/script/cmd_battle.h"
#include "battle/battle_state.h"
#include "battle/link_party.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/save/game_state.h"
#include "engine/script/cmd_core.h"
#include "engine/script/interpreter.h"
#include "engine/script/operand.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "farm/farm_commands.h"
#include "farm/farm_groups.h"
#include "farm/farm_screen.h"
#include "farm/farms.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_save_flash.h"
#include "field/actors/actor_tasks.h"
#include "field/map/map.h"
#include "field/map/map_character.h"
#include "field/map/ov000_021fbb2c.h"
#include "link/exchange_programs.h"
#include "link/exchange_start.h"

/* Returns from the farm to the field: fades out, ends the map, its actors and
 * the sprites, starts startFarmTask with getFarmSlotAt's result, waits
 * for func_020b4b64, loads the map, script and farm overlays again and sets
 * global variable 9 to 1. */
void func_0208ce74(void) {
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
            deleteMainActors();
            deleteSubActors();
            endSubActorTask();
            stopSubMapSpriteTask();
            stopSubMapTask();
            task->state = task->state + 1;
            return;
        case 3:
            startFarmTask(getFarmSlotAt(0));
            task->state = task->state + 1;
            return;
        case 4:
            if (func_020b4b64() == 1) {
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
            setScriptGlobal(SCRIPT_GLOBAL(9), 1);
            endTask(task);
            return;
    }
}

/* Command 0xE2: sets global variable 9 to 19 and 27 to 3, and ends the
 * thread's frame. */
s32 func_0208ce40(struct ScriptThread *thread) {
    setScriptGlobal(SCRIPT_GLOBAL(9), 0x13);
    setScriptGlobal(SCRIPT_GLOBAL(27), 3);
    return 0;
}

/* Command 0x133: sets global variable 9 to 19 and 27 to 13. */
s32 func_0208ce0c(struct ScriptThread *thread) {
    setScriptGlobal(SCRIPT_GLOBAL(9), 0x13);
    setScriptGlobal(SCRIPT_GLOBAL(27), 0xD);
    return 0;
}

/* Command 0x134: clears global variables 21 and 22 and starts
 * func_020812a0's task. */
s32 func_0208cdbc(struct ScriptThread *thread) {
    struct StateTask *task;

    task = createTask(&func_020812a0, 0x117);
    setScriptGlobal(SCRIPT_GLOBAL(21), 0);
    setScriptGlobal(SCRIPT_GLOBAL(22), 0);
    task->state = 0;
    task->wait  = 0;
    return 1;
}

/* Leaves the field for startTradeExchange's program: pauses the scripts, fades
 * out, ends the map, its actors and the sprites, runs the program until
 * isExchangeEnded says it is done, then loads the overlays and the map again,
 * fades in, resumes the scripts and sets global variable 9 to 1. */
void func_0208ca98(void) {
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
            pauseScripts();
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
            task->state = 0x12C;
            return;
        case 0x12C:
            startTradeExchange();
            task->state = task->state + 1;
            return;
        case 0x12D:
            if (isExchangeEnded() != 0) {
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

/* Command 0x12C: starts func_0208ca98's task. */
s32 func_0208ca64(struct ScriptThread *thread) {
    struct StateTask *task;

    task        = createTask(&func_0208ca98, 0x103);
    task->state = 0;
    task->wait  = 0;
    return 1;
}

/* Command 0xFC: does nothing. */
s32 func_0208ca5c(struct ScriptThread *thread) {
    return 1;
}

/* Command 0xC9: sets global variable 9 to 19 and 27 to 1. */
s32 func_0208ca28(struct ScriptThread *thread) {
    setScriptGlobal(SCRIPT_GLOBAL(9), 0x13);
    setScriptGlobal(SCRIPT_GLOBAL(27), 1);
    return 0;
}

/* Command 0xE3: clears global variables 21 and 22, starts the battle
 * (func_020816e8's task) and calls func_ov005_02286198(0xF00). */
s32 cmdStartBattle(struct ScriptThread *thread) {
    struct StateTask *task;

    task = createTask(&func_020816e8, 0x117);
    setScriptGlobal(SCRIPT_GLOBAL(21), 0);
    setScriptGlobal(SCRIPT_GLOBAL(22), 0);
    task->state = 0;
    task->wait  = 0;
    func_ov005_02286198(0xF00);
    return 1;
}

/* Command 0x12B: sets global variable 9 to 19 and 27 to 4. */
s32 func_0208c99c(struct ScriptThread *thread) {
    setScriptGlobal(SCRIPT_GLOBAL(9), 0x13);
    setScriptGlobal(SCRIPT_GLOBAL(27), 4);
    return 0;
}

/* Command 0xE4: goes on if global variable 22 is 0, and jumps ahead
 * otherwise. */
s32 func_0208c960(struct ScriptThread *thread) {
    if (getScriptGlobal(SCRIPT_GLOBAL(22)) == 0) {
        thread->pc += 1;
    } else {
        thread->pc += *thread->pc;
    }
    return 1;
}

/* Command 0xE5: goes on if global variable 22 is 1, and jumps ahead
 * otherwise. */
s32 func_0208c924(struct ScriptThread *thread) {
    if (getScriptGlobal(SCRIPT_GLOBAL(22)) == 1) {
        thread->pc += 1;
    } else {
        thread->pc += *thread->pc;
    }
    return 1;
}

/* Command 0xE6: setBattleFlags with the operand. */
s32 func_0208c904(struct ScriptThread *thread) {
    setBattleFlags(readOperand(thread));
    return 1;
}

/* Command 0xE7: func_02080ec4 with the operand. */
s32 func_0208c8e4(struct ScriptThread *thread) {
    func_02080ec4(readOperand(thread));
    return 1;
}

/* Command 0xE8: func_02080ea4 with the operand. */
s32 func_0208c8c8(struct ScriptThread *thread) {
    func_02080ea4(readOperand(thread));
    return 1;
}

/* Command 0xE9: func_02080e64 with five operands. */
s32 func_0208c864(struct ScriptThread *thread) {
    s16 a;
    s16 b;
    s16 c;
    s16 d;

    a = readOperand(thread);
    b = readOperand(thread);
    c = readOperand(thread);
    d = readOperand(thread);
    func_02080e64(a, b, c, d, readOperand(thread));
    return 1;
}

/* Command 0xEA: calls func_020a03f0. */
s32 func_0208c84c(struct ScriptThread *thread) {
    func_020a03f0();
    return 1;
}

/* Command 0xEB: keeps the BGM playing (getBgm) in SCRIPT_SAVED_BGM. */
s32 cmdSaveBgm(struct ScriptThread *thread) {
    SCRIPT_SAVED_BGM = getBgm();
    return 1;
}

/* Command 0xEC: plays the BGM kept by command 0xEB again and sleeps for 8
 * frames. */
s32 cmdRestoreBgm(struct ScriptThread *thread) {
    playBgm(SCRIPT_SAVED_BGM);
    sleepScriptThread(thread->index, 8);
    return 0;
}
