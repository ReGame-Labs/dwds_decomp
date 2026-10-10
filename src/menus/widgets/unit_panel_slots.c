#include "menus/widgets/unit_panel_slots.h"
#include "battle/battle_mode/battle_bg.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"

/* Swaps two unit panel slots and moves both panels to their new places. */
void swapUnitPanels(s32 a, s32 b) {
    u16 *ids  = UNIT_PANEL_SLOTS.ids;
    u16 id    = ids[b];
    s32 unk10 = UNIT_PANEL_SLOTS.unk10[b];
    s16 x     = UNIT_PANEL_SLOTS.x[b];
    s16 y     = UNIT_PANEL_SLOTS.y[b];

    ids[b]                    = ids[a];
    UNIT_PANEL_SLOTS.unk10[b] = UNIT_PANEL_SLOTS.unk10[a];
    UNIT_PANEL_SLOTS.x[b]     = UNIT_PANEL_SLOTS.x[a];
    UNIT_PANEL_SLOTS.y[b]     = UNIT_PANEL_SLOTS.y[a];
    ids[a]                    = id;
    UNIT_PANEL_SLOTS.unk10[a] = unk10;
    UNIT_PANEL_SLOTS.x[a]     = x;
    UNIT_PANEL_SLOTS.y[a]     = y;
    if (ids[a] != -1) {
        func_ov002_0224b7d0((s8) ids[a], UNIT_PANEL_OFFSETS[a * 2], UNIT_PANEL_OFFSETS[a * 2 + 1]);
    }
    if (ids[b] != -1) {
        func_ov002_0224b7d0((s8) ids[b], UNIT_PANEL_OFFSETS[b * 2], UNIT_PANEL_OFFSETS[b * 2 + 1]);
    }
}

/* Hands a value to a unit panel (func_ov002_0224b7c4), if a slot has it. */
void setUnitPanelValue(s32 id, s32 value) {
    if (findUnitPanelSlot(id) == -1) {
        return;
    }
    func_ov002_0224b7c4(id, value);
}

/* The slot of a unit panel, -1 if none has it. */
s32 findUnitPanelSlot(s32 id) {
    s32 index;

    for (index = 0; index < UNIT_PANEL_SLOT_COUNT; index++) {
        if (id == UNIT_PANEL_SLOTS.ids[index]) {
            return index;
        }
    }
    return -1;
}

/* The unit panel of a slot. */
u16 getSlotUnitPanel(s32 index) {
    return UNIT_PANEL_SLOTS.ids[index];
}

/* Frees a unit panel (func_ov002_0224b7dc) and empties its slot. */
void freeUnitPanel(s32 id) {
    s32 slot = findUnitPanelSlot(id);

    if (slot == -1) {
        return;
    }
    func_ov002_0224b7dc(id);
    UNIT_PANEL_SLOTS.ids[slot]   = 0xFFFF;
    UNIT_PANEL_SLOTS.unk10[slot] = 0;
    UNIT_PANEL_SLOTS.x[slot]     = 0;
    UNIT_PANEL_SLOTS.y[slot]     = 0;
}

/* Frees the sprites, unit panels 0 to 5 and func_020a1238's, and empties
 * every slot. */
void freeUnitPanels(void) {
    s32 i;
    struct UnitPanelSlots *panels;
    s32 slot;

    panels = &UNIT_PANEL_SLOTS;
    freeMainSprite(panels->sprite);
    UNIT_PANEL_SLOTS.sprite = -1;
    UNIT_PANEL_SLOTS.unk78  = 0;
    UNIT_PANEL_SLOTS.unk7A  = 0;
    for (i = 0; i < UNIT_PANEL_SPRITES; i++) {
        freeMainSprite(panels->sprites[i]);
        panels->sprites[i] = -1;
        panels->unk50[i]   = 0;
        panels->unk5A[i]   = 0;
    }
    freeUnitPanel(0);
    freeUnitPanel(1);
    freeUnitPanel(2);
    freeUnitPanel(3);
    freeUnitPanel(4);
    freeUnitPanel(5);
    func_020a1238();
    panels = &UNIT_PANEL_SLOTS;
    for (slot = 0; slot < UNIT_PANEL_SLOT_COUNT; slot++) {
        UNIT_PANEL_SLOTS.ids[slot] = 0xFFFF;
        panels->unk10[slot]        = 0;
        panels->x[slot]            = 0;
        panels->y[slot]            = 0;
    }
}

/* Sets up a unit panel with its slot's unk10 (func_ov002_0224b7b8). */
void func_0204ca8c(s32 id, s16 unk1, s16 unk2) {
    s32 index = findUnitPanelSlot(id);

    if (index == -1) {
        return;
    }
    func_ov002_0224b7b8(id, UNIT_PANEL_SLOTS.unk10[index], unk1, unk2);
}

/* Moves a unit panel to (x, y), off its slot's offset. */
void moveUnitPanel(s32 id, s16 x, s16 y) {
    struct UnitPanelSlots *panels = &UNIT_PANEL_SLOTS;
    s32 slot                      = findUnitPanelSlot(id);

    if (slot == -1) {
        return;
    }
    panels->x[slot] = x;
    panels->y[slot] = y;
    func_ov002_0224b7d0(id, x + UNIT_PANEL_OFFSETS[slot * 2], y + UNIT_PANEL_OFFSETS[slot * 2 + 1]);
}

/* The number of decimal digits of a value, up to 7 (0 has 1). */
s32 countDigits(s32 value) {
    s32 digits;
    s32 divisor;

    if (value == 0) {
        return 1;
    }
    for (divisor = 1, digits = 1; digits < 8; digits++, divisor *= 10) {
        if (func_0202de00(value, divisor) == 0) {
            return digits - 1;
        }
    }
    return 1;
}
