#ifndef LINK_EXCHANGE_DATA_H
#define LINK_EXCHANGE_DATA_H

/* The wireless exchange: what two DS send each other to visit each other's
 * farm, and the tasks that send it. */

#include "engine/data.h"
#include "types.h"

/* The order of the farms, which packExchangeData copies as a whole, a byte at a
 * time: slots of groups, -1 for none (struct SaveData's groupOrder). */
struct GroupOrder {
    /* 0x0 */ s8 slots[4];
};

/* What packExchangeData packs of the save for the other DS, 0x41AC bytes. The
 * other's copy is at data_021da40c during a visit. */
struct ExchangeData {
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ struct PlayerName playerName;
    /* 0x000E */ u8 unkE[2];
    /* 0x0010 */ struct Digimon digimon[40];
    /* 0x3C10 */ struct GroupOrder groupOrder;
    /* 0x3C14 */ struct Farm groups[4];
    /* 0x3DC4 */ struct FarmGoods items[50];
};

/* The task of an exchange (func_0209c438, func_0209c738). */
struct ExchangeTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
};

s16 func_0209c268(void);
u8 func_0209c418(void);
void func_0209c224(void);
void func_0209c38c(void);
void func_0209c438(void);
void func_0209c738(void);
void packExchangeData(struct ExchangeData *data);

#endif /* LINK_EXCHANGE_DATA_H */
