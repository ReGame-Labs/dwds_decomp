#ifndef MENUS_WIDGETS_MENU_DISPLAYS_H
#define MENUS_WIDGETS_MENU_DISPLAYS_H

/* The menu displays' task, shared by the screens that use it, and the back
 * button. */

#include "types.h"

struct ButtonGroup;
struct Task;

/* The back button's part of its button group's work. */
struct BackButton {
    /* 0x0 */ s16 *state; /* set to nextState when the button is used */
    /* 0x4 */ s16 nextState;
    /* 0x8 */ s32 keys; /* the pad buttons that also use it */
};

extern s16 MENU_DISPLAYS_USERS;
extern s32 BACK_BUTTON_GROUP;
extern struct Task *MENU_DISPLAYS_TASK;

void releaseMenuDisplays(void);
void resetMenuDisplays(void);
s32 func_0205b5b4();
void closeBackButton(void);
void createBackButton(s16 *state, s16 nextState, s16 x, s16 y, s16 width, s16 height, s32 keys);
void onBackButton(s16 touched, s16 cursor, struct ButtonGroup *group);
void startMenuDisplaysTask();

#endif /* MENUS_WIDGETS_MENU_DISPLAYS_H */
