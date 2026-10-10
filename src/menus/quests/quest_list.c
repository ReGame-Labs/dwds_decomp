#include "menus/quests/quest_list.h"
#include "engine/data.h"
#include "engine/palette/palette_fade.h"
#include "engine/save/card_backup.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "link/wifi_matching.h"

/* Puts the quest list, if it is open, in its state 600. */
void func_0207a2c0(void) {
    if (getUiFlag(UI_FLAG_QUEST_LIST) == 0) {
        return;
    }
    ((struct QuestList *) findTask(QUEST_LIST_TASK_ID))->state = 600;
}

/* Whether the quest list's unk20 is 0; 0 with no list. */
s32 func_0207a278(void) {
    if (getUiFlag(UI_FLAG_QUEST_LIST) == 0) {
        return 0;
    }
    return ((struct QuestList *) findTask(QUEST_LIST_TASK_ID))->unk20 == 0;
}

/* Closes the quest list, if it is open, and the quest window. */
void closeQuestList(void) {
    struct QuestList *list;

    if (getUiFlag(UI_FLAG_QUEST_LIST) == 0) {
        return;
    }
    list = findTask(QUEST_LIST_TASK_ID);
    closeButtonGroup(list->buttons);
    if (list->unk30 != 0xFF) {
        stopSubPaletteEffects();
    }
    closeWindow(list->windows[0]);
    closeWindow(list->windows[1]);
    closeWindow(list->windows[2]);
    releaseGfxSlot(list->fonts[1]);
    releaseGfxSlot(list->fonts[0]);
    endTask(list);
    QUEST_LIST_TASK_ID = 0;
    clearUiFlag(UI_FLAG_QUEST_LIST);
    closeQuestWindow();
}

/* Opens the quest window on a quest, or shows the quest in it if it is
 * open. */
void openQuestWindow(s16 quest, u8 unk20, u8 unk21) {
    struct QuestWindow *window;

    if (getUiFlag(UI_FLAG_QUEST_WINDOW) != 0) {
        showQuestWindowQuest(quest, 0);
        return;
    }
    window               = createTask(runQuestWindow, 0x115);
    QUEST_WINDOW_TASK_ID = getTaskId(window);
    window->state        = 0;
    window->unk1E        = 0;
    window->quest        = quest;
    window->unk20        = unk20;
    window->unk21        = unk21;
    window->unk24        = 0;
    setUiFlag(UI_FLAG_QUEST_WINDOW);
}
