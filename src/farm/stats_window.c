#include "farm/stats_window.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/sprite/sprite.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "farm/data.h"
#include "farm/farm_groups.h"
#include "farm/results.h"
#include "menus/widgets/menu_displays.h"
#include "menus/widgets/status_window.h"

/* Closes the stats before and after the day. */
void closeStatsCompare(void) {
    struct StatsCompare *compare;

    compare = findTask(data_021e5cb8);
    freeStatusWindowSprites(0);
    func_020587fc(0);
    freeStatusWindowSprites(1);
    func_020587fc(1);
    releaseMenuDisplays();
    closeWindowAndClear(&compare->beforeWindow);
    closeWindowAndClear(&compare->afterWindow);
    releaseGfxSlot(compare->gfxSlot);
    endTaskById(data_021e5cb8);
    data_021e5cb8 = 0;
    freeTextBank();
    clearUiFlag(FARM_PANEL_STATS);
}

/* Shows the stats of another digimon before and after the day. Sprites 1 to 8
 * of the window of the stats after are the arrows on the stats that went
 * up. */
void showStatsCompare(s32 digimon) {
    struct StatsCompare *compare;
    struct Window *window;
    struct Digimon *after;
    struct Digimon *before;

    compare = findTask(data_021e5cb8);
    window  = getWindow(compare->afterWindow);
    if (getUiFlag(FARM_PANEL_STATS) == 0) {
        return;
    }
    if (digimon == compare->shown) {
        return;
    }
    compare->shown   = digimon;
    compare->digimon = digimon;
    before           = getDigimonBeforeDay(digimon);
    after            = getDigimon(digimon);
    func_02058590(0, before);
    func_02058590(1, after);
    if (before == NULL || after == NULL) {
        func_020a8a98(compare->afterWindow, -1, -1, -1, -1, 0xFFFF);
        func_020a869c(compare->afterWindow, 1, 999, 999);
        func_020a869c(compare->afterWindow, 2, 999, 999);
        func_020a869c(compare->afterWindow, 3, 999, 999);
        func_020a869c(compare->afterWindow, 4, 999, 999);
        func_020a869c(compare->afterWindow, 5, 999, 999);
        func_020a869c(compare->afterWindow, 6, 999, 999);
        func_020a869c(compare->afterWindow, 7, 999, 999);
        func_020a869c(compare->afterWindow, 8, 999, 999);
        return;
    }
    if (after->unk48 > before->unk48) {
        setMainSpritePos(window->sprites[1], (window->x + 10) * 8, (window->y + 6) * 8 - 2);
    } else {
        setMainSpritePos(window->sprites[1], 999, 999);
    }
    if (after->unk4A > before->unk4A) {
        setMainSpritePos(window->sprites[2], (window->x + 10) * 8, (window->y + 8) * 8 - 2);
    } else {
        setMainSpritePos(window->sprites[2], 999, 999);
    }
    if (after->unk4C > before->unk4C) {
        setMainSpritePos(window->sprites[3], (window->x + 10) * 8, (window->y + 10) * 8 - 2);
    } else {
        setMainSpritePos(window->sprites[3], 999, 999);
    }
    if (after->unk4E > before->unk4E) {
        setMainSpritePos(window->sprites[4], (window->x + 10) * 8, (window->y + 12) * 8 - 2);
    } else {
        setMainSpritePos(window->sprites[4], 999, 999);
    }
    if (after->maxLevel > before->maxLevel) {
        setMainSpritePos(window->sprites[5], (window->x + 10) * 8, (window->y + 14) * 8 - 2);
    } else {
        setMainSpritePos(window->sprites[5], 999, 999);
    }
    if (after->maxHp > before->maxHp) {
        setMainSpritePos(window->sprites[6], window->x * 8 + 0x34, window->y * 8 + 0x20);
    } else {
        setMainSpritePos(window->sprites[6], 999, 999);
    }
    if (after->maxMp > before->maxMp) {
        setMainSpritePos(window->sprites[7], window->x * 8 + 0x6C, window->y * 8 + 0x20);
    } else {
        setMainSpritePos(window->sprites[7], 999, 999);
    }
    if (after->level > before->level) {
        setMainSpritePos(window->sprites[8], window->x * 8 + 0x73, window->y * 8 + 0x12);
    } else {
        setMainSpritePos(window->sprites[8], 999, 999);
    }
}
