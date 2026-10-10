#include "farm/farms.h"
#include "engine/data.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "engine/digimon/species_flags.h"
#include "engine/libs.h"
#include "engine/save/game_state.h"
#include "engine/script/interpreter.h"
#include "engine/system/display_modes.h"
#include "engine/ui/gauge.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/farm_queries.h"
#include "farm/farm_screen.h"
#include "farm/farm_task.h"
#include "items/inventory.h"
#include "link/farm_visit.h"
#include "m2c_macros.h"

/* Makes a farm of a kind in the first free slot and puts it last in the
 * order. Returns the slot, or -1 when the four are in use. */
s32 createFarm(s8 kind) {
    s8 slot;
    struct Farm *farm;
    s32 place;

    getFarmKind(kind);
    for (slot = 0; slot < FARM_COUNT; slot++) {
        if (SAVE->groups[slot].id == 0) {
            break;
        }
    }
    if (slot == FARM_COUNT) {
        return -1;
    }
    farm = getGroup(slot);
    func_02030f18(farm, 0, sizeof(struct Farm));
    farm->id            = takeNextId();
    farm->unk4          = SAVE->unk1E0;
    farm->name[0]       = 0xFFFF;
    farm->kind          = kind;
    farm->capacityLevel = 1;
    farm->goodsLevel    = 1;
    farm->expLevel      = 1;
    farm->foodLevel     = 1;
    farm->layoutLevel   = 1;
    /* data_021df5f8 is the save block plus 0x4000, inside the goods; at 0x438
     * past it the save keeps the id of the farm made last, 0 after one is
     * deleted. */
    M2C_FIELD(&data_021df5f8, s32 *, 0x438) = farm->id;
    setAllDigimonFlags(0x10);
    for (place = 0;; place++) {
        if (SAVE->groupOrder[place] == -1) {
            break;
        }
    }
    FARM_ORDER[place] = slot;
    setScriptGlobal(0xFFFF8025, getFarmPlace(slot));
    return slot;
}

/* Deletes the farm in a slot: its digimon and its goods leave it, and the
 * later places of the order move up. */
s32 deleteFarm(s8 slot) {
    struct Farm *farm;
    s32 place;
    s32 i;
    s8 next;

    farm  = getGroup(slot);
    place = getFarmPlace(slot);
    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        if (farm->digimon[i] != 0) {
            removeFarmDigimon(farm->digimon[i]);
        }
    }
    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        if (farm->goods[i] != 0) {
            func_ov005_02286010(farm->goods[i]);
        }
    }
    FARM_ORDER[place] = -1;
    farm->id          = 0;
    for (; place < FARM_COUNT - 1; place++) {
        next                        = SAVE->groupOrder[place + 1];
        SAVE->groupOrder[place + 1] = SAVE->groupOrder[place];
        SAVE->groupOrder[place]     = next;
    }
    M2C_FIELD(&data_021df5f8, s32 *, 0x438) = 0;
    clearAllDigimonFlags(0x10);
    return 1;
}

/* The slot of the farm at a place in the order. */
s8 getFarmSlotAt(s8 place) {
    return FARM_ORDER[place];
}

/* The id of the farm at a place in the order, 0 for none. */
s32 getFarmIdAt(s8 place) {
    s8 slot;

    if (place < 0 || place >= 4) {
        return 0;
    }
    slot = getFarmSlotAt(place);
    if (slot == -1) {
        return 0;
    }
    return FARMS[slot].id;
}

/* The place of a slot in the order, or -1. */
s8 getFarmPlace(s8 slot) {
    s32 place;

    for (place = 0; place < FARM_COUNT; place++) {
        if (slot == SAVE->groupOrder[place]) {
            break;
        }
    }
    if (place == FARM_COUNT) {
        return -1;
    }
    return place;
}

/* The slot of the farm with an id, or -1. */
s8 findFarmSlot(s32 id) {
    s32 slot;
    struct Farm *farm;

    for (slot = 0; slot < FARM_COUNT; slot++) {
        farm = getGroup(slot);
        if (farm->id == id) {
            break;
        }
    }
    if (slot == FARM_COUNT) {
        return -1;
    }
    return slot;
}

/* The place in the order of the farm with an id. */
s8 getFarmPlaceById(s32 id) {
    return getFarmPlace(findFarmSlot(id));
}

/* raiseFarmLevel for the farm at a place in the order: the farm upgrade
 * shop raises a level with it. */
s32 raiseFarmLevelAt(s8 place, u32 level) {
    return raiseFarmLevel(getFarmSlotAt(place), level);
}

/* Raises one of the five levels of the farm in a slot when its kind has a
 * next one. Returns whether it did. */
s32 raiseFarmLevel(s32 slot, u32 level) {
    struct Farm *farm;
    struct FarmKind *kind;
    s32 raised;
    s8 current;

    farm   = getGroup(slot);
    raised = 0;
    if (farm->id == 0) {
        return 0;
    }
    kind = getFarmKind(farm->kind);
    switch (level) {
        default:
            break;
        case FARM_LEVEL_CAPACITY:
            current = farm->capacityLevel;
            if (current < FARM_LEVEL_COUNT && kind->capacity[current] != -1) {
                farm->capacityLevel = current + 1;
                raised              = 1;
            }
            break;
        case FARM_LEVEL_GOODS:
            current = farm->goodsLevel;
            if (current < FARM_LEVEL_COUNT && kind->goodsCapacity[current] != -1) {
                farm->goodsLevel = current + 1;
                raised           = 1;
            }
            break;
        case FARM_LEVEL_EXP:
            current = farm->expLevel;
            if (current < FARM_LEVEL_COUNT && kind->exp[current] != -1) {
                farm->expLevel = current + 1;
                raised         = 1;
            }
            break;
        case FARM_LEVEL_FOOD:
            current = farm->foodLevel;
            if (current < FARM_LEVEL_COUNT && kind->food[current] != -1) {
                farm->foodLevel = current + 1;
                raised          = 1;
            }
            break;
        case FARM_LEVEL_LAYOUT:
            current = farm->layoutLevel;
            if (current < FARM_LEVEL_COUNT && kind->layouts[current] != -1) {
                farm->layoutLevel = current + 1;
                raised            = 1;
            }
            break;
    }
    return raised;
}

/* getFarmLevel for the farm at a place in the order. */
s8 getFarmLevelAt(s8 place, u32 level) {
    return getFarmLevel(getFarmSlotAt(place), level);
}

/* One of the five levels of the farm in a slot, 0 for a free slot. */
s8 getFarmLevel(s32 slot, u32 level) {
    struct Farm *farm;
    s8 value;

    farm  = getGroup(slot);
    value = 0;
    if (farm->id != 0) {
        getFarmKind(farm->kind);
        switch (level) {
            default:
                break;
            case FARM_LEVEL_CAPACITY:
                value = farm->capacityLevel;
                break;
            case FARM_LEVEL_GOODS:
                value = farm->goodsLevel;
                break;
            case FARM_LEVEL_EXP:
                value = farm->expLevel;
                break;
            case FARM_LEVEL_FOOD:
                value = farm->foodLevel;
                break;
            case FARM_LEVEL_LAYOUT:
                value = farm->layoutLevel;
                break;
        }
    }
    return value;
}

/* countFarmLevelValues for the farm at a place in the order. */
s32 countFarmLevelValuesAt(s8 place, u32 level) {
    return countFarmLevelValues(getFarmSlotAt(place), level);
}

/* How many values one of the five levels of the farm in a slot can take. */
s32 countFarmLevelValues(s32 slot, u32 level) {
    struct Farm *farm;
    struct FarmKind *kind;
    s32 count;

    farm  = getGroup(slot);
    count = 0;
    if (farm->id != 0) {
        kind = getFarmKind(farm->kind);
        switch (level) {
            case FARM_LEVEL_CAPACITY:
                for (count = 0; count < FARM_LEVEL_COUNT && kind->capacity[count] != -1; count++) {
                }
                break;
            case FARM_LEVEL_GOODS:
                for (count = 0; count < FARM_LEVEL_COUNT && kind->goodsCapacity[count] != -1; count++) {
                }
                break;
            case FARM_LEVEL_EXP:
                for (count = 0; count < FARM_LEVEL_COUNT && kind->exp[count] != -1; count++) {
                }
                break;
            case FARM_LEVEL_FOOD:
                for (count = 0; count < FARM_LEVEL_COUNT && kind->food[count] != -1; count++) {
                }
                break;
            case FARM_LEVEL_LAYOUT:
                for (count = 0; count < FARM_LEVEL_COUNT && kind->layouts[count] != -1; count++) {
                }
                break;
        }
    }
    return count;
}

/* addFarmDigimon for the farm with an id. */
s32 addFarmDigimonById(s32 farmId, s32 digimon) {
    return addFarmDigimon(findFarmSlot(farmId), digimon);
}

/* addFarmDigimon for the farm at a place in the order. */
s32 addFarmDigimonAt(s8 place, s32 digimon) {
    return addFarmDigimon(getFarmSlotAt(place), digimon);
}

/* Puts a digimon in the farm in a slot when there is room, after taking it
 * out of where getDigimonPlace says it is. Returns whether it did. */
s32 addFarmDigimon(s32 slot, s32 id) {
    struct Farm *farm;
    struct Digimon *digimon;
    s32 capacity;
    s32 i;
    s32 where;

    farm    = getGroup(slot);
    digimon = getDigimon(id);
    if (farm == NULL || farm->id == 0 || id == 0) {
        return 0;
    }
    /* getGroupId is defined with an s32 index, but the binary narrows the
     * slot to s8 as if its parameter were one. */
    capacity = func_020b4c80(getGroupId((s8) slot));
    for (i = 0; i < capacity; i++) {
        if (farm->digimon[i] == 0) {
            break;
        }
    }
    if (i == capacity) {
        return 0;
    }
    unequipWeapon(id);
    unequipArmor(id);
    unequipAccessory(id);
    where = getDigimonPlace(id);
    if (where != 0) {
        if (where == 1) {
            func_020a2e18(id);
        }
    } else {
        removeFarmDigimon(id);
    }
    farm->digimon[i] = id;
    if (func_020b4ab8(farm->id, id, 0x20) != 0) {
        farm->unk64 = id;
    }
    digimon->flags &= 0x400;
    setDigimonFlags(id, 2);
    func_020a09c0(id, 0);
    func_020a0908(id, 0);
    return 1;
}

/* Takes a digimon out of the farm it is in, moving the later ones up.
 * Returns whether it was in one. */
s32 removeFarmDigimon(s32 id) {
    s32 i;
    s32 slot;
    struct Farm *farm;
    s32 removed;
    s32 next;

    if (id == 0) {
        return 0;
    }
    removed = 0;
    for (slot = 0; slot < FARM_COUNT; slot++) {
        farm = getGroup(slot);
        if (farm->id != 0) {
            for (i = 0; i < FARM_SLOT_COUNT; i++) {
                if (id == farm->digimon[i]) {
                    break;
                }
            }
            if (i < FARM_SLOT_COUNT) {
                farm->digimon[i] = 0;
                removed          = 1;
                break;
            }
        }
    }
    /* Not found, this runs on the last farm with i past its digimon. */
    for (; i < FARM_SLOT_COUNT - 1; i++) {
        next                 = farm->digimon[i + 1];
        farm->digimon[i + 1] = farm->digimon[i];
        farm->digimon[i]     = next;
    }
    if (id == farm->unk64) {
        func_020b4a58(farm->id, 0x20);
        farm->unk64 = 0;
    }
    return removed;
}

/* Makes the goods with id -2 in a buffer of the caller's, at the first stage
 * of its kind: findFarmGoods finds them through TEMP_FARM_GOODS. */
s32 makeTempFarmGoods(s16 dataIndex, struct FarmGoods *buf) {
    struct FarmGoodsData *data;

    data            = getFarmGoodsData(dataIndex / 3 * 3);
    buf->id         = -2;
    buf->dataIndex  = dataIndex;
    buf->unk8       = 0;
    buf->unkC       = -1;
    buf->stage      = 1;
    buf->unkE       = 0;
    buf->countdown  = data->growTime;
    buf->flags      = 0;
    TEMP_FARM_GOODS = buf;
    return -2;
}

/* Gives the player new goods in the first free entry of the 50. Returns their
 * id, 0 when the 50 are in use. */
s32 createFarmGoods(s16 dataIndex) {
    struct FarmGoods *entry;
    struct FarmGoodsData *data;
    s32 i;

    data = getFarmGoodsData(dataIndex);
    for (i = 0; i < FARM_GOODS_COUNT; i++) {
        if (SAVE->items[i].id == 0) {
            break;
        }
    }
    if (i == FARM_GOODS_COUNT) {
        return 0;
    }
    entry            = &PLAYER_GOODS[i];
    entry->id        = takeNextId();
    entry->dataIndex = dataIndex;
    entry->unk8      = 0;
    entry->unkC      = -1;
    entry->stage     = 1;
    entry->unkE      = 0;
    entry->countdown = data->growTime;
    entry->flags     = 0;
    return entry->id;
}

/* Deletes the goods with an id, taking them off their farm and moving the
 * later ones up. Returns whether there were any. */
s32 deleteFarmGoods(s32 id) {
    s32 i;
    struct FarmGoods next;

    func_ov005_02286010(id);
    for (i = 0; i < FARM_GOODS_COUNT; i++) {
        if (id == SAVE->items[i].id) {
            break;
        }
    }
    if (i < FARM_GOODS_COUNT) {
        PLAYER_GOODS[i].id = 0;
        for (; i < FARM_GOODS_COUNT - 1; i++) {
            next               = SAVE->items[i + 1];
            SAVE->items[i + 1] = SAVE->items[i];
            SAVE->items[i]     = next;
        }
        return 1;
    }
    return 0;
}

/* How many goods the player has. */
s32 countPlayerGoods(void) {
    s32 i;

    for (i = 0; i < FARM_GOODS_COUNT; i++) {
        if (getFarmGoodsAt(i)->id == 0) {
            break;
        }
    }
    return i;
}

/* Counts the goods down to their next stage and moves them there when it is
 * time. Returns their stage, 0 for no goods. */
s8 growFarmGoods(s32 id) {
    struct FarmGoods *goods;

    goods = findFarmGoods(id);
    if (goods == NULL) {
        return 0;
    }
    goods->flags &= ~1;
    if (goods->stage < 3) {
        goods->countdown--;
        if (goods->countdown < 1) {
            goods->dataIndex++;
            goods->stage++;
            goods->flags |= 1;
            if (goods->stage >= 3) {
                goods->countdown = 0;
            } else {
                goods->countdown = getFarmGoodsData(goods->dataIndex)->growTime;
            }
        }
    }
    return goods->stage;
}

/* The goods with an id, or NULL. */
struct FarmGoods *findFarmGoods(s32 id) {
    s32 i;

    if (id == -2) {
        return TEMP_FARM_GOODS;
    }
    for (i = 0; i < FARM_GOODS_COUNT; i++) {
        if (id == SAVE->items[i].id) {
            break;
        }
    }
    if (i == FARM_GOODS_COUNT) {
        return NULL;
    }
    return getFarmGoodsAt(i);
}

/* The goods at an index of the save's 50, or NULL. */
struct FarmGoods *getFarmGoodsAt(s8 index) {
    if (index >= 0 && index < FARM_GOODS_COUNT) {
        return &PLAYER_GOODS[index];
    }
    return NULL;
}

/* The id of the goods at an index of the save's 50, 0 for none. */
s32 getFarmGoodsIdAt(s32 index) {
    if (index < 0 || index > FARM_GOODS_COUNT - 1) {
        return 0;
    }
    return PLAYER_GOODS[index].id;
}

/* The index of the goods with an id, or -1. */
s32 findFarmGoodsIndex(s32 id) {
    s32 i;

    for (i = 0; i < FARM_GOODS_COUNT; i++) {
        if (id == SAVE->items[i].id) {
            return i;
        }
    }
    return -1;
}

/* Where goods are in a farm's goods, or -1. */
s32 findGoodsInFarm(s32 farmId, s32 id) {
    struct Farm *farm = getGroupById(farmId);
    s32 i;

    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        if (id == farm->goods[i]) {
            break;
        }
    }
    if (i < FARM_SLOT_COUNT) {
        return i;
    }
    return -1;
}

/* The entry of FARM_GOODS_DATA of the goods with an id. The ids from -0xFF
 * to -0xF5 stand for the first stages of the farm's events, the kinds from
 * entry 0xF9 on. */
s16 getFarmGoodsDataById(u32 id) {
    struct FarmGoods *goods;

    if (id >= -0xFFU && id <= -0xF5U) {
        return (id + 0xFF) * 3 + 0xF9;
    }
    goods = findFarmGoods(id);
    if (goods == NULL) {
        return -1;
    }
    return goods->dataIndex;
}

/* An effect of the goods with an id. */
struct FarmEffect *getFarmGoodsEffect(u32 id, s32 index) {
    return &func_ov005_02293c14(id)->effects[index];
}

/* The id of the goods at an index of the goods of the farm in a slot. */
s32 getFarmGoodsIdBySlot(s32 slot, s8 index) {
    struct Farm *farm = getGroup(slot);

    return findFarmGoods(farm->goods[index])->id;
}

/* The id of the goods at an index of a farm's goods, 0 for none. */
s32 getFarmGoodsId(s32 farmId, s32 index) {
    struct Farm *farm;
    struct FarmGoods *goods;

    farm = getGroupById(farmId);
    if (farm == NULL) {
        return 0;
    }
    goods = findFarmGoods(farm->goods[index]);
    if (goods == NULL) {
        return 0;
    }
    return goods->id;
}

/* How many different icons the goods of a farm have, icon 0x1C1 left out.
 * Each one is looked for among as many entries as goods were seen before it,
 * not as many as were counted. */
s32 countFarmGoodsIcons(struct Farm *farm) {
    u16 seen[8];
    s32 i;
    s32 count;
    s32 j;
    struct FarmGoodsData *data;

    count = 0;
    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        if (farm->goods[i] == 0) {
            continue;
        }
        data = func_ov005_02293c14(farm->goods[i]);
        if (data->icon == 0x1C1) {
            continue;
        }
        for (j = 0; j < i; j++) {
            if (data->icon - 0x18F == seen[j]) {
                break;
            }
        }
        if (j == i) {
            seen[count] = data->icon - 0x18F;
            count++;
        }
    }
    return count;
}

/* An entry of FARM_GOODS_DATA. */
struct FarmGoodsData *getFarmGoodsData(u16 dataIndex) {
    return &FARM_GOODS_DATA[dataIndex];
}

/* The entry of FARM_GOODS_DATA of the goods with an id, the one of the
 * stage before if they have just grown. Goods the player doesn't have are
 * looked up with func_0209a560 (probably the goods of a visited farm). */
struct FarmGoodsData *func_ov005_02293c14(u32 id) {
    struct FarmGoods *goods;

    if (id >= -0xFFU && id <= -0xF5U) {
        return getFarmGoodsData((id + 0xFF) * 3 + 0xF9);
    }
    goods = findFarmGoods(id);
    if (goods == NULL) {
        goods = func_0209a560(id);
    }
    if (goods->flags & 1) {
        return getFarmGoodsData(goods->dataIndex - 1);
    }
    return getFarmGoodsData(goods->dataIndex);
}

/* The entry of FARM_GOODS_DATA of the goods func_0209a560 finds. */
struct FarmGoodsData *func_ov005_02293bf8(s32 id) {
    struct FarmGoods *goods = func_0209a560(id);

    return getFarmGoodsData(goods->dataIndex);
}

/* Clears the farm screens' globals when the overlay is loaded: no palette
 * effects, windows, touch buttons or tasks. */
void clearFarmScreenGlobals(void) {
    data_021e5c80       = -1;
    data_021e5c98       = -1;
    data_021e5ca4       = -1;
    data_021e5c8c       = 0xFF;
    data_021e5c90       = 0xFF;
    data_021e5c88       = 0xFF;
    data_021e5c94       = 0xFF;
    data_021e5cac       = 0;
    data_021e5cc0       = 0;
    data_021e5cb4       = 0;
    data_021e5cc4       = 0;
    data_021e5cb8       = 0;
    data_021e5cb0       = 0;
    FARM_SCREEN_TASK_ID = 0;
}
