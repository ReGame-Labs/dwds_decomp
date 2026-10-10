#include "farm/checks.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "engine/palette/palette_fade.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display_modes.h"
#include "engine/system/setup.h"
#include "engine/system/system.h"
#include "engine/text/text_banks.h"
#include "engine/ui/buttons.h"
#include "engine/window/message_box.h"
#include "engine/window/window.h"
#include "farm/data.h"
#include "farm/farms.h"
#include "farm/goods_panel.h"
#include "field/actors/actor_tasks.h"
#include "field/actors/actor_walk.h"
#include "field/map/map.h"
#include "menus/digiconvert/digiconvert_open.h"

/* Does nothing. */
void func_ov005_02291f08(void) {}

/* Frees the sprites of tickFarmTask's task id, and the pick of its digimon
 * unless keepPicked. */
void func_ov005_02291f0c(s32 id, s32 keepPicked) {
    struct FarmTask *task = findTask(id);
    s32 i;

    func_ov005_0228c798(&task->icon);
    func_ov005_0228c798(&task->unk3A);
    func_ov005_0228c798(&task->unk38);
    if (keepPicked == 0 && task->picked != -1) {
        resumeSubActorWander(FARM_DIGIMON_ACTORS[task->picked]);
        task->picked = -1;
    }
    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        if (task->marks[i] != 0xFFFF) {
            func_ov005_0228c798(&task->marks[i]);
        }
    }
}

/* Frees the actors of the farm's digimon and makes them again
 * (func_ov005_0228ad10). */
void func_ov005_02291ee0(void) {
    func_ov005_0228ac88();
    findFarmSlot(data_ov005_022a1d0c);
    func_ov005_0228ad10();
}

/* These checks give 1 when the digimon id can be used, or a negative reason
 * why not; the farm task (tickFarmTask) runs them for its menus. This one
 * fails with -6 when id is already in func_020a2d60's list of 10 ids and -7
 * when 6 of them are in use: probably the party, whose texts are "Already in
 * your party" and "Your party is full". The ones below fail with -5 when id is
 * the only one in the list. */
s32 func_ov005_02291e50(s32 id) {
    struct Digimon *digimon = getDigimon(id);
    u16 status;

    if (func_020a2d60(id) != -1) {
        return -6;
    }
    if (func_020a2c6c() >= 6) {
        return -7;
    }
    status = func_020a2c9c(digimon);
    if (status & 8) {
        return -1;
    }
    if (status & 2) {
        return -2;
    }
    if (status & 4) {
        return -3;
    }
    if (status & 0x10) {
        return -4;
    }
    return 1;
}

/* The same without the check for a full party. */
s32 func_ov005_02291dd4(s32 id) {
    struct Digimon *digimon = getDigimon(id);
    u16 status;

    if (func_020a2d60(id) != -1) {
        return -6;
    }
    status = func_020a2c9c(digimon);
    if (status & 8) {
        return -1;
    }
    if (status & 2) {
        return -2;
    }
    if (status & 4) {
        return -3;
    }
    if (status & 0x10) {
        return -4;
    }
    return 1;
}

/* Fails with -1 for status bit 8, -5 for the list's only digimon and -13 for
 * status bit 4. */
s32 func_ov005_02291d70(s32 id) {
    u16 status = func_020a2c9c(getDigimon(id));

    if (status & 8) {
        return -1;
    }
    if (func_020a2d60(id) != -1 && func_020a2c6c() == 1) {
        return -5;
    }
    if (status & 4) {
        return -13;
    }
    return 1;
}

/* Fails with -1 for status bit 8, -5 for the list's only digimon and -8 when
 * getDigimonPlace gives 2 for it. */
s32 func_ov005_02291d18(s32 id) {
    if (func_020a2c9c(getDigimon(id)) & 8) {
        return -1;
    }
    if (func_020a2d60(id) != -1 && func_020a2c6c() == 1) {
        return -5;
    }
    if (getDigimonPlace(id) == 2) {
        return -8;
    }
    return 1;
}

/* Fails with -9 for status bit 8 and -5 for the list's only digimon. */
s32 func_ov005_02291cd0(s32 id) {
    if (func_020a2c9c(getDigimon(id)) & 8) {
        return -9;
    }
    if (func_020a2d60(id) != -1 && func_020a2c6c() == 1) {
        return -5;
    }
    return 1;
}

/* Closes the screen of tickFarmTask's task, fading out, and gives it back
 * state 0. */
void func_ov005_02291a34(void) {
    struct Task02291a34 *task = (struct Task02291a34 *) getCurrentTask();
    struct FarmTask *parent   = findTask(FARM_TASK_ID);

    if (task->wait > 0) {
        task->wait--;
        return;
    }
    switch (task->state) {
        case 0:
            if (data_021e5c80 != -1) {
                stopSubPaletteEffects(data_021e5c80);
            }
            if (data_021e5c98 != -1) {
                stopSubPaletteEffects(data_021e5c98);
            }
            data_021e5c80 = -1;
            data_021e5c98 = -1;
            if (data_021e5cc0 != 0) {
                closeButtonGroup(data_021e5cc0);
            }
            if (data_021e5cac != 0) {
                closeButtonGroup(data_021e5cac);
            }
            data_021e5cc0 = 0;
            data_021e5cac = 0;
            freeTextBank();
            closeAllWindows();
            func_020a95c0();
            freeMainSprites();
            freeSubSprites();
            endMainActorTask();
            endSubActorTask();
            stopSubMapTask();
            func_ov005_02289a34();
            fadeOutMainPalette(0, 0x100, 0, 0, 4);
            fadeOutMainPalette(0x900, 0x100, 0, 0, 4);
            fadeOutMainPalette(0xA00, 0x300, 0, 0, 4);
            fadeOutSubPalette(0, 0x100, 0, 0, 4);
            fadeOutSubPalette(0x900, 0x100, 0, 0, 4);
            fadeOutSubPalette(0xA00, 0x300, 0, 0, 4);
            task->wait = 8;
            task->state++;
            break;
        case 1:
            func_020ac1f8();
            func_020ac1cc();
            task->state++;
            break;
        case 2:
            loadOverlay(3);
            func_02044654();
            task->state = 300;
            break;
        case 300:
            if (isDigiconvertClosed() == 0) {
                break;
            }
            loadOverlay(2);
            task->state = 10000;
            break;
        case 10000:
            endTask(task);
            parent->state = 0;
            data_021e5ca4 = 0;
            break;
    }
}
