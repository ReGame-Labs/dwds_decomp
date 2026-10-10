#include "menus/widgets/text_list.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "engine/text/print_text.h"
#include "engine/text/text_object.h"

/* Sets preset `index` of the text lists' creation (createTextList). */
void setTextListPreset(s32 index, s32 value, s16 x, s16 y) {
    data_021b53fc[index] = value;
    data_021b53dc[index] = x;
    data_021b53ec[index] = y;
}

/* Sets the text drawing flag of a kind: 0x80, 0x20 or 0x40 of data_021e33cc
 * (0x80 for an unknown kind). */
void func_0204c5e0(s32 kind) {
    switch (kind) {                                 /* irregular */
        case 0:
            func_020a5848();
            return;
        case 1:
            func_020a58a8();
            return;
        case 2:
            func_020a5878();
            return;
        default:
            func_020a5848();
            return;
    }
}

/* Clears it. */
void func_0204c58c(s32 kind) {
    switch (kind) {                                 /* irregular */
        case 0:
            func_020a5830();
            return;
        case 1:
            func_020a5890();
            return;
        case 2:
            func_020a5860();
            return;
        default:
            func_020a5830();
            return;
    }
}

/* Empties the text lists' slots. */
void initTextLists(void) {
    s32 i;

    for (i = 0; i < TEXT_LIST_COUNT; i++) {
        TEXT_LIST_IDS[i] = -1;
    }
}

/* A text list's task: when its position has moved, frees the rows' images,
 * then draws it. */
void tickTextList(void) {
    struct TextListTask *task;

    task = (struct TextListTask *) getCurrentTask();
    switch (task->state) {
        case TEXT_LIST_ACTIVE:
            if (task->position != task->drawnPosition) {
                freeTextListImages(task);
            }
            drawTextList(task);
            break;
        case TEXT_LIST_PAUSED:
            break;
    }
}

/* Sets a text list's position. */
void setTextListPos(s32 id, s16 position) {
    struct TextListTask *task = findTextList(id);

    if (task != NULL) {
        task->position = position;
    }
}

/* Has a text list drawn again. */
void redrawTextList(s32 id) {
    struct TextListTask *task;

    task = findTextList(id);
    if (task != NULL) {
        task->redraw = TRUE;
    }
}

/* Sets unk4A of a row of a text list. */
void func_0204bff8(s32 id, s32 row, s8 value) {
    struct TextListTask *task;

    task = findTextList(id);
    if (task == NULL) {
        return;
    }
    if (row < 0 || row >= TEXT_LIST_ROWS) {
        return;
    }
    task->unk4A[row] = value;
}

/* Sets a text list's unk28 and has it drawn again. */
void func_0204bfd8(s32 id, s32 value) {
    struct TextListTask *task = findTextList(id);

    if (task != NULL) {
        task->unk28  = value;
        task->redraw = TRUE;
    }
}
