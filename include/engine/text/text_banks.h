#ifndef ENGINE_TEXT_TEXT_BANKS_H
#define ENGINE_TEXT_TEXT_BANKS_H

/* Texts: the in-ROM name tables, the help banks of /dat/msg loaded one at a
 * time (loadTextBank), and the texts drawn as sprites. */

#include "engine/data.h"
#include "types.h"

/* A text drawn as sprites, a task of its own. */
struct SpriteText {
    struct Task task;
    u8 unk1C[0xA];
    /* 0x26 */ u16 tiles;   /* given back on its end */
    /* 0x28 */ u16 unk28;
    u8 unk2A[4];
    /* 0x2E */ u16 count;   /* of its sprites */
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ void *sprites; /* 12 bytes each, freed on its end */
    /* 0x3C */ s16 unk3C;
};

u16 *formatNumber(s32 value, s32 digits, u16 *buffer, s32 flags);
void *func_0209d304(s32 index);
void *func_0209d334(s32 index);
void *getAbilityHelp(s32 index);
void *getAbilityName(s32 index);
void *getSkillHelp(s32 index);
void *getSkillName(s32 index);
void *getSpeciesShortName(s16 index);
void *func_0209d470(s32 *table, s32 index);
void *getGroupName(s32 id);
void *getItemHelp(s32 item);
void *func_0209d6f8(s32 index);
s32 loadTextBank(s32 bank);
void *getDigimonName(s32 id);
BOOL func_0209d8c8(s32 id);
s16 func_0209d8e8(s32 id);
void func_0209d900(s32 id);
void func_0209d954(s32 id);
void *func_0209d41c(s16 id);
void *getCharacterName(s16 index);
void *func_0209d47c(s32 index, void *text0, void *text1, void *text2);
u16 *func_0209d2d0(const u16 *src, u16 *dst);
void *func_0209d5f4(s32 id);
void freeTextBank(void);
void *func_0209d320();
void *getSpeciesName();
void *func_0209d350(s32 value);
u8 *func_0209d378(s32 value);

#endif /* ENGINE_TEXT_TEXT_BANKS_H */
