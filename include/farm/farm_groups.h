#ifndef FARM_FARM_GROUPS_H
#define FARM_FARM_GROUPS_H

#include "types.h"

struct DigimonItem;
struct Farm;
struct WifiData;

s16 func_020b48a4(void);
void clearAllDigimonFlags(s32 flags);
void func_020b4a58(s32 id, s32 flags);
void setAllDigimonFlags(s32 flags);
BOOL func_020b4b64(void);
void func_020b4b80(void);
struct Farm *getGroup(s32 slot);
void func_020b4e10(void);
s32 func_020b4e5c(void);
void *getFarmText(s32 index);
void closeWindowAndClear(u8 *window);
void func_020b48b4(s32 id, s16 unk50);
s32 func_020b4cf8();
void func_020b4f50(void);
void clearDigimonFlags(s32 id, s32 flags);
void setDigimonFlags(s32 id, s32 flags);
struct DigimonItem *getDigimonItem(s32 index);
s8 func_020b4c80(s32 id);
void func_020b4cb4(s32 key);
void *getGroupById(s32 id);
void clearDigimonItems(void);
u8 *getGroupInOrder(s32 index);
void clearGroups(void);
void deleteFriend(struct WifiData *wifi, s32 index);
s32 func_020b4ab8();

#endif /* FARM_FARM_GROUPS_H */
