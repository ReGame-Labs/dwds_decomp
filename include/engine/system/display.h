#ifndef ENGINE_SYSTEM_DISPLAY_H
#define ENGINE_SYSTEM_DISPLAY_H

#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "types.h"

/* Flags of DISPLAY_FLAGS; initDisplay clears 2 and sets 4. */
#define DISPLAY_FLAG_2 0x2
#define DISPLAY_FLAG_4 0x4

/* What softReset resets the game with, kept by the hardware where
 * NitroSDK's OS_ResetSystem leaves its parameter. */
#define SOFT_RESET_MAGIC 0x01234567
#define RESET_PARAMETER (*(s32 *) 0x027FFC20)

s16 putSubBgChars(u8 bg, s16 slot, s16 count, s32 data);
s16 putMainBgChars(u8 bg, s16 slot, s16 count, s32 data);
void clearVramTransfers(void);
void getSubBgPriorities(s32 *bg0, s32 *bg1, s32 *bg2, s32 *bg3);
void getMainBgPriorities(s32 *bg0, s32 *bg1, s32 *bg2, s32 *bg3);
void applySubBgPriorities(void);
void applyMainBgPriorities(void);
void applyHideSubLayers(void);
void applyHideMainLayers(void);
void applyShowSubLayers(void);
void applyShowMainLayers(void);
void applySetSubLayers(void);
void applySetMainLayers(void);
u8 isDisplayReady(void);
void setDisplayReady(void);
void func_0208786c(void);
void func_02087884(void);
s32 isSoftReset(void);
void softReset(void);
void func_020878d4(void);
void func_020878ec(void);
void resetBgPriorities(void);
void setSubBgPriorities(s32 bg0, s32 bg1, s32 bg2, s32 bg3);
void setMainBgPriorities(s32 bg0, s32 bg1, s32 bg2, s32 bg3);
void hideSubLayers(s32 layers);
void hideMainLayers(s32 layers);
void showSubLayers(s32 layers);
void showMainLayers(s32 layers);
void setSubLayersShown(s8 layers);
void setMainLayersShown(s8 layers);
s32 addVBlankCallback();
s32 func_020879c4();
void initDisplay(void);
void func_02086df4(s32 index, s32 *gfx);
s16 loadSubBgChars(u8 bg, s16 slot, struct CharacterData *chars);
s16 loadMainBgChars(u8 bg, s16 slot, struct CharacterData *chars);
void runVramTransfers(void);
struct BgData *copySubBgScreenAndFlush(u8 *params);
struct BgData *copyMainBgScreenAndFlush(u8 *params);
s32 *allocVramTransferData(s32 size);
s32 queueVramTransfer();

#endif /* ENGINE_SYSTEM_DISPLAY_H */
