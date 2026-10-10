#include "farm/farm_screen.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/save/game_state.h"
#include "engine/system/system.h"
#include "engine/text/text_banks.h"
#include "engine/text/window_text.h"
#include "engine/ui/dial.h"
#include "engine/ui/gauge.h"
#include "engine/window/message_box.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/farm_queries.h"
#include "farm/farms.h"
#include "farm/goods_panel.h"
#include "farm/open_pick_farm.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_tasks.h"
#include "field/map/map.h"
#include "field/map/ov000_021fbb2c.h"
#include "nitro/g2.h"

/* Closes the window of func_ov005_02289044. */
void func_ov005_02288e20(void) {
    closeWindowAndClear(&data_021e5c8c);
    freeTextBank();
}

/* The effect's value if its chance comes up, else 0. */
s16 rollFarmEffect(struct FarmEffect *effect) {
    if (getRandom(100) < effect->chance) {
        return effect->value;
    }
    return 0;
}

/* Gives the digimon what the goods of its farm do. */
void giveFarmGoodsEffects(s32 id, s32 digimon) {
    struct Farm *farm = getGroupById(id);
    s32 i;

    for (i = 0; i < FARM_SLOT_COUNT && farm->goods[i] != 0; i++) {
        func_ov005_022883e0(digimon, id, farm->goods[i]);
    }
}

/* Adds to the growth rates of the 8 types of digimon (see
 * func_ov005_02287df0) what the goods of getDigimonItem's entries of the farm
 * add: FARM_EFFECT_GROWTH_DRAGON to FARM_EFFECT_GROWTH_HOLY to one type each,
 * FARM_EFFECT_GROWTH_ALL to the 8. */
void func_ov005_022880e0(s32 *rates, struct Farm *farm) {
    s32 i;
    struct DigimonItem *entry;
    struct FarmGoodsData *data;
    struct FarmEffect *effect;

    for (i = 0; i < 8; i++) {
        entry = getDigimonItem(i);
        if (entry == NULL) {
            return;
        }
        if (entry->owner != farm->id) {
            continue;
        }
        data   = getFarmGoodsData(entry->item);
        effect = &data->effects[0];
        switch (effect->kind) {
            case FARM_EFFECT_GROWTH_DRAGON:
                func_ov005_02287dc8(0, effect->value, rates);
                break;
            case FARM_EFFECT_GROWTH_BEAST:
                func_ov005_02287dc8(1, effect->value, rates);
                break;
            case FARM_EFFECT_GROWTH_AQUAN:
                func_ov005_02287dc8(2, effect->value, rates);
                break;
            case FARM_EFFECT_GROWTH_BIRD:
                func_ov005_02287dc8(3, effect->value, rates);
                break;
            case FARM_EFFECT_GROWTH_INSECT:
                func_ov005_02287dc8(4, effect->value, rates);
                break;
            case FARM_EFFECT_GROWTH_MACHINE:
                func_ov005_02287dc8(5, effect->value, rates);
                break;
            case FARM_EFFECT_GROWTH_DARK:
                func_ov005_02287dc8(6, effect->value, rates);
                break;
            case FARM_EFFECT_GROWTH_HOLY:
                func_ov005_02287dc8(7, effect->value, rates);
                break;
            case FARM_EFFECT_GROWTH_ALL:
                func_ov005_02287dc8(0, effect->value, rates);
                func_ov005_02287dc8(1, effect->value, rates);
                func_ov005_02287dc8(2, effect->value, rates);
                func_ov005_02287dc8(3, effect->value, rates);
                func_ov005_02287dc8(4, effect->value, rates);
                func_ov005_02287dc8(5, effect->value, rates);
                func_ov005_02287dc8(6, effect->value, rates);
                func_ov005_02287dc8(7, effect->value, rates);
                break;
        }
    }
}

/* The food the farm's digimon eat in a day, FOOD_PER_STAGE's amount for
 * each one's stage, leaving out the ones with bit 2 or 4 of func_020a2c9c;
 * up to 99999. */
s32 getFarmFoodConsumed(s32 id) {
    struct Farm *farm;
    s32 i;
    s32 total;
    struct Digimon *digimon;

    farm  = getGroupById(id);
    total = 0;
    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        if (farm->digimon[i] != 0) {
            digimon = getDigimon(farm->digimon[i]);
            if (!(func_020a2c9c(digimon) & 0x14)) {
                total += FOOD_PER_STAGE[digimon->unk1E];
            }
        }
    }
    if (total > 99999) {
        total = 99999;
    }
    if (total < 0) {
        total = 0;
    }
    return total;
}

/* The food the digimon of all the farms eat in a day, up to 999999. */
s32 getFoodConsumed(void) {
    s32 i;
    s32 total;
    s32 id;

    for (i = 0, total = 0; i < FARM_COUNT; i++) {
        id = getFarmIdAt(i);
        if (id == 0) {
            break;
        }
        total += getFarmFoodConsumed(id);
    }
    if (total < 0) {
        total = 0;
    }
    if (total > 999999) {
        total = 999999;
    }
    return total;
}

/* The food the farm gathers in a day, within 0 and 999999. */
s32 getFarmFoodProduced(s32 id) {
    s32 food = rollFarmFoodProduced(id);

    if (food > 999999) {
        food = 999999;
    }
    if (food < 0) {
        food = 0;
    }
    return food;
}

/* The food all the farms gather in a day. */
s32 getFoodProduced(void) {
    s32 i;
    s32 total;
    s32 id;

    for (i = 0, total = 0; i < FARM_COUNT; i++) {
        id = getFarmIdAt(i);
        if (id == 0) {
            break;
        }
        total += getFarmFoodProduced(id);
    }
    return total;
}

/* Opens the screen of the farm, unless it is open. A farm day lasts 46080
 * frames, 12 minutes and 48 seconds. */
void openFarmScreen(s32 id) {
    struct FarmScreen *screen;

    if (FARM_SCREEN_TASK_ID != 0) {
        return;
    }
    func_020ac1f8();
    screen              = createTask(&tickFarmScreen, 0x110);
    screen->state       = 0;
    screen->wait        = 0;
    screen->farm        = id;
    FARM_SCREEN_TASK_ID = getTaskId(screen);
    FARM_DAY_LENGTH     = 46080;
}

/* Runs the farm day: every frame that flags 0x5E, 0x66, 0x62 and 0x409 are
 * clear, the save's count goes up; flag 0x5E (an event is due) is set at every
 * eighth of the day and flag 0x62 (the day is over, func_020b4e10) once it is
 * full. */
void tickFarmDayTimer(void) {
    struct FarmDayTimer *timer = (struct FarmDayTimer *) getCurrentTask();
    struct Window *window;
    s32 limit;
    u32 frames;

    switch (timer->state) {
        case 0:
            /* getGfxSlot returns the slot's address as an s32 */
            window            = getWindow(timer->window);
            timer->paletteRow = ((struct GfxSlot *) getGfxSlot(window->gfxSlot))->palette;
            func_020e22f4(getMainPaletteBase((s16) (timer->paletteRow * 16)), timer->full, sizeof(timer->full));
            func_020e22f4(getMainPaletteBase((s16) ((timer->paletteRow + 1) * 16)), timer->empty, sizeof(timer->empty));
            timer->state = 300;
        case 300:
            if (getGameFlag(0x5E) == 0 && getGameFlag(0x66) == 0 && getGameFlag(0x62) == 0 && getGameFlag(0x409) == 0) {
                limit  = FARM_DAY_LENGTH;
                frames = SAVE->groupTimer;
                if (frames < limit) {
                    SAVE->groupTimer = ++frames;
                    if (frames % (limit / 8) == 0) {
                        setGameFlag(0x5E);
                    }
                } else {
                    SAVE->groupTimer = limit;
                    func_020b4e10();
                }
            }
            func_ov005_022874f8(timer);
            break;
    }
}

/* Starts an event of the farm when flag 0x5E calls for one, unless the day is
 * over (flag 0x62), flag 0x66 is set or a screen fades. The kind of event
 * func_ov005_02287070 picks becomes a goods entry: farm goods at random, or
 * one of the events -0xFF to -0xF5, some by func_020a0854's level. */
void func_ov005_022872c0(struct FarmScreen *screen) {
    s32 digimon;
    s32 item;
    u8 level;

    getPadPressed();
    getPadHeld();
    if (getGameFlag(0x62) != 0) {
        return;
    }
    if (getGameFlag(0x66) != 0) {
        return;
    }
    if (isMainPaletteEffectRunning(-1) == 1) {
        return;
    }
    if (isSubPaletteEffectRunning(-1) == 1) {
        return;
    }
    if (getGameFlag(0x5E) == 0) {
        return;
    }
    level = func_020a0854();
    switch (func_ov005_02287070(screen->farm, &digimon)) {
        case -1:
            break;
        case 0:
            item          = pickFarmGoods(getGroupById(screen->farm));
            screen->unk36 = func_ov005_022871bc(screen->farm, item, digimon, getTaskId(screen));
            break;
        case 1:
            if (level > 2) {
                item = -0xFE;
            } else {
                item = -0xFF;
            }
            screen->unk36 = func_ov005_022871bc(screen->farm, item, digimon, getTaskId(screen));
            break;
        case 2:
            if (level > 2) {
                item = -0xFC;
            } else {
                item = -0xFD;
            }
            screen->unk36 = func_ov005_022871bc(screen->farm, item, digimon, getTaskId(screen));
            break;
        case 3:
            if (level > 3) {
                item = -0xF9;
            } else if (level > 1) {
                item = -0xFA;
            } else {
                item = -0xFB;
            }
            screen->unk36 = func_ov005_022871bc(screen->farm, item, digimon, getTaskId(screen));
            break;
        case 4:
            screen->unk36 = func_ov005_022871bc(screen->farm, -0xF7, digimon, getTaskId(screen));
            break;
        case 5:
            screen->unk36 = func_ov005_022871bc(screen->farm, -0xF6, digimon, getTaskId(screen));
            break;
        case 6:
            screen->unk36 = func_ov005_022871bc(screen->farm, -0xF5, digimon, getTaskId(screen));
            break;
    }
    clearGameFlag(0x3F3);
    clearGameFlag(0x5E);
    if (getGameFlag(0x5F) != 0) {
        setGameFlag(0x3F3);
        return;
    }
    clearGameFlag(0x3F3);
}

/* Goods of the farm, picked at random. */
s32 pickFarmGoods(struct Farm *farm) {
    s32 roll = getRandom((u16) (countFarmGoods(farm->id) * 100));

    return farm->goods[roll / 100];
}

/* Sets the screen up for its farm: the map, the view and the actors. */
void func_ov005_022867bc(struct FarmScreen *screen) {
    u16 x;
    u16 y;

    if (screen->farm == 0) {
        return;
    }
    startMainMap();
    startMainActorTask();
    getGroupById(screen->farm);
    screen->slot  = findFarmSlot(screen->farm);
    screen->unk2C = getFarmLayoutIndex((s16) screen->slot);
    x             = getRandom(32);
    y             = getRandom(32);
    func_ov005_02288d08(screen->slot, (s16) x * 8, (s16) y * 8);
    getMainMapView(NULL, NULL, &screen->unk2E, &screen->unk30);
    func_ov005_0228ab04(screen->slot);
    func_ov005_0228ae74(screen->slot);
}

/* Writes the farm's name in the screen's window. */
void drawFarmName(void) {
    struct FarmScreen *screen;
    struct Farm *farm;

    if (FARM_SCREEN_TASK_ID == 0) {
        return;
    }
    screen = findTask(FARM_SCREEN_TASK_ID);
    if (screen->farm == 0) {
        return;
    }
    farm = getGroupById(screen->farm);
    func_020a68cc(screen->window, 0x15, 0x15, 9, 2, farm->name, 0, 0xB, 3, 2, 0);
}

/* Fills the window's whole screen, 32 by 24 tiles, with its unk6 and redraws
 * it. */
void func_ov005_02286514(s32 index) {
    struct Window *window = getWindow(index);

    func_020a8b6c(index, 0, 0, 0x20, 0x18, window->unk6);
    redrawWindow(index);
}

/* Closes the farm's screen. */
void closeFarmScreen(void) {
    struct FarmScreen *screen;

    if (FARM_SCREEN_TASK_ID == 0) {
        return;
    }
    screen        = findTask(FARM_SCREEN_TASK_ID);
    screen->state = 600;
    screen->wait  = 0;
}

/* The farm screen's task. */
struct FarmScreen *getFarmScreen(void) {
    return findTask(FARM_SCREEN_TASK_ID);
}

/* Blends BG1 over the rest at 35%. */
void func_ov005_02286424(void) {
    func_ov005_022863c4(35);
}

/* Blends BG1 over the rest, percent of it showing. */
void func_ov005_022863c4(s32 percent) {
    G2_SetBlendAlpha(2, 0x3C, percent * 31 / 100, (100 - percent) * 31 / 100);
}

/* Moves the view to the next actor, or somewhere at random if there is none. */
void func_ov005_0228622c(struct FarmScreen *screen) {
    struct Actor *actor;

    if (screen->actorCount != 0) {
        if (screen->actorIndex >= screen->actorCount) {
            func_ov005_022862d4(screen);
        }
        screen->actor = screen->actors[screen->actorIndex];
        actor         = getMainActor(screen->actor);
        func_ov000_021fbb2c(actor->x - 0x80, actor->y - 0x60, 1);
        screen->actorIndex++;
        return;
    }
    func_ov000_021fbb2c(getRandom(999), getRandom(999), 1);
}

/* Whether the window of func_ov005_02284fd4 is open. */
s32 func_ov005_02285034(void) {
    if (data_ov005_022a1d1c != 0) {
        return 1;
    }
    return 0;
}

/* Opens a window with the digimon's name and icon for an event of its farm. */
void func_ov005_02284fd4(u16 actor, s32 digimon, s32 farm, s16 event) {
    struct DigimonNameWindow *window;

    window              = createTask(&func_ov005_0228478c, 0x112);
    data_ov005_022a1d1c = getTaskId(window);
    window->state       = 0;
    window->wait        = 0;
    window->farm        = farm;
    window->digimon     = digimon;
    window->unk2C       = event;
    window->actor       = actor;
    window->unk4A       = 0;
}
