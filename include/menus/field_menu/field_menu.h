#ifndef MENUS_FIELD_MENU_FIELD_MENU_H
#define MENUS_FIELD_MENU_FIELD_MENU_H

#include "engine/data.h"
#include "types.h"

/* The field menu: its task (tickFieldMenu) picks one of six entries (the
 * Digimon, the items, the quests, the farm groups, the tamer and the save
 * screens). The setup and teardown of its backgrounds, text slots and VRAM. */

/* The menu's block of the heap. */
struct FieldMenuWork {
    /* 0x00 */ struct BgGraphics bg;  /* background 0xF, "m_bg02" */
    /* 0x18 */ struct BgGraphics bg2; /* background 4 */
    /* 0x30 */ u8 unk30[0xC4];
};

struct FieldMenuTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct FieldMenuWork *work;
    /* 0x20 */ u8 *unk20; /* a block of 0xE bytes */
    /* 0x24 */ s16 state;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 unk28; /* 0xFF at the start */
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30; /* freed by stopSubPaletteEffectsButFades */
    /* 0x34 */ s32 unk34; /* freed by stopMainPaletteEffectsButFades */
};

void freeFieldMenuText(void);
void initFieldMenuText(struct FieldMenuTask *task);
void clearBgAndSpriteVram(void);
void freeFieldMenuBgs(struct FieldMenuTask *task);
void loadFieldMenuBgs(struct FieldMenuTask *task);
void tickFieldMenu();

#endif /* MENUS_FIELD_MENU_FIELD_MENU_H */
