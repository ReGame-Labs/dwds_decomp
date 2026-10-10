#include "farm/panel_pages.h"
#include "engine/data.h"
#include "engine/sprite/sprite.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_object.h"
#include "engine/ui/gauge.h"
#include "engine/window/window.h"
#include "farm/data.h"
#include "farm/goods_panel.h"
#include "farm/panel_digimon.h"
#include "farm/panel_status.h"

/* The callback of a window of the farm's pages: keeps the window's first
 * sprite and the image where the window is. */
void func_ov005_02281004(u16 flags, struct Window *window) {
    struct FarmPages *pages;

    if (data_021e5cb8 == 0) {
        return;
    }
    pages = findTask(data_021e5cb8);
    setMainSpritePos(window->sprites[0], (window->x + 1) * 8, (window->y + 8) * 8);
    if (pages->image.flags != 0) {
        func_020a58c0(&pages->image, pages->imageX, pages->imageY);
    }
}

/* Turns to the page of the farm, if panel 4 is open. */
void setFarmPage(s32 owner, s16 page) {
    struct FarmPages *pages;

    if (getUiFlag(FARM_PANEL_PAGES) == 0) {
        return;
    }
    pages = findTask(data_021e5cb8);
    if (pages->owner == owner && pages->page == page) {
        return;
    }
    pages->page  = page;
    pages->owner = owner;
    pages->state = FARM_PAGE_STATES[page];
}

/* Closes panel 4. */
void closeFarmPages(void) {
    struct FarmPages *pages;
    s32 i;

    if (getUiFlag(FARM_PANEL_PAGES) == 0) {
        return;
    }
    pages = findTask(data_021e5cb8);
    for (i = 0; i < FARM_SLOT_COUNT; i++) {
        func_ov005_0228c7c4(&pages->unk62[i]);
        func_ov005_0228c7c4(&pages->unk72[i]);
    }
    closeWindow(pages->windows[0]);
    closeWindow(pages->windows[1]);
    closeWindow(pages->windows[2]);
    if (pages->image.flags != 0) {
        freeWindowImage(&pages->image);
    }
    func_020a98a8(2);
    releaseGfxSlot(pages->gfxSlot);
    endTaskById(data_021e5cb8);
    data_021e5cb8 = 0;
    clearUiFlag(FARM_PANEL_PAGES);
}

/* Opens panel 0 on the digimon, or shows the digimon there if it is open. */
void openDigimonPanel(struct Digimon *digimon, s8 palette, s16 mode) {
    struct DigimonPanel *panel;

    if (getUiFlag(FARM_PANEL_DIGIMON) != 0) {
        func_ov005_0227fe6c(digimon->id);
        return;
    }
    panel          = createTask(func_ov005_022809f4, 0x10F);
    data_021e5cb8  = getTaskId(panel);
    panel->state   = 0;
    panel->wait    = 0;
    panel->shown   = digimon;
    panel->digimon = panel->shown;
    panel->palette = palette;
    panel->mode    = mode;
    setUiFlag(FARM_PANEL_DIGIMON);
}

/* The same with panel 0xA. */
void openSecondDigimonPanel(struct Digimon *digimon, s8 palette, s16 mode) {
    struct DigimonPanel *panel;

    if (getUiFlag(FARM_PANEL_DIGIMON_B) != 0) {
        func_ov005_0227fe54(digimon->id);
        return;
    }
    panel          = createTask(func_ov005_02280704, 0x10F);
    data_021e5cb0  = getTaskId(panel);
    panel->state   = 0;
    panel->wait    = 0;
    panel->shown   = digimon;
    panel->digimon = panel->shown;
    panel->palette = palette;
    panel->mode    = mode;
    setUiFlag(FARM_PANEL_DIGIMON_B);
}
