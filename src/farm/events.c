#include "farm/events.h"
#include "engine/system/system.h"
#include "farm/data.h"
#include "farm/effects.h"

/* Starts the event of FARM_EVENTS for the digimon in slot of the
 * farm. */
void startFarmEventTask(u16 slot, u16 event, s16 unk72, s32 unk8C) {
    struct FarmEventTask *task = createTask(tickFarmEventTask, 0x10F);

    task->state   = 0;
    task->wait    = 0;
    task->event   = event;
    task->unk72   = unk72;
    task->slot    = slot;
    task->unk8C   = unk8C;
    task->digimon = data_ov005_022a1d9c[task->slot];
}
