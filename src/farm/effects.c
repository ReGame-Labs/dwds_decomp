#include "farm/effects.h"
#include "engine/data.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "farm/data.h"
#include "farm/farms.h"

/* Puts event's effect n on the digimon, giving what the stat was before and
 * after. */
void applyEventEffect(struct Digimon *digimon, s32 *after, s32 *before, u16 event, u16 n) {
    applyFarmEffect(digimon, after, before, &FARM_EVENTS[event].effects[n]);
}

/* Puts the effect of the goods with an id on the digimon, giving what the
 * stat was before and after. */
void applyGoodsEffect(struct Digimon *digimon, s32 *after, s32 *before, u32 id) {
    struct FarmGoodsData *item = func_ov005_02293c14(id);

    applyFarmEffect(digimon, after, before, &item->effects[0]);
}

/* The sprite of the goods' icon, 0xFFFF for none. */
u16 func_ov005_0228f924(void) {
    struct FarmTask *task = findTask(FARM_TASK_ID);

    if (task == NULL) {
        return 0xFFFF;
    }
    return task->icon;
}

/* Frees the goods' icon and the marks over the farm's digimon. */
void func_ov005_0228f8a8(void) {
    struct FarmTask *task = findTask(FARM_TASK_ID);
    s32 i;

    if (task == NULL) {
        return;
    }
    if (task->icon == 0xFFFF) {
        return;
    }
    freeSubSprite(task->icon);
    task->icon = 0xFFFF;
    freeSubSprite(task->unk3A);
    task->unk3A = 0xFFFF;
    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        if (task->marks[i] != 0xFFFF) {
            freeSubSprite(task->marks[i]);
            task->marks[i] = 0xFFFF;
        }
    }
}
