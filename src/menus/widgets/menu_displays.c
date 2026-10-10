#include "menus/widgets/menu_displays.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"

/* Frees the back button's group. Written out three times: twice inside
 * another test of the same id, so the original had an inline function. */
static inline void freeBackButtonGroup(void) {
    if (BACK_BUTTON_GROUP == -1) {
        return;
    }
    closeButtonGroup(BACK_BUTTON_GROUP);
    BACK_BUTTON_GROUP = -1;
}

/* Makes a back button: touching the rect or pressing one of the keys sets
 * *state to nextState and frees the button. */
void createBackButton(s16 *state, s16 nextState, s16 x, s16 y, s16 width, s16 height, s32 keys) {
    struct ButtonGroup *group;
    struct BackButton *button;

    if (BACK_BUTTON_GROUP != -1) {
        freeBackButtonGroup();
    }
    BACK_BUTTON_GROUP = createButtonGroup(0x38, 0, onBackButton);
    addRectButton(x, y, width, height, 0, BACK_BUTTON_GROUP);
    group             = findTask(BACK_BUTTON_GROUP);
    button            = (struct BackButton *) group->work;
    button->state     = state;
    button->nextState = nextState;
    button->keys      = keys;
}

/* The back button's callback. */
void onBackButton(s16 touched, s16 cursor, struct ButtonGroup *group) {
    struct BackButton *button = (struct BackButton *) group->work;
    u16 keys                  = button->keys;

    if (!(keys & getPadPressed()) && takeButtonGroupTap(BACK_BUTTON_GROUP) == 0) {
        return;
    }
    *button->state = button->nextState;
    freeBackButtonGroup();
}

/* Frees the back button. */
void closeBackButton(void) {
    freeBackButtonGroup();
}

/* Forgets the menu displays' task without ending it. */
void resetMenuDisplays(void) {
    MENU_DISPLAYS_TASK  = NULL;
    MENU_DISPLAYS_USERS = 0;
}

/* Releases the menu displays: the last screen using them ends their task,
 * with every task of its priority. */
void releaseMenuDisplays(void) {
    MENU_DISPLAYS_USERS -= 1;
    if (MENU_DISPLAYS_USERS > 0) {
        return;
    }
    endTasksOfPriority(0x11B);
    MENU_DISPLAYS_TASK  = NULL;
    MENU_DISPLAYS_USERS = 0;
}
