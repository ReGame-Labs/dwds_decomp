#include "engine/script/cmd_gamestate.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/digimon/species_flags.h"
#include "engine/save/game_state.h"
#include "engine/script/cmd_choice.h"
#include "engine/script/cmd_core.h"
#include "engine/script/operand.h"
#include "engine/sprite/sprite.h"
#include "engine/system/display.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "engine/window/window.h"
#include "farm/farm_queries.h"
#include "m2c_macros.h"
#include "nitro/pad.h"

/* The choice menu's button callback for a list of choices: the B button picks
 * the last choice unless the menu's unk6C has bit 0x8; the cursor sprite goes
 * to the row's place in the window. */
void func_0208b6f4(s16 touched, s16 cursor, struct ButtonGroup *group) {
    struct ChoiceMenuTask *menu = findTask(CHOICE_MENU_TASK);
    struct Window *window       = getWindow(menu->window);
    u8 *entry                   = &data_02116b7c[menu->unk6C * 0x10];

    if ((getPadPressed() & PAD_BUTTON_B) && !(menu->unk6C & 8)) {
        menu->choice = menu->count - 1;
    } else {
        menu->choice = getGroupChosenButton(group);
    }
    setSubSpritePos(menu->sprite, (window->x + (s8) entry[6]) * 8 + 2, (window->y + (s8) entry[7] + cursor * 2) * 8);
}

/* The same for a menu whose B button picks the first choice. */
void func_0208b69c(s16 touched, s16 cursor, struct ButtonGroup *group) {
    struct ChoiceMenuTask *menu;

    menu = findTask(CHOICE_MENU_TASK);
    if ((getPadPressed() & PAD_BUTTON_B) && !(menu->unk6C & 8)) {
        menu->choice = 0;
        return;
    }
    menu->choice = getGroupChosenButton(group);
}

/* Command 0x126: puts the choice menu, if there is one, in state 10000 with
 * the operand and sleeps until the menu wakes the thread. */
s32 func_0208b62c(struct ScriptThread *thread) {
    s16 value = (u16) readOperand(thread);
    struct ChoiceMenuTask *menu;

    if (CHOICE_MENU_TASK == 0) {
        return 1;
    }
    menu         = findTask(CHOICE_MENU_TASK);
    menu->state  = 10000;
    menu->unk70  = value;
    menu->thread = thread->index;
    suspendScriptThread(thread->index);
    return 0;
}

/* Command 0x127: puts the choice menu, if there is one, in state 500 with
 * three operands and sleeps until the menu wakes the thread. */
s32 func_0208b5a0(struct ScriptThread *thread) {
    s16 kind   = readOperand(thread);
    s16 second = readOperand(thread);
    s16 third  = readOperand(thread);
    struct ChoiceMenuTask *menu;

    if (CHOICE_MENU_TASK == 0) {
        return 1;
    }
    menu         = findTask(CHOICE_MENU_TASK);
    menu->state  = 500;
    menu->kind   = kind;
    menu->unk66  = second;
    menu->unk6E  = third;
    menu->thread = thread->index;
    suspendScriptThread(thread->index);
    if (kind == 5) {
        func_020878d4();
    }
    return 0;
}

/* Whether a Digimon's unk1D is one of the bits of mask (bit n for value n). */
s32 func_0208b35c(s32 mask, struct Digimon *digimon) {
    if (((mask & 1) && (digimon->unk1D == 0)) || ((mask & 2) && (digimon->unk1D == 1)) ||
        ((mask & 4) && (digimon->unk1D == 2)) || ((mask & 8) && (digimon->unk1D == 3)) ||
        ((mask & 0x10) && (digimon->unk1D == 4)) || ((mask & 0x20) && (digimon->unk1D == 5)) ||
        ((mask & 0x40) && (digimon->unk1D == 6)) || ((mask & 0x80) && (digimon->unk1D == 7))) {
        return 1;
    }
    return 0;
}

/* Whether a Digimon fits a condition value (CONDITION_*). */
s32 func_0208b2b4(s32 condition, struct Digimon *digimon) {
    s32 fits;

    if (condition == CONDITION_ANY) {
        return 1;
    }
    if (condition < CONDITION_UNK1D) {
        if (digimon->unk4 == condition) {
            fits = 1;
        } else {
            fits = 0;
        }
        return fits;
    }
    if (condition < CONDITION_UNK1A) {
        if (digimon->unk1D == condition - CONDITION_UNK1D) {
            fits = 1;
        } else {
            fits = 0;
        }
        return fits;
    }
    if (condition < CONDITION_UNK1E) {
        if (digimon->unk1A == condition - CONDITION_UNK1A) {
            fits = 1;
        } else {
            fits = 0;
        }
        return fits;
    }
    if (digimon->unk1E == condition - CONDITION_UNK1E) {
        return 1;
    }
    return 0;
}

/* Whether the entry getFarmKindById gives for the group holding a Digimon
 * has an unk1A (1-9) whose bit is in mask; 9 shares 5's bit. */
s32 func_0208b23c(s32 mask, struct Digimon *digimon) {
    s32 bit;
    s8 type;
    void *entry;

    entry = getFarmKindById(findDigimonFarm(digimon->id)->id);
    type  = M2C_FIELD(entry, s8 *, 0x1A);
    bit   = 0;
    if (type == 1) {
        bit = 1;
    }
    if (type == 2) {
        bit = 2;
    }
    if (type == 3) {
        bit = 4;
    }
    if (type == 4) {
        bit = 8;
    }
    if (type == 5) {
        bit = 0x10;
    }
    if (type == 6) {
        bit = 0x20;
    }
    if (type == 7) {
        bit = 0x40;
    }
    if (type == 8) {
        bit = 0x80;
    }
    if (type == 9) {
        bit = 0x10;
    }
    if (bit & mask) {
        return 1;
    }
    return 0;
}

/* Whether the Digimon that fit a condition value number at least count, or,
 * for a count of -1, whether there are none. */
s32 func_0208b0f4(s32 condition, s32 count) {
    s32 none;
    s32 number;

    if (condition == CONDITION_ANY) {
        number = func_020a3418();
    } else if (condition < CONDITION_UNK1D) {
        number = func_020a331c(condition);
    } else if (condition < CONDITION_UNK1A) {
        number = func_020a32d8((u8) (condition - CONDITION_UNK1D));
    } else if (condition < CONDITION_UNK1E) {
        number = func_020a3294((u8) (condition - CONDITION_UNK1A));
    } else {
        number = countDigimonAtStage(condition - CONDITION_UNK1E);
    }
    if (count == -1) {
        if (number == 0) {
            none = 1;
        } else {
            none = 0;
        }
        return none;
    }
    if (number >= count) {
        return 1;
    }
    return 0;
}

/* Whether func_020a0f58's count is at least count. */
s32 func_0208b0d8(s32 count) {
    if (func_020a0f58() >= count) {
        return 1;
    }
    return 0;
}

/* Whether at least count of the event flags 0x1C9-0x204 are set. */
s32 func_0208b0b4(s32 count) {
    if ((s8) func_020a02b0() >= count) {
        return 1;
    }
    return 0;
}

/* Command 0x10A: adds the operand to func_020a0864's counter (capped at
 * 999999). */
s32 func_0208b080(struct ScriptThread *thread) {
    func_020a0864((u16) resolveOperand(thread, *thread->pc));
    thread->pc++;
    return 1;
}

/* Command 0x10B: calls func_020a0e44. */
s32 func_0208b068(struct ScriptThread *thread) {
    func_020a0e44();
    return 1;
}

/* Command 0x10C: adds the operand to addMoney's counter (capped at
 * 999999). */
s32 func_0208b04c(struct ScriptThread *thread) {
    addMoney(readOperand(thread));
    return 1;
}

/* Command 0x10D: puts getDigimonPlace of a Digimon (by index) into a local
 * variable. */
s32 func_0208b010(struct ScriptThread *thread) {
    s16 index;
    struct Digimon *digimon;

    index               = readOperand(thread);
    digimon             = getDigimonAt(readOperand(thread));
    thread->vars[index] = getDigimonPlace(digimon->id);
    return 1;
}
