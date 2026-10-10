#include "link/exchange_data.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "link/farm_visit.h"

/* Returns whether no exchange task runs. */
u8 func_0209c418(void) {
    u8 done;

    if (data_021da414 == 0) {
        done = TRUE;
    } else {
        done = FALSE;
    }
    return done;
}

/* Ends the exchange task and frees the other DS's data. */
void func_0209c38c(void) {
    struct ExchangeTask *task;

    task = findTask(data_021da414);
    heapFree(data_021da40c);
    heapFree(data_021da410);
    endTask(task);
    data_021da414 = 0;
}

/* Packs the player's name, Digimon and farms for the other DS. The Digimon
 * sent get flag 0x20. */
void packExchangeData(struct ExchangeData *data) {
    s32 i;

    data->unk0 = 0;
    /* match depends on copying the name and the order of the farms through
     * their addresses cast to integers: copied as members, the two copies
     * come out with other registers. */
    *(struct PlayerName *) (s32) &data->playerName = PLAYER_NAME;
    func_02030f78(data->digimon, data_021db82c, sizeof(data->digimon));
    *(struct GroupOrder *) (s32) &data->groupOrder = *(struct GroupOrder *) (s32) FARM_ORDER;
    func_02030f78(data->groups, FARMS, sizeof(data->groups));
    func_02030f78(data->items, PLAYER_GOODS, sizeof(data->items));
    for (i = 0; i < 40; i++) {
        if (data->digimon[i].id != 0) {
            data->digimon[i].unk108 |= 0x20;
        }
    }
}

/* Counts a farm visit, up to 99. */
s16 func_0209c268(void) {
    data_021e0af8.visits++;
    if (data_021e0af8.visits > 99) {
        data_021e0af8.visits = 99;
    }
    return data_021e0af8.visits;
}

/* Starts the visit of the other DS's farm (func_0209b11c) and counts it. */
void func_0209c224(void) {
    struct FarmVisit *visit;

    visit         = createTask(func_0209b11c, 0x113);
    visit->state  = 0;
    visit->wait   = 0;
    data_021da408 = getTaskId(visit);
    func_0209c268();
}
