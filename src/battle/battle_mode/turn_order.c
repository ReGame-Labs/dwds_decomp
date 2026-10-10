#include "battle/battle_mode/turn_order.h"
#include "battle/battle_mode/battle.h"
#include "battle/battle_mode/battle_bg.h"
#include "battle/battle_mode/data.h"
#include "battle/battle_state.h"
#include "battle/link_party.h"
#include "battle/sprite_slots.h"
#include "battle/unit_panels.h"
#include "engine/bg/bg_layers.h"
#include "engine/digimon/game_data.h"
#include "engine/system/display.h"
#include "engine/text/text_object.h"
#include "engine/ui/gauge.h"

/* Rebuilds the turn order after the turn being played: takes back the turns
 * the order gave each unit, then gives them again. */
void rebuildTurnOrder(struct BattleTask *task) {
    struct BattleStats *stats;
    s32 i;
    u8 index;
    struct Turn *turn;

    index = task->turn + 1;
    if (index >= TURN_COUNT) {
        index = 0;
    }
    turn = &BATTLE->turns[index];
    for (i = 1; i < TURN_COUNT; i++) {
        stats = &BATTLE->units[turn->unit].stats;
        index++;
        stats->nextTurn -= stats->turnInterval;
        turn++;
        if (index >= TURN_COUNT) {
            index = 0;
            turn  = BATTLE->turns;
        }
    }
    func_ov002_0224a0c8(0);
    index = task->turn + 1;
    if (index >= TURN_COUNT) {
        index = 0;
    }
    for (i = 1; i < TURN_COUNT; i++) {
        func_ov002_02249f64(&BATTLE->turns[index]);
        index++;
        if (index >= TURN_COUNT) {
            index = 0;
        }
    }
}

/* The setters below change the display at the next vblank. */
void setBattleDispSelect(enum GXDispSelect sel) {
    BATTLE->dispSelect = sel;
    addVBlankCallback(&applyBattleDispSelect);
}

/* Picks one of the three setups of the sub screen's BG3 (subBg3Setup) and sets
 * unk4533. */
void func_ov002_02249e10(s8 value, s8 subBg3Setup) {
    BATTLE->unk4533     = value;
    BATTLE->subBg3Setup = subBg3Setup;
    addVBlankCallback(&func_ov002_0224bca8);
}

/* Sets the main screen's blending. */
void setBattleMainBlend(s32 plane1, s32 plane2, s32 ev1, s32 ev2) {
    BATTLE->mainBlend.plane1 = plane1;
    BATTLE->mainBlend.plane2 = plane2;
    BATTLE->mainBlend.ev1    = ev1;
    BATTLE->mainBlend.ev2    = ev2;
    addVBlankCallback(&applyBattleMainBlend);
}

/* Sets the sub screen's blending. */
void setBattleSubBlend(s32 plane1, s32 plane2, s32 ev1, s32 ev2) {
    BATTLE->subBlend.plane1 = plane1;
    BATTLE->subBlend.plane2 = plane2;
    BATTLE->subBlend.ev1    = ev1;
    BATTLE->subBlend.ev2    = ev2;
    addVBlankCallback(&applyBattleSubBlend);
}

/* Changes the sub screen's blend weights. */
void changeBattleSubBlendWeights(s32 ev1, s32 ev2) {
    BATTLE->subBlend.ev1 = ev1;
    BATTLE->subBlend.ev2 = ev2;
    addVBlankCallback(&applyBattleSubBlendWeights);
}

/* Turns the main screen's blending off. */
void disableBattleMainBlend(void) {
    addVBlankCallback(&applyBattleMainBlendOff);
}

/* Turns the sub screen's blending off. */
void disableBattleSubBlend(void) {
    addVBlankCallback(&applyBattleSubBlendOff);
}

/* Copies a layout's setup into a text window. */
void copyWindowLayout(struct WindowLayout *layout, struct TextWindow *window) {
    window->unk4   = layout->window.unk4;
    window->unkA   = layout->window.unkA;
    window->font   = layout->window.font;
    window->width  = layout->window.width;
    window->height = layout->window.height;
    window->unk1C  = layout->window.unk1C;
    window->unk20  = layout->window.unk20;
    window->flags  = layout->window.flags;
}

/* Closes the message window. */
void func_ov002_02247bf4(void) {
    func_020867fc(1, 0, 2, 0x20, 4, 0);
    freeWindowImage(&BATTLE->windows[0]);
    releaseSlotSprite(0x2A);
    BATTLE->unk4B91 = 0;
}

/* Counts down the delayed values and hands each to playSound once its
 * frames have run out. */
void func_ov002_02247b94(void) {
    s32 i;
    struct DelayedValue *delayed;

    delayed = BATTLE->delayedValues;
    for (i = 0; i < DELAYED_VALUE_COUNT; i++) {
        if (delayed->value != -1) {
            if (delayed->frames != 0) {
                delayed->frames--;
            } else {
                playSound(delayed->value);
                delayed->value = -1;
            }
        }
        delayed++;
    }
}

/* Queues a value for playSound in so many frames; FALSE when the queue is
 * full. */
BOOL func_ov002_02247b34(s16 value, s16 frames) {
    s32 i;
    struct DelayedValue *delayed;

    delayed = BATTLE->delayedValues;
    for (i = 0; i < DELAYED_VALUE_COUNT; i++) {
        if (delayed->value == -1) {
            delayed->value  = value;
            delayed->frames = frames;
            return TRUE;
        }
        delayed++;
    }
    return FALSE;
}

/* Puts a unit in the first panel, with no icon sprite yet (0xFF). */
void setFirstUnitPanelUnit(u8 unit) {
    data_ov002_0225a7c8.unit       = unit;
    data_ov002_0225a7c8.sprites[1] = 0xFF;
}

/* The unit in one of the panels after the first. */
s8 getUnitPanelUnit(s32 index) {
    struct UnitPanel *panel = &data_ov002_0225a9e8[index];

    return panel->unit;
}

/* Puts a unit in one of the panels after the first, with no icon sprite yet
 * (0xFF). */
void setUnitPanelUnit(s32 index, u8 unit) {
    struct UnitPanel *panel = &data_ov002_0225a9e8[index];

    panel->unit       = unit;
    panel->sprites[1] = 0xFF;
}

/* Redraws the first panel's numbers and icon from its unit's status. */
void refreshFirstUnitPanel(void) {
    struct UnitPanel *panel;
    struct UnitStatus *status;
    u8 icon;

    panel                   = &data_ov002_0225a7c8;
    status                  = getUnitStatus(panel->unit);
    panel->numbers[0].value = status->shown0;
    func_020a4980(&panel->numbers[0]);
    if (panel->unit <= 5) {
        panel->numbers[1].value = status->shown1;
        func_020a4980(&panel->numbers[1]);
    }
    panel->flags |= 0x10;
    if (panel->unit <= 5) {
        icon = ((struct Digimon *) getDigimon(status->unk14))->unk1A;
    } else if (isLocalBattle()) {
        icon = ((struct EnemyData *) func_020a14e8(status->unk14))->unk03;
    } else {
        icon = ((struct Digimon *) findLinkPartyDigimon(status->unk14))->unk1A;
    }
    if (status->unk10 == 0xFF) {
        setSlotSpriteAnimation(panel->sprites[1], (u16) icon);
        return;
    }
    setSlotSpriteAnimation(panel->sprites[1], (u16) (status->unk10 + 9));
}

/* The same as refreshFirstUnitPanel for one of the panels after the first. */
void refreshUnitPanel(s32 index) {
    struct UnitPanel *panel;
    struct UnitStatus *status;
    u8 icon;

    panel                   = &data_ov002_0225a9e8[index];
    status                  = getUnitStatus(panel->unit);
    panel->numbers[0].value = status->shown0;
    func_020a4980(&panel->numbers[0]);
    if (panel->unit <= 5) {
        panel->numbers[1].value = status->shown1;
        func_020a4980(&panel->numbers[1]);
    }
    panel->flags |= 0x10;
    if (panel->unit <= 5) {
        icon = ((struct Digimon *) getDigimon(status->unk14))->unk1A;
    } else if (isLocalBattle()) {
        icon = ((struct EnemyData *) func_020a14e8(status->unk14))->unk03;
    } else {
        icon = ((struct Digimon *) findLinkPartyDigimon(status->unk14))->unk1A;
    }
    if (status->unk10 == 0xFF) {
        setSlotSpriteAnimation(panel->sprites[1], (u16) icon);
        return;
    }
    setSlotSpriteAnimation(panel->sprites[1], (u16) (status->unk10 + 9));
}
