#ifndef BATTLE_CHARACTERS_CHR_H
#define BATTLE_CHARACTERS_CHR_H

/* A battle character: its files in /dat/btchr/, its sequences and its placing
 * in one of the five slots of the main or the sub screen. */

#include "types.h"

struct BattleChr;
struct BtchrFrame;

void clearSubBattleChrFlags(u32 slot, s32 flags);
void clearMainBattleChrFlags(u32 slot, s32 flags);
void endBattleChrs(void);
void removeAllSubBattleChrs(void);
void removeAllMainBattleChrs(void);
void playMainBattleChrSeq(u32 slot, s16 seq, s16 loopLimit);
void setSubBattleChrFlags(u32 slot, s32 flags);
void setMainBattleChrFlags(u32 slot, s32 flags);
void freeBattleChrFiles(s32 chr);
void removeSubBattleChr(u32 slot);
void removeMainBattleChr(u32 slot);
/* Both return a struct BattleChr *, which func_ov002_02239a9c keeps in a u8 *. */
void *getSubBattleChr(u32 slot);
void *getMainBattleChr(u32 slot);
void playSubBattleChrSeq(u32 slot, s16 seq, s16 loopLimit);
void reallocSubBattleChrTiles(u32 offset);
void reallocMainBattleChrTiles(u32 offset);
void loadSubBattleChrPalette(s32 chr, s32 palette);
void loadMainBattleChrPalette(s32 chr, s32 palette);
void loadBattleChrAnim(s32 chr);
void loadBattleChrChars(s32 chr);
void startMainBattleChrPlaceTask(u16 chr, s16 x, s16 y, u16 palette, u32 slot, u16 place, u8 unk2E, u8 withSprite, s32 delay,
                                 u16 priority);
void startSubBattleChrPlaceTask(u16 chr, s16 x, s16 y, u16 palette, u32 slot, u16 place, u8 unk2E, u8 withSprite, s32 delay,
                                u16 priority, u8 show);
void tickMainBattleChrPlaceTask(void);
void tickSubBattleChrPlaceTask(void);
void placeSubBattleChr(u16 chr, s16 x, s16 y, u16 palette, u32 slot, u16 place, u8 unk2E, u8 withSprite);
void placeMainBattleChr(u16 chr, s16 x, s16 y, u16 palette, u32 slot, u16 place, u8 unk2E, u8 withSprite);
void skipBattleChrSeqs(struct BtchrFrame **frames, u16 seq);
s16 getBattleChrCell(struct BattleChr *chr);

#endif /* BATTLE_CHARACTERS_CHR_H */
