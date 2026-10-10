#include "engine/script/cmd_screen.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "engine/digimon/species_flags.h"
#include "engine/input/touch.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"
#include "engine/save/game_state.h"
#include "engine/script/cmd_core.h"
#include "engine/script/interpreter.h"
#include "engine/script/operand.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "engine/ui/digimon_list.h"
#include "engine/ui/gauge.h"
#include "farm/farm_groups.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_save_flash.h"
#include "field/actors/actor_tasks.h"
#include "field/map/map.h"
#include "field/map/map_character.h"
#include "field/map/ov000_021fbb2c.h"
#include "m2c_macros.h"

/* Fades both screens out, runs program index of data_02136684 and
 * data_02136694 and fades back in. */
void func_020892a0(void) {
    struct ProgramTask *task = (struct ProgramTask *) getCurrentTask();

    if (task->wait > 0) {
        task->wait--;
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
            task->wait = 32;
            task->state++;
            break;
        case 1:
            func_ov000_021fbdf8();
            func_020c28a4();
            task->state++;
            break;
        case 2:
            freeMainSprites();
            freeSubSprites();
            deleteMainActors();
            deleteSubActors();
            endSubActorTask();
            stopSubMapSpriteTask();
            stopSubMapTask();
            task->state++;
            break;
        case 3:
            data_02136684[task->index]();
            task->state = 300;
            break;
        case 300:
            if (data_02136694[task->index]()) {
                lockMainPalettes();
                lockSubPalettes();
                task->state = 10000;
            }
            break;
        case 10000:
            loadOverlay(2);
            loadOverlay(1);
            loadOverlay(4);
            task->state++;
            break;
        case 10001:
            func_020a3454(1);
            func_020a3454(2);
            restoreSubMap();
            if (getGameFlag(0x405) == 0) {
                fadeInMainPalette(0, 0x100, 0, 0, 4);
                fadeInMainPalette(0x900, 0x100, 0, 0, 4);
                fadeInMainPalette(0xA00, 0x800, 0, 0, 4);
                fadeInSubPalette(0, 0x100, 0, 0, 4);
                fadeInSubPalette(0x900, 0x100, 0, 0, 4);
                fadeInSubPalette(0xA00, 0x800, 0, 0, 4);
            } else {
                clearMainPalettes();
                clearSubPalettes();
            }
            task->wait = 32;
            task->state++;
            break;
        case 10002:
            func_ov000_021fbef8();
            setScriptGlobal(SCRIPT_GLOBAL(9), 1);
            endTask(task);
            break;
    }
}

/* Command 0x136: calls func_020a0764(1) and func_020b4b80. */
s32 func_02089280(struct ScriptThread *thread) {
    func_020a0764(1);
    func_020b4b80();
    return 1;
}

/* Command 0x137: goes on if the system was reset by cmdResetGame, else
 * jumps. */
s32 func_0208924c(struct ScriptThread *thread) {
    if (isSoftReset()) {
        thread->pc += 1;
    } else {
        thread->pc += *thread->pc;
    }
    return 1;
}

/* Command 0x13B: opens the name entry for the player's name (5 letters, into
 * PLAYER_NAME) and sets global variables 9 to 19 and 27 to 14. */
s32 cmdEnterPlayerName(struct ScriptThread *thread) {
    setNameEntry(0, 0, 5, &PLAYER_NAME);
    func_02083628();
    func_0208357c(8, 0);
    setScriptGlobal(SCRIPT_GLOBAL(9), 0x13);
    setScriptGlobal(SCRIPT_GLOBAL(27), 0xE);
    return 0;
}

/* Command 0x13C: the same for the name of the group of global variable 28 (5
 * letters). */
s32 func_02089188(struct ScriptThread *thread) {
    setNameEntry(2, 0, 5, getGroupInOrder(getScriptGlobal(SCRIPT_GLOBAL(28))) + 8);
    func_02083628();
    func_0208357c(8, 0);
    setScriptGlobal(SCRIPT_GLOBAL(9), 0x13);
    setScriptGlobal(SCRIPT_GLOBAL(27), 0xE);
    return 0;
}

/* Command 0x13D: the same for name entry kind 4 (8 letters, no buffer). */
s32 func_02089130(struct ScriptThread *thread) {
    setNameEntry(4, 0, 8, NULL);
    func_02083628();
    func_0208357c(8, 0);
    setScriptGlobal(SCRIPT_GLOBAL(9), 0x13);
    setScriptGlobal(SCRIPT_GLOBAL(27), 0xE);
    return 0;
}

/* Command 0x142: the same for the name of getNameEntryDigimon's Digimon (8
 * letters). */
s32 func_020890d0(struct ScriptThread *thread) {
    setNameEntry(1, 0, 8, ((struct Digimon *) getDigimon(getNameEntryDigimon()))->name);
    func_02083628();
    func_0208357c(8, 0);
    setScriptGlobal(SCRIPT_GLOBAL(9), 0x13);
    setScriptGlobal(SCRIPT_GLOBAL(27), 0xE);
    return 0;
}

/* Command 0x13E: starts func_0208365c's task. */
s32 func_0208909c(struct ScriptThread *thread) {
    struct StateTask *task = createTask(func_0208365c, 0x117);

    task->state = 0;
    task->wait  = 0;
    return 1;
}

/* The four commands below fade the palettes of one of the thread's slots
 * (mode 0-3, 9 does nothing) and put the thread to sleep until the fade's
 * task wakes it. */
/* Command 0x148: the sub screen, fading in. */
s32 func_02088e60(struct ScriptThread *thread) {
    s16 mode                     = readOperand(thread);
    s16 slot                     = readOperand(thread);
    struct PaletteFadeTask *task = createTask(func_02088b8c, 0x124);

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
    if (mode == 9) {
        task->state = 1300;
    }
    task->slot            = slot;
    task->unk6A           = thread->unk70[slot];
    task->paletteRow      = thread->paletteRow[slot];
    task->paletteRowCount = thread->paletteRowCount[slot];
    task->thread          = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x149: the main screen, fading in. */
s32 func_02088db4(struct ScriptThread *thread) {
    s16 mode                     = readOperand(thread);
    s16 slot                     = readOperand(thread);
    struct PaletteFadeTask *task = createTask(func_02088964, 0x124);

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
    if (mode == 9) {
        task->state = 1300;
    }
    task->slot            = slot;
    task->unk6A           = thread->unk70[slot];
    task->paletteRow      = thread->paletteRow[slot];
    task->paletteRowCount = thread->paletteRowCount[slot];
    task->thread          = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x148's task: fades the slot's palette rows of the sub screen in
 * (fadeInMainPalette) in the way its state (500-800) gives, waits for the fade and
 * wakes the thread; state 1300 only wakes it. */
void func_02088b8c(void) {
    struct PaletteFadeTask *task = (struct PaletteFadeTask *) getCurrentTask();

    if (task->wait != 0) {
        task->wait--;
        return;
    }
    switch (task->state) {
        case 500:
            task->fade  = fadeInMainPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0, 1, 1);
            task->state = 1200;
            break;
        case 600:
            task->fade  = fadeInMainPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 1, 1);
            task->state = 1200;
            break;
        case 700:
            task->fade  = fadeInMainPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 0, 1);
            task->state = 1200;
            break;
        case 800:
            task->fade  = fadeInMainPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 0, 8);
            task->state = 1200;
            break;
        case 1200:
            unlockMainPalettes();
            task->state++;
        case 1201:
            if (isMainPaletteEffectRunning(task->fade) != 1) {
                task->state = 10000;
            }
            break;
        case 1300:
            unlockMainPalettes();
            task->state = 10000;
            break;
        case 10000:
            wakeScriptThread(task->thread);
            endTask(task);
            break;
    }
}

/* Command 0x149's task: fades the slot's palette rows of the main screen in
 * (fadeInSubPalette) in the way its state (500-800) gives, waits for the fade and
 * wakes the thread; state 1300 only wakes it. */
void func_02088964(void) {
    struct PaletteFadeTask *task = (struct PaletteFadeTask *) getCurrentTask();

    if (task->wait != 0) {
        task->wait--;
        return;
    }
    switch (task->state) {
        case 500:
            task->fade  = fadeInSubPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0, 1, 1);
            task->state = 1200;
            break;
        case 600:
            task->fade  = fadeInSubPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 1, 1);
            task->state = 1200;
            break;
        case 700:
            task->fade  = fadeInSubPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 0, 1);
            task->state = 1200;
            break;
        case 800:
            task->fade  = fadeInSubPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 0, 8);
            task->state = 1200;
            break;
        case 1200:
            unlockSubPalettes();
            task->state++;
        case 1201:
            if (isSubPaletteEffectRunning(task->fade) != 1) {
                task->state = 10000;
            }
            break;
        case 1300:
            unlockSubPalettes();
            task->state = 10000;
            break;
        case 10000:
            wakeScriptThread(task->thread);
            endTask(task);
            break;
    }
}

/* Command 0x14A: the sub screen, fading out. */
s32 func_020888b8(struct ScriptThread *thread) {
    s16 mode                     = readOperand(thread);
    s16 slot                     = readOperand(thread);
    struct PaletteFadeTask *task = createTask(func_02088610, 0x124);

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
    if (mode == 9) {
        task->state = 1300;
    }
    task->slot            = slot;
    task->unk6A           = thread->unk70[slot];
    task->paletteRow      = thread->paletteRow[slot];
    task->paletteRowCount = thread->paletteRowCount[slot];
    task->thread          = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x14B: the main screen, fading out. */
s32 func_0208880c(struct ScriptThread *thread) {
    s16 mode                     = readOperand(thread);
    s16 slot                     = readOperand(thread);
    struct PaletteFadeTask *task = createTask(func_02088414, 0x124);

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
    if (mode == 9) {
        task->state = 1300;
    }
    task->slot            = slot;
    task->unk6A           = thread->unk70[slot];
    task->paletteRow      = thread->paletteRow[slot];
    task->paletteRowCount = thread->paletteRowCount[slot];
    task->thread          = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x14A's task: fades the slot's palette rows of the sub screen out
 * (fadeOutMainPalette) in the way its state (500-800) gives, waits for the fade and
 * wakes the thread; state 1300 only wakes it. */
void func_02088610(void) {
    struct PaletteFadeTask *task = (struct PaletteFadeTask *) getCurrentTask();

    if (task->wait != 0) {
        task->wait--;
        return;
    }
    switch (task->state) {
        case 500:
            task->fade  = fadeOutMainPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0, 1, 1);
            task->state = 1200;
            break;
        case 600:
            task->fade  = fadeOutMainPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 1, 1);
            task->state = 1200;
            break;
        case 700:
            task->fade  = fadeOutMainPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 0, 1);
            task->state = 1200;
            break;
        case 800:
            task->fade  = fadeOutMainPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 0, 8);
            task->state = 1200;
            break;
        case 1200:
            if (isMainPaletteEffectRunning(task->fade) != 1) {
                task->state = 10000;
            }
            break;
        case 1300:
            task->state = 10000;
            break;
        case 10000:
            func_0208577c((u8) task->slot, task->unk6A);
            wakeScriptThread(task->thread);
            endTask(task);
            break;
    }
}

/* Command 0x14B's task: fades the slot's palette rows of the main screen out
 * (fadeOutSubPalette) in the way its state (500-800) gives, waits for the fade and
 * wakes the thread; state 1300 only wakes it. */
void func_02088414(void) {
    struct PaletteFadeTask *task = (struct PaletteFadeTask *) getCurrentTask();

    if (task->wait != 0) {
        task->wait--;
        return;
    }
    switch (task->state) {
        case 500:
            task->fade  = fadeOutSubPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0, 1, 1);
            task->state = 1200;
            break;
        case 600:
            task->fade  = fadeOutSubPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 1, 1);
            task->state = 1200;
            break;
        case 700:
            task->fade  = fadeOutSubPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 0, 1);
            task->state = 1200;
            break;
        case 800:
            task->fade  = fadeOutSubPalette(task->paletteRow << 4, task->paletteRowCount << 4, 0x7FFF, 0, 8);
            task->state = 1200;
            break;
        case 1200:
            if (isSubPaletteEffectRunning(task->fade) != 1) {
                task->state = 10000;
            }
            break;
        case 1300:
            task->state = 10000;
            break;
        case 10000:
            func_02085710((u8) task->slot, task->unk6A);
            wakeScriptThread(task->thread);
            endTask(task);
            break;
    }
}

/* Command 0x14C: sets the scroll of one of the main screen's backgrounds. */
s32 cmdSetMainBgScroll(struct ScriptThread *thread) {
    s16 bg = readOperand(thread);
    s16 x  = readOperand(thread);
    s16 y  = readOperand(thread);

    setMainBgOffset(bg, x, y);
    return 1;
}

/* Command 0x14D: sets the scroll of one of the sub screen's backgrounds. */
s32 cmdSetSubBgScroll(struct ScriptThread *thread) {
    s16 bg = readOperand(thread);
    s16 x  = readOperand(thread);
    s16 y  = readOperand(thread);

    setSubBgOffset(bg, x, y);
    return 1;
}

/* Command 0x14E: scrolls one of the main screen's backgrounds by an offset. */
s32 cmdScrollMainBg(struct ScriptThread *thread) {
    s16 bg = readOperand(thread);
    s16 dx = readOperand(thread);
    s16 dy = readOperand(thread);
    s16 x;
    s16 y;

    getMainBgOffset(bg, &x, &y);
    setMainBgOffset(bg, (s16) (x + dx), (s16) (y + dy));
    return 1;
}

/* Command 0x14F: scrolls one of the sub screen's backgrounds by an offset. */
s32 cmdScrollSubBg(struct ScriptThread *thread) {
    s16 bg = readOperand(thread);
    s16 dx = readOperand(thread);
    s16 dy = readOperand(thread);
    s16 x;
    s16 y;

    getSubBgOffset(bg, &x, &y);
    setSubBgOffset(bg, (s16) (x + dx), (s16) (y + dy));
    return 1;
}

/* The four commands below start a palette fade of count colors from start,
 * stepping each color channel by step. Given a variable, they keep the fade's
 * handle in it and sleep for as long as the fade lasts. */
/* Command 0x150: fades the sub screen in. */
s32 cmdFadeSubScreenIn(struct ScriptThread *thread) {
    s16 start    = readOperand(thread);
    s16 count    = readOperand(thread);
    s16 color    = readOperand(thread);
    s16 interval = readOperand(thread);
    s16 step     = readOperand(thread);
    s16 var      = readOperand(thread);
    s16 fade     = fadeInMainPalette(start, count, color, interval, step);

    if (var != -1) {
        thread->vars[var] = fade;
        sleepScriptThread(thread->index, interval * 32 / step + 1);
    }
    return 0;
}

/* Command 0x151: fades the main screen in; unlike the other three, goes on to
 * the next command without a variable. */
s32 cmdFadeMainScreenIn(struct ScriptThread *thread) {
    s16 start    = readOperand(thread);
    s16 count    = readOperand(thread);
    s16 color    = readOperand(thread);
    s16 interval = readOperand(thread);
    s16 step     = readOperand(thread);
    s16 var      = readOperand(thread);
    s16 fade     = fadeInSubPalette(start, count, color, interval, step);

    if (var == -1) {
        return 1;
    }
    thread->vars[var] = fade;
    sleepScriptThread(thread->index, interval * 32 / step + 1);
    return 0;
}

/* Command 0x152: fades the sub screen out. */
s32 cmdFadeSubScreenOut(struct ScriptThread *thread) {
    s16 start    = readOperand(thread);
    s16 count    = readOperand(thread);
    s16 color    = readOperand(thread);
    s16 interval = readOperand(thread);
    s16 step     = readOperand(thread);
    s16 var      = readOperand(thread);
    s16 fade     = fadeOutMainPalette(start, count, color, interval, step);

    if (var != -1) {
        thread->vars[var] = fade;
        sleepScriptThread(thread->index, interval * 32 / step + 1);
    }
    return 0;
}

/* Command 0x153: fades the main screen out. */
s32 cmdFadeMainScreenOut(struct ScriptThread *thread) {
    s16 start    = readOperand(thread);
    s16 count    = readOperand(thread);
    s16 color    = readOperand(thread);
    s16 interval = readOperand(thread);
    s16 step     = readOperand(thread);
    s16 var      = readOperand(thread);
    s16 fade     = fadeOutSubPalette(start, count, color, interval, step);

    if (var != -1) {
        thread->vars[var] = fade;
        sleepScriptThread(thread->index, interval * 32 / step + 1);
    }
    return 0;
}

/* Command 0x155: goes on if one of the buttons given was pressed, or the
 * thread's sub screen sprite was touched; else jumps. */
s32 func_02087f5c(struct ScriptThread *thread) {
    u16 pressed = getPadPressed();

    if ((pressed & resolveOperand(thread, thread->pc[1])) ||
        (thread->subSprite != 0xFFFF && isSpriteTapped(thread->subSprite) == 1)) {
        thread->pc += 2;
    } else {
        thread->pc += *thread->pc;
    }
    return 1;
}

/* Command 0x156: calls func_020a04c0 with two operands and func_020a0f1c with
 * the first. */
s32 func_02087f20(struct ScriptThread *thread) {
    s16 id = readOperand(thread);

    func_020a04c0(id, readOperand(thread));
    func_020a0f1c(id);
    return 1;
}

/* Command 0x15E: calls func_020a0908 with getNameEntryDigimon's Digimon and the
 * operand. */
s32 func_02087f00(struct ScriptThread *thread) {
    s16 value = readOperand(thread);

    func_020a0908(getNameEntryDigimon(), value);
    return 1;
}

/* Command 0x15F: puts func_020a020c's value into a local variable. */
s32 func_02087ed4(struct ScriptThread *thread) {
    s16 var = readOperand(thread);

    thread->vars[var] = func_020a020c();
    return 1;
}

/* Command 0x157: goes on if at least count Digimon are of a type
 * (countDigimonAtStage), else jumps. */
s32 func_02087e74(struct ScriptThread *thread) {
    s16 type  = resolveOperand(thread, thread->pc[1]);
    s16 count = resolveOperand(thread, thread->pc[2]);

    if (count <= (s16) countDigimonAtStage(type)) {
        thread->pc += 3;
    } else {
        thread->pc += *thread->pc;
    }
    return 1;
}

/* Command 0x158: goes on if one of the party's members has the unk4 given, else
 * jumps. */
s32 func_02087e04(struct ScriptThread *thread) {
    s16 id = resolveOperand(thread, thread->pc[1]);
    s32 i;
    s32 member;
    s32 value;
    struct Digimon *digimon;

    for (i = 0; i < 10; i++) {
        member = func_020a2d98(i);
        if (member != 0) {
            digimon = getDigimon(member);
            value   = digimon->unk4;
            if (value == id) {
                thread->pc += 2;
                return 1;
            }
        }
    }
    thread->pc += *thread->pc;
    return 1;
}

/* Command 0x159: goes on if the screen is touched inside the rectangle given,
 * else jumps. */
s32 cmdJumpUnlessTouchedIn(struct ScriptThread *thread) {
    s16 left   = resolveOperand(thread, thread->pc[1]);
    s16 top    = resolveOperand(thread, thread->pc[2]);
    s16 width  = resolveOperand(thread, thread->pc[3]);
    s16 height = resolveOperand(thread, thread->pc[4]);
    s16 x      = getTouchX();
    s16 y      = getTouchY();

    if (getTouchTap() == 1 && x >= left && x < left + width && y >= top && y < top + height) {
        thread->pc += 5;
    } else {
        thread->pc += *thread->pc;
    }
    return 1;
}

/* Command 0x15A: sleeps until woken. */
s32 cmdSuspend(struct ScriptThread *thread) {
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x15B: wakes the thread that started this one. */
s32 cmdWakeParent(struct ScriptThread *thread) {
    if (thread->parent != 0xFF) {
        wakeScriptThread(thread->parent);
    }
    return 1;
}

/* Command 0x15C: runs program number - 100 of data_021366a4 and data_021366b8,
 * sleeping until it is done. */
s32 func_02087ca0(struct ScriptThread *thread) {
    s16 number               = readOperand(thread);
    struct ProgramTask *task = createTask(func_02087b74, 0x107);

    task->state  = 0;
    task->wait   = 0;
    task->index  = number - 100;
    task->thread = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x15C's task: pauses the scripts and starts the program; once the
 * program's update says it is done, loads the overlays 2, 1 and 4 again,
 * resumes the scripts and wakes the thread. A program without an update
 * keeps the task waiting. */
void func_02087b74(void) {
    struct ProgramTask *task = (struct ProgramTask *) getCurrentTask();

    if (task->wait != 0) {
        task->wait--;
        return;
    }
    switch (task->state) {
        case 0:
            pauseScripts();
            data_021366a4[task->index]();
            if (data_021366b8[task->index] == NULL) {
                task->state = 500;
            } else {
                task->state = 300;
            }
            break;
        case 300:
            if (data_021366b8[task->index]()) {
                task->state = 10000;
            }
            break;
        case 500:
            break;
        case 10000:
            loadOverlay(2);
            loadOverlay(1);
            loadOverlay(4);
            task->wait = 32;
            task->state++;
            break;
        case 10001:
            resumeScripts();
            wakeScriptThread(task->thread);
            endTask(task);
            break;
    }
}

/* Command 0x15D: resets the game (softReset) and ends the thread's
 * frame. */
s32 cmdResetGame(struct ScriptThread *thread) {
    softReset();
    return 0;
}

/* Command 0x16A: sets an event flag, skips an operand, sets data_021df5f8's
 * word at 0x43C to -244 and calls func_020a0278 with func_020a020c's value. */
s32 func_02087b14(struct ScriptThread *thread) {
    s16 flag = readOperand(thread);

    readOperand(thread);
    M2C_FIELD(&data_021df5f8, s32 *, 0x43C) = -244;
    setGameFlag(flag);
    func_020a0278(func_020a020c());
    return 1;
}

/* Command 0x16B: once func_020a020c is 59, clears data_021df5f8's word at 0x43C
 * and event flag 360. */
s32 func_02087adc(struct ScriptThread *thread) {
    if (func_020a020c() == 59) {
        M2C_FIELD(&data_021df5f8, s32 *, 0x43C) = 0;
        clearGameFlag(360);
    }
    return 1;
}
