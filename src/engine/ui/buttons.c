#include "engine/ui/buttons.h"
#include "battle/battle_state.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/save/game_state.h"
#include "engine/sprite/sprite.h"
#include "engine/system/system.h"
#include "engine/ui/gauge.h"
#include "nitro/pad.h"
#include "title/title_menu.h"

/* Sets the game up at boot (main calls it): a cleared save (func_020a4694),
 * no buttons, the UI (func_020aa6a0), the play-time task and func_02080fe4's
 * state. */
void initGameData(void) {
    func_020a4694(&data_021db5f8);
    clearButtons();
    func_020aa6a0(0, 1);
    startPlayTimeClock();
    func_02080fe4();
}

/* A friend code to show in a text, 1122-3344-5566: a placeholder. */
u64 getFriendCode(void) {
    return 112233445566ULL;
}

/* Forgets the overlays loaded and loads the field's: the map, the event
 * scripts and the farm. */
void loadFieldOverlays(void) {
    data_021e5ad8 = OVERLAY_MODE_NONE;
    data_021e5ae4 = OVERLAY_MODE_NONE;
    data_021e5ae8 = OVERLAY_MODE_NONE;
    loadOverlay(OVERLAY_MODE_FIELD);
    loadOverlay(OVERLAY_MODE_SCRIPTS);
    loadOverlay(OVERLAY_MODE_FARM);
}

/* Whether the field map's overlay is loaded. */
BOOL isFieldOverlayLoaded(void) {
    if (data_021e5ad8 == OVERLAY_MODE_FIELD) {
        return TRUE;
    }
    return FALSE;
}

/* Frees every button. */
void clearButtons(void) {
    s32 i;

    for (i = 0; i < BUTTON_COUNT; i++) {
        BUTTONS[i].flags = 0;
    }
}

/* Runs a button group once a frame, after it has waited its first frames and
 * while it isn't paused. */
void tickButtonGroup(void) {
    struct ButtonGroup *group = (struct ButtonGroup *) getCurrentTask();

    if (group->wait > 0) {
        group->wait--;
        return;
    }
    if (group->flags & BUTTON_GROUP_PAUSED) {
        return;
    }
    func_020b2228(group);
    if (group->callback != NULL) {
        group->callback(group->touched, group->cursor, group);
    }
    func_020b2328(group);
}

/* The rectangle of the main screen sprite's cell, in pixels. */
void getMainSpriteRect(struct Rect *rect, u16 sprite) {
    getSpriteCellRect(rect, getMainSprite(sprite));
}

/* The rectangle of the sub screen sprite's cell, in pixels. */
void getSubSpriteRect(struct Rect *rect, u16 sprite) {
    getSpriteCellRect(rect, getSubSprite(sprite));
}

/* Pauses the group: its task stops testing the buttons. */
void pauseButtonGroup(s32 id) {
    struct ButtonGroup *group = findTask(id);

    if (group != NULL) {
        group->flags |= BUTTON_GROUP_PAUSED;
    }
}

/* Lets a paused group run again. */
void resumeButtonGroup(s32 id) {
    struct ButtonGroup *group = findTask(id);

    if (group != NULL) {
        group->flags &= ~BUTTON_GROUP_PAUSED;
    }
}

/* Puts the group's cursor on the button, as if it were touched. */
void setButtonGroupCursor(s32 button, s32 id) {
    struct ButtonGroup *group = findTask(id);

    if (group != NULL) {
        group->touched = button;
        group->cursor  = button;
    }
}

/* The button of the group's cursor, 0 when there's no group. */
s16 getButtonGroupCursor(s32 id) {
    struct ButtonGroup *group = findTask(id);

    if (group == NULL) {
        return 0;
    }
    return group->cursor;
}

/* Whether a button of the group was tapped, which uses up the tap. */
BOOL takeButtonGroupTap(s32 id) {
    BOOL tapped;
    struct ButtonGroup *group;

    group  = findTask(id);
    tapped = FALSE;
    if (group != NULL && getTouchTap() == 1 && group->touched != -1) {
        clearTouch();
        tapped = TRUE;
    }
    return tapped;
}

/* Whether a button of the group was tapped, leaving the tap for others. */
BOOL isButtonGroupTapped(s32 id) {
    BOOL tapped;
    struct ButtonGroup *group;

    group  = findTask(id);
    tapped = FALSE;
    if (group != NULL && getTouchTap() == 1 && group->touched != -1) {
        tapped = TRUE;
    }
    return tapped;
}

/* The button tapped, or -1, using up the tap. */
s16 getGroupTappedButton(struct ButtonGroup *group) {
    s16 button = -1;

    if (group != NULL && getTouchTap() == 1 && group->touched != -1) {
        clearTouch();
        button = group->touched;
    }
    return button;
}

/* getGroupChosenButton for the group with the task id. */
s16 getChosenButton(s32 id) {
    return getGroupChosenButton(findTask(id));
}

/* The button chosen: the cursor's when A is pressed, or the one tapped, or -1. */
s16 getGroupChosenButton(struct ButtonGroup *group) {
    s16 button = -1;

    if (group != NULL) {
        if (getPadPressed() & PAD_BUTTON_A) {
            button = group->cursor;
        } else if (getTouchTap() == 1 && group->touched != -1) {
            clearTouch();
            button = group->touched;
        }
    }
    return button;
}

/* The group's index-th button, NULL if there's none. */
struct Button *getButton(s32 index, s32 id) {
    struct ButtonGroup *group;
    u8 button;

    group = findTask(id);
    if (group == NULL) {
        return NULL;
    }
    button = group->buttons[index];
    if (button == BUTTON_NONE) {
        return NULL;
    }
    return &BUTTONS[button];
}

/* Adds a button that takes its rectangle from the object getSubActor or
 * getMainActor returns for sprite, and returns its index in the group. */
s32 addObjectButton(s16 sprite, u16 flags, s32 id) {
    struct ButtonGroup *group = findTask(id);
    struct Button *button;
    s32 free;
    s32 i;

    if (group == NULL) {
        return 0;
    }
    for (free = 0, button = BUTTONS; free < BUTTON_COUNT && button->flags != 0; button++, free++) {
    }
    for (i = 0; i < BUTTON_COUNT; i++) {
        if (group->buttons[i] == BUTTON_NONE) {
            group->buttons[i]    = free;
            BUTTONS[free].flags  = flags | BUTTON_OBJECT;
            BUTTONS[free].sprite = sprite;
            group->count++;
            break;
        }
    }
    return i;
}

/* Switches off the group's index-th button. */
void disableButton(s32 index, s32 id) {
    struct ButtonGroup *group;
    u8 button;

    group = findTask(id);
    if (group == NULL) {
        return;
    }
    button = group->buttons[index];
    if (button == BUTTON_NONE) {
        return;
    }
    BUTTONS[button].flags |= BUTTON_DISABLED;
}

/* Switches the group's index-th button back on. */
void enableButton(s32 index, s32 id) {
    struct ButtonGroup *group;
    u8 button;

    group = findTask(id);
    if (group == NULL) {
        return;
    }
    button = group->buttons[index];
    if (button == BUTTON_NONE) {
        return;
    }
    BUTTONS[button].flags &= ~BUTTON_DISABLED;
}
