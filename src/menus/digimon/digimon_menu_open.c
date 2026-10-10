#include "menus/digimon/digimon_menu_open.h"
#include "battle/battle_mode/battle_bg.h"
#include "battle/characters/chr_system.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/text/text_banks.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "menus/digimon/digimon_menu.h"
#include "menus/digimon/digimon_menu_status.h"
#include "menus/widgets/window_anim.h"
#include "title/title_menu.h"

/* Sets the Digimon menu's screens up again, as openDigimonMenu first did,
 * once a screen its run function opened over them has closed: the battle
 * characters' overlay (ov001), the backgrounds, fonts, window frames and
 * sprites. */
void restoreDigimonMenu(void) {
    struct DigimonMenu *menu;

    loadOverlay(3);
    func_020a3454(9);
    initMainBattleChrs(0x100);
    initSubBattleChrs(0x100);
    menu = findTask(DIGIMON_MENU_TASK_ID);
    loadDigimonMenuBgs(menu);
    func_ov006_022880d0(menu);
    func_020aa340(2, 1);
    func_020aa308(2, 1);
    loadDigimonMenuFonts();
    loadMainWindowFrameInSlot(1, 2);
    loadSubWindowFrameInSlot(0, 2);
    menu->windows[0]   = createMenuWindow(10, 1, 0, 0);
    menu->work->unk328 = createSubSprite(0x3A9, 0, 0, 0xF, 0);
    menu->work->unk324 = createMainSprite(0x1F7, 0x10, 0xA8, 0xF, 0);
    menu->work->unk32C = createMainSprite(0x21E, 0xA4, 0xB0, 0xE, 0);
    func_ov002_0224b80c();
    func_ov002_0224b824();
}

/* The Digimon menu task's onEnd: frees its blocks and forgets the task. */
void onDigimonMenuEnd(void) {
    struct DigimonMenu *menu = (struct DigimonMenu *) getCurrentTask();

    heapFree(menu->work);
    heapFree(menu->unk28);
    heapFree(menu->unk2C);
    heapFree(menu->techniques);
    heapFree(menu->traits);
    heapFree(menu->equipSlots);
    heapFree(menu->popup);
    heapFree(menu->tab);
    heapFree(menu->list0);
    heapFree(menu->list1);
    heapFree(menu->list2);
    heapFree(menu->unk50);
    DIGIMON_MENU_TASK_ID = -1;
    DIGIMON_MENU         = NULL;
    freeTextBank();
}
