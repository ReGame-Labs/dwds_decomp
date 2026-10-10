#include "menus/widgets/scroll_bar.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/libs.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/field_menu/field_menu.h"
#include "menus/field_menu/party_panel.h"
#include "menus/widgets/menu_displays.h"
#include "title/title_menu.h"

/* Empties the scroll bars' slots. */
void initScrollBars(void) {
    s32 i;

    for (i = 0; i < SCROLL_BAR_COUNT; i++) {
        SCROLL_BAR_IDS[i] = -1;
    }
}

/* Ends a scroll bar's task and frees its slot. */
void closeScrollBar(s32 id) {
    s32 i;

    if (id == -1) {
        return;
    }
    for (i = 0; i < SCROLL_BAR_COUNT; i++) {
        if (id == SCROLL_BAR_IDS[i]) {
            endTaskById(id);
            SCROLL_BAR_IDS[i] = -1;
            return;
        }
    }
}

/* A scroll bar's task: unless it is paused, calls its callback and has the
 * touch (or none, at -1) move it. */
void tickScrollBar(void) {
    struct ScrollBarTask *task;
    s16 x;
    s16 y;
    void (*callback)(struct ScrollBarTask *);

    task = (struct ScrollBarTask *) getCurrentTask();
    x    = -1;
    y    = -1;
    if (getTouchHeld() != 0) {
        x = getTouchX();
        y = getTouchY();
    }
    switch (task->state) {
        case SCROLL_BAR_PAUSED:
            return;
        case SCROLL_BAR_RESUMED:
            task->state = SCROLL_BAR_ACTIVE;
        case SCROLL_BAR_ACTIVE:
            callback = task->callback;
            if (callback != NULL) {
                callback(task);
            }
            updateScrollBar(task, x, y);
            return;
    }
}

/* Pauses a scroll bar and hides its sprite. */
void pauseScrollBar(s32 id) {
    struct ScrollBarTask *task;
    struct Sprite *sprite;

    task = findScrollBar(id);
    if (task == NULL) {
        return;
    }
    task->state   = SCROLL_BAR_PAUSED;
    sprite        = task->sprite;
    sprite->flags = (u16) (sprite->flags | SPRITE_HIDDEN);
}

/* Resumes a scroll bar and shows its sprite. */
void resumeScrollBar(s32 id) {
    struct ScrollBarTask *task;
    struct Sprite *sprite;

    task = findScrollBar(id);
    if (task == NULL) {
        return;
    }
    task->state   = SCROLL_BAR_RESUMED;
    sprite        = task->sprite;
    sprite->flags = (u16) (sprite->flags & ~SPRITE_HIDDEN);
}

/* A scroll bar's position, 0 for none. */
s16 getScrollBarPos(s32 id) {
    struct ScrollBarTask *task;

    task = findScrollBar(id);
    if (task != NULL) {
        return task->position;
    }
    return 0;
}

/* Sets a scroll bar's position. */
void setScrollBarPos(s32 id, s16 position) {
    struct ScrollBarTask *task;

    task = findScrollBar(id);
    if (task != NULL) {
        task->position = position;
    }
}

/* A scroll bar's task by its id, NULL if no slot has it. */
struct ScrollBarTask *findScrollBar(s32 id) {
    s32 i;

    if (id == -1) {
        return NULL;
    }
    for (i = 0; i < SCROLL_BAR_COUNT; i++) {
        if (id == SCROLL_BAR_IDS[i]) {
            return findTask(id);
        }
    }
    return NULL;
}

/* Opens the field menu. */
void openFieldMenu(void) {
    startFieldMenuTask();
}

/* Whether the field menu is open. */
s32 isFieldMenuOpen(void) {
    if (FIELD_MENU_TASK != NULL) {
        return 1;
    }
    return 0;
}

/* Opens the field menu: loads ov006 (loadOverlay(5)), sets display mode 9
 * (func_020a3454) and starts its task. */
void startFieldMenuTask(void) {
    struct FieldMenuTask *task;
    void *work;

    loadOverlay(5);
    func_020a3454(9);
    task             = createTask(tickFieldMenu, FIELD_MENU_TASK_PRIORITY);
    task->task.onEnd = NULL;
    FIELD_MENU_TASK  = task;
    work             = heapAlloc(sizeof(struct FieldMenuWork), 4);
    task->work       = work;
    func_02030f18(task->work, 0, sizeof(struct FieldMenuWork));
    work        = heapAlloc(FIELD_MENU_UNK20_SIZE, 4);
    task->unk20 = work;
    CLEAR(task->unk20, FIELD_MENU_UNK20_SIZE);
    task->state = 0;
    task->unk26 = 0;
    task->unk28 = 0xFF;
    func_020aa308(2, 1);
    func_020aa340(2, 1);
    func_02049f18(0, 2);
    loadFieldMenuBgs(task);
    initFieldMenuText(task);
    startMenuDisplaysTask();
}

/* Brings the field menu back, after one of its screens: display mode 9 and
 * its backgrounds and text slots again. */
void reopenFieldMenu(void) {
    struct FieldMenuTask *task;

    func_020a3454(9);
    task        = FIELD_MENU_TASK;
    task->state = 0;
    task->unk26 = 0;
    task->unk28 = 0xFF;
    func_020aa308(2, 1);
    func_020aa340(2, 1);
    func_02049f18(0, 2);
    loadFieldMenuBgs(task);
    initFieldMenuText(task);
}
