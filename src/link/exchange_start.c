#include "link/exchange_start.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "link/exchange.h"

/* Copies the partner's row of data_021db718 to dest, if func_0206b020 finds
 * it. */
void func_0206afe4(struct WifiData *wifi, s32 unk1, s32 unk2, s32 friendData, void *dest) {
    s32 index;

    index = func_0206b020(wifi, unk1, unk2, friendData);
    if (index != -1) {
        func_020e2454(dest, data_021db718[index], sizeof(data_021db718[0]));
    }
}

/* Resets the exchange's globals. */
void resetExchangeGlobals(void) {
    EXCHANGE_TASK_ID = -1;
    EXCHANGE_ACTIVE  = 0;
}
