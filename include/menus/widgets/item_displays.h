#ifndef MENUS_WIDGETS_ITEM_DISPLAYS_H
#define MENUS_WIDGETS_ITEM_DISPLAYS_H

#include "types.h"

/* The item and equipment displays: the key items, the item names, the bag, an
 * item's record, the equipment on a Digimon and a piece of equipment. */

s32 func_0204f5f4();
s32 func_0204fc04();
s32 func_02050974();
s32 func_0205140c();
s32 func_0205244c();
s32 func_02052f6c();
u8 *getKeyItemDisplayList(s16 index);
void closeKeyItemDisplay(s16 index);
void func_0204f8c8(s16 index, s16 value);
u8 *func_020501f4(s16 index);
void func_02050edc(s16 index, s16 value);
void func_02050ffc();
void func_02051dd8(s16 index, s32 value);
void closeEquippedDisplay(s16 index);
void func_02051edc();
void func_02052a98(s16 index, s16 value);
s32 func_02052c00();
void refreshKeyItemDisplay(s16 index, s32 mode, s16 value);
void freeKeyItemDisplaySprites(s16 index);
void freeItemNameDisplaySprite(s16 index);
void closeItemNameDisplay(s16 index);
void closeBagDisplay(s16 index);
void freeItemRecordDisplaySprites(s16 index);
void closeItemRecordDisplay(s16 index);
void freeEquipmentDisplaySprites(s16 index);
void freeBagDisplaySprites(s16 index);
void freeEquippedDisplaySprites(s16 index);
void closeEquipmentDisplay(s16 index);

#endif /* MENUS_WIDGETS_ITEM_DISPLAYS_H */
