#include "battle/unit_panels.h"
#include "battle/sprite_slots.h"
#include "battle/unit_panel_draw.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"
#include "engine/text/font.h"
#include "engine/text/text_object.h"
#include "engine/text/window_text.h"
#include "engine/ui/gauge.h"

/* Whether the touch is inside the rectangle, edges included. */
s32 isTouchInRect(u32 left, u32 top, u32 right, u32 bottom) {
    u32 x;
    u32 y;

    x = getTouchX();
    y = getTouchY();
    if (left <= x && x <= right && top <= y && y <= bottom) {
        return 1;
    }
    return 0;
}

/* Sets the byte the shop screens of menus/shop/farm_shops.c and menus/shop/item_equipment_shop.c set to 1
 * when they close. */
void func_0207e6bc(s8 value) {
    data_021bb7dc = value;
}

/* The mode func_0207e63c set. */
u8 func_0207e6ac(void) {
    return data_021bb7d8;
}

/* Which of the two kinds of list the current mode shows (func_0207e658). */
s32 func_0207e694(void) {
    return func_0207e658(data_021bb7d8);
}

/* Modes 1 and 3 are of the second kind of list, 0, 2, 4 and 5 of the first;
 * 0xFF for any other. */
s32 func_0207e658(s32 mode) {
    switch (mode) {
        case 0:
        case 2:
        case 4:
        case 5:
            return 0;
        case 1:
        case 3:
            return 1;
        default:
            return 0xFF;
    }
}

/* Sets the mode and a second value; the script command of engine/script/operand.c
 * does, before it starts the task func_0207e6cc. */
void func_0207e63c(s8 mode, s8 arg1) {
    data_021bb7d8 = mode;
    data_021bb7d4 = arg1;
}

/* The 19 ids of list index of the first table. */
u16 *func_0207e628(s32 index) {
    return data_021bb800[index];
}

/* Copies 19 ids into list index of the first table. */
void func_0207e5f4(s32 index, const u16 *src) {
    s32 i;

    for (i = 0; i < 19; i++) {
        data_021bb800[index][i] = *src;
        src++;
    }
}

/* The 23 ids of list index of the second table. */
u16 *func_0207e5e0(s32 index) {
    return data_021bb84c[index];
}

/* Copies 23 ids into list index of the second table. */
void func_0207e5ac(s32 index, const u16 *src) {
    s32 i;

    for (i = 0; i < 23; i++) {
        data_021bb84c[index][i] = *src;
        src++;
    }
}

/* The 16 ids that menus/shop/farm_shops.c's screen lists. */
u16 *func_0207e5a0(void) {
    return data_021bb7e0;
}

/* Copies the 16 ids that menus/shop/farm_shops.c's screen lists. */
void func_0207e574(u16 *src) {
    s32 i;

    for (i = 0; i < 16; i++) {
        data_021bb7e0[i] = *src;
        src++;
    }
}

/* Once a frame: rolls the units' numbers, marks the units whose panels need
 * redrawing, and moves and draws the panels. */
void updateUnitPanels(void) {
    s32 i;
    u8 *changed;
    struct UnitStatus *status;
    struct UnitPanel *panel;

    changed = UNIT_CHANGES;
    status  = UNIT_STATUS;
    for (i = 0; i < UNIT_COUNT; i++) {
        *changed = UNIT_UNCHANGED;
        if (status->rollFrames0 != 0) {
            status->roll0.value += status->rollStep0;
            status->shown0 = status->roll0.part.whole;
            status->rollFrames0--;
            *changed = UNIT_CHANGED;
        }
        if (status->rollFrames1 != 0) {
            status->roll1.value += status->rollStep1;
            status->shown1 = status->roll1.part.whole;
            status->rollFrames1--;
            *changed = UNIT_CHANGED;
        }
        if (status->unk10 != status->shownUnk10) {
            status->shownUnk10 = status->unk10;
            *changed           = UNIT_CHANGED;
        }
        changed++;
        status++;
    }

    panel = &UNIT_PANELS[UNIT_PANEL_COUNT - 1];
    for (i = UNIT_PANEL_COUNT - 1; i >= 0; i--) {
        if (panel->flags & UNIT_PANEL_MARK_CHANGED) {
            if (UNIT_CHANGES[panel->unit] == UNIT_UNCHANGED) {
                UNIT_CHANGES[panel->unit] = UNIT_CHANGED_BY_PANEL;
            }
            if (!(panel->flags & UNIT_PANEL_SKIP_DRAW)) {
                panel->flags &= ~UNIT_PANEL_MARK_CHANGED;
            }
        }
        if (panel->flags & UNIT_PANEL_USED) {
            if (panel->flags & UNIT_PANEL_TIMER) {
                if (panel->timer != 0) {
                    panel->timer--;
                    if (panel->timer == 0) {
                        func_020846bc((findUnitPanel(panel->unit) + 5) * 0x10 + 0x900, 0x10, -11);
                        markMainPalettesDirty();
                    }
                }
            }
            if (panel->flags & UNIT_PANEL_MOVING) {
                if (panel->moveDelay != 0) {
                    panel->moveDelay--;
                }
                if (panel->moveFrames != 0 && panel->moveDelay == 0) {
                    panel->pos.x.value += panel->velocity.x.value;
                    panel->pos.y.value += panel->velocity.y.value;
                    setSlotSpritePosition(panel->sprites[0], panel->pos.x.part.whole, panel->pos.y.part.whole);
                    panel->numberPos0.x.value += panel->velocity.x.value;
                    panel->numberPos0.y.value += panel->velocity.y.value;
                    panel->numberPos1.x.value += panel->velocity.x.value;
                    panel->numberPos1.y.value += panel->velocity.y.value;
                    if (panel->sprites[1] != 0xFF) {
                        panel->spritePos1.x.value += panel->velocity.x.value;
                        panel->spritePos1.y.value += panel->velocity.y.value;
                        setSlotSpritePosition(panel->sprites[1], panel->spritePos1.x.part.whole,
                                              panel->spritePos1.y.part.whole);
                    }
                    panel->spritePos2.x.value += panel->velocity.x.value;
                    panel->spritePos2.y.value += panel->velocity.y.value;
                    setSlotSpritePosition(panel->sprites[2], panel->spritePos2.x.part.whole, panel->spritePos2.y.part.whole);
                    panel->textPos.x.value += panel->velocity.x.value;
                    panel->textPos.y.value += panel->velocity.y.value;
                    panel->moveFrames--;
                    if (panel->moveFrames == 0) {
                        panel->flags &= ~UNIT_PANEL_MOVING;
                        panel->flags &= ~UNIT_PANEL_TEXT_AFTER_MOVE;
                        if (panel->flags & UNIT_PANEL_CLOSE_AFTER_MOVE) {
                            func_0207d920(panel->unit);
                        }
                    }
                }
            }
            if (panel->flags & UNIT_PANEL_USED) {
                if (!(panel->flags & UNIT_PANEL_SKIP_DRAW) && isUnitChanged(panel->unit) == 1) {
                    func_0207d0fc(panel->unit);
                }
                if (!(panel->flags & UNIT_PANEL_SKIP_DRAW)) {
                    func_020a4ad4(&panel->numbers[0], panel->numberPos0.x.part.whole, panel->numberPos0.y.part.whole);
                    if (panel->unit <= 5) {
                        func_020a4ad4(&panel->numbers[1], panel->numberPos1.x.part.whole, panel->numberPos1.y.part.whole);
                    }
                    if (!(panel->flags & UNIT_PANEL_TEXT_AFTER_MOVE)) {
                        func_020a58c0(&panel->text, panel->textPos.x.part.whole, panel->textPos.y.part.whole);
                    }
                } else {
                    panel->flags &= ~UNIT_PANEL_SKIP_DRAW;
                }
            }
        }
        panel--;
    }
}

/* Frees every panel and sets up its text window: one line in font 5, two
 * characters wide. */
void initUnitPanels(void) {
    s32 i;
    struct UnitPanel *panel;
    struct Font *font;
    struct TextWindow *text;

    for (i = 0; i < UNIT_PANEL_COUNT; i++) {
        PANEL_UNITS[i] = -1;
    }
    panel = UNIT_PANELS;
    for (i = 0; i < UNIT_PANEL_COUNT; i++) {
        panel->flags      = 0;
        font              = func_020a97c8(5);
        text              = &panel->text;
        text->unk4        = 4;
        text->unk6        = 0;
        text->unkA        = 0xFFFF;
        text->font        = 5;
        text->width       = (font->charWidth * 2 + 8) / 8;
        text->height      = 1;
        text->unk1C       = 0;
        text->unk20       = 0;
        text->unk24       = 0;
        text->unk26       = 0;
        panel->text.flags = 2;
        func_020a6b10(text);
        panel++;
    }
}

/* Frees every panel's text window. */
void freeUnitPanelTexts(void) {
    s32 i;
    struct UnitPanel *panel;

    panel = UNIT_PANELS;
    for (i = 0; i < UNIT_PANEL_COUNT; i++) {
        freeWindowImage(&panel->text);
        panel++;
    }
}

/* What the unit's panel shows of it. */
struct UnitStatus *getUnitStatus(s32 unit) {
    return &UNIT_STATUS[unit];
}

/* The panel with the index. */
struct UnitPanel *getUnitPanel(s32 index) {
    return &UNIT_PANELS[index];
}

/* Whether the unit's panel has to be redrawn: a mark the panel itself set is
 * taken back. */
s32 isUnitChanged(s32 unit) {
    u8 state = UNIT_CHANGES[unit];

    if (state == UNIT_UNCHANGED) {
        return 0;
    }
    if (state == UNIT_CHANGED_BY_PANEL) {
        UNIT_CHANGES[unit] = UNIT_UNCHANGED;
    }
    return 1;
}

/* Marks the unit changed, for its panel to be redrawn. */
void markUnitChanged(s32 unit) {
    UNIT_CHANGES[unit] = UNIT_CHANGED;
}
