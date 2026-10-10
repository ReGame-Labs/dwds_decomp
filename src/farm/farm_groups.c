#include "farm/farm_groups.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/text/text_banks.h"
#include "engine/ui/buttons.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "farm/data.h"
#include "farm/exit_question.h"
#include "farm/farm_commands.h"
#include "farm/farm_queries.h"
#include "farm/farms.h"

/* Deletes a friend from the roster and moves the later ones down.
 * func_020f0d60 deletes one and clears it (strongly inferred to be
 * DWC_DeleteBuddyFriendData). */
void deleteFriend(struct WifiData *wifi, s32 index) {
    u8 *entry = wifi->friends[index];

    func_020f0d60(entry);
    for (; index < 15; index++) {
        func_020e2454(wifi->friends[index + 1], entry, sizeof(wifi->friends[0]));
        entry += sizeof(wifi->friends[0]);
    }
    func_020f0d60(wifi->friends[15]);
}

/* Closes the window whose index *window holds, if any. */
void closeWindowAndClear(u8 *window) {
    if (*window == 0xFF) {
        return;
    }
    closeWindow(*window);
    *window = 0xFF;
}

/* A text of the farm's table FARM_TEXTS: "Switch Farms", "Exit DigiFarm?",
 * the Digimon list's tabs and menus. */
void *getFarmText(s32 index) {
    return func_0209d470(FARM_TEXTS, index);
}

/* Empties the save's groups, their order and their items. */
void clearGroups(void) {
    s32 i;

    for (i = 0; i < 50; i++) {
        SAVE->items[i].id = 0;
    }
    for (i = 0; i < 4; i++) {
        SAVE->groupOrder[i] = -1;
        SAVE->groups[i].id  = 0;
    }
}

/* Loads the event scripts' and the farm's overlays and starts
 * func_ov005_02292f48's task as the farm task of FARM_TASK_ID. */
void func_020b4f50(void) {
    struct Task02292f48 *task;

    loadOverlay(OVERLAY_MODE_SCRIPTS);
    loadOverlay(OVERLAY_MODE_FARM);
    task         = createTask(func_ov005_02292f48, 0x10F);
    FARM_TASK_ID = getTaskId(task);
    task->state  = 0;
    task->wait   = 0;
    task->unk2A  = 0;
    task->unk2C  = -1;
    task->unk22  = 0;
}

/* Frees the 8 items given to Digimon. */
void clearDigimonItems(void) {
    s32 i;
    struct DigimonItem *entry = data_021df9d0;

    for (i = 0; i < 8; i++) {
        entry->owner = 0;
        entry++;
    }
}

/* Always 1. */
s32 func_020b4e5c(void) {
    return 1;
}

/* The index-th item given to a Digimon, NULL if that entry is free. */
struct DigimonItem *getDigimonItem(s32 index) {
    struct DigimonItem *entry;

    if (index < 0 || index >= 8) {
        return NULL;
    }
    entry = &data_021df9d0[index];
    if (entry->owner == 0) {
        entry = NULL;
    }
    return entry;
}

/* Sets game flag 0x62, which func_020b4b80 clears. */
void func_020b4e10(void) {
    setGameFlag(0x62);
}

/* The group in the slot, NULL past the 4 slots. */
struct Farm *getGroup(s32 slot) {
    if (slot < 0 || slot >= 4) {
        return NULL;
    }
    return &FARMS[slot];
}

/* The group with the given id; -2 is the one TEMP_FARM points to.
 * It returns void * because getGroupName adds the name's offset to it in
 * bytes. */
void *getGroupById(s32 id) {
    s32 i;

    if (id == -2) {
        return (void *) TEMP_FARM;
    }
    for (i = 0; i < 4; i++) {
        if (id == SAVE->groups[i].id) {
            break;
        }
    }
    if (i == 4) {
        return NULL;
    }
    return &FARMS[i];
}

/* The group at a place in FARM_ORDER's order, if that place and its slot are
 * in use. It returns u8 * because func_02089188 adds the name's offset to it
 * in bytes. */
u8 *getGroupInOrder(s32 index) {
    s8 slot;
    struct Farm *group;

    slot = FARM_ORDER[index];
    if (slot == -1) {
        return NULL;
    }
    group = &FARMS[slot];
    if (group->id == 0) {
        group = NULL;
    }
    return (u8 *) group;
}

/* Looks key up in data_02127644's pairs, which must hold it, and fetches the
 * text of its value without using it. */
void func_020b4cb4(s32 key) {
    s32 i;
    s16 value;

    for (i = 0; TRUE; i++) {
        if (key == data_02127644[i][0]) {
            value = data_02127644[i][1];
            break;
        }
    }
    getFarmText(value);
}

/* The value for the group's capacityLevel in the s8 row at 0x10 of its kind's
 * getFarmKind entry. */
s8 func_020b4c80(s32 id) {
    struct Farm *group;
    s8 *kind;

    group = getGroupById(id);
    kind  = getFarmKindById(id);
    return (kind + 0x10)[group->capacityLevel - 1];
}

/* Clears game flags 0x5E, 0x62 and 0x44C-0x456, frees the items given to
 * Digimon and clears the save's group timer. */
void func_020b4b80(void) {
    s32 i;

    clearGameFlag(0x62);
    clearGameFlag(0x5E);
    for (i = 0; i < 3; i++) {
        clearGameFlag(i + 0x44C);
        clearGameFlag(i + 0x450);
        clearGameFlag(i + 0x454);
    }
    clearDigimonItems();
    SAVE->groupTimer = 0;
}

/* Whether no farm task (FARM_TASK_ID) runs. */
BOOL func_020b4b64(void) {
    if (FARM_TASK_ID == 0) {
        return TRUE;
    }
    return FALSE;
}

/* Sets flags on the Digimon with the id. */
void setDigimonFlags(s32 id, s32 flags) {
    struct Digimon *digimon = getDigimon(id);

    digimon->flags |= flags;
}

/* Clears flags on the Digimon with the id. */
void clearDigimonFlags(s32 id, s32 flags) {
    struct Digimon *digimon = getDigimon(id);

    digimon->flags &= ~flags;
}

/* Sets flags on every Digimon kept. */
void setAllDigimonFlags(s32 flags) {
    s32 i;
    struct Digimon *digimon;

    for (i = 0; i < 40; i++) {
        digimon = getDigimonAt(i);
        if (digimon->id != 0) {
            digimon->flags |= flags;
        }
    }
}

/* Clears flags on every Digimon kept. */
void clearAllDigimonFlags(s32 flags) {
    s32 i;
    struct Digimon *digimon;

    for (i = 0; i < 40; i++) {
        digimon = getDigimonAt(i);
        if (digimon->id != 0) {
            digimon->flags &= ~flags;
        }
    }
}

/* Starts func_020b3614's task on the group with the id. Its result is left in
 * data_021e5ca4. */
void func_020b48b4(s32 id, s16 unk50) {
    struct Task020b3614 *task;

    task          = createTask(func_020b3614, 0x10F);
    task->state   = 0;
    task->wait    = 0;
    task->unk50   = unk50;
    task->unk58   = 0;
    task->unk5A   = 0;
    task->unk5C   = 0;
    task->unk5E   = 0;
    task->slot    = findFarmSlot(id);
    data_021e5cb4 = getTaskId(task);
    data_021e5ca4 = -1;
}

/* The result of func_020b48b4's task, -1 until it has one. */
s16 func_020b48a4(void) {
    return data_021e5ca4;
}
