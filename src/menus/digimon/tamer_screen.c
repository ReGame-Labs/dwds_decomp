#include "menus/digimon/tamer_screen.h"
#include "engine/bg/bg_layers.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/sprite/sprite_create.h"
#include "engine/text/font.h"
#include "engine/ui/buttons.h"
#include "menus/digimon/data.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Leaves the Tamer screen: removes its sprites and buttons, gives back what
 * openTamerScreen took from allocMainVram and allocSubVram, stops drawing
 * the play time and unloads font00 from both screens. */
void func_ov006_0227cb7c(struct TamerScreen *screen) {
    freeMainSprite(screen->unk28);
    freeMainSprite(screen->unk2C);
    func_ov006_0227bebc(screen);
    func_0208577c(2, screen->unk4A);
    func_02085710(2, screen->unk4C);
    screen->playTimeChar = -1;
    func_020a98a8(2);
    func_020a9844(2);
}

/* Whether the Tamer screen has closed: its task clears TAMER_SCREEN
 * when it ends. */
u8 isTamerScreenClosed(void) {
    return TAMER_SCREEN == NULL;
}

/* Frees the Tamer screen's backgrounds. */
void freeTamerScreenBgs(struct TamerScreen *screen) {
    stopSubPaletteEffectsButFades(screen->subPaletteEffect);
    stopMainPaletteEffectsButFades(screen->mainPaletteEffect);
    freeBgGraphics(&data_ov006_0229f428);
    freeBgGraphics(&data_ov006_0229f4a0);
    freeBgGraphics(&data_ov006_0229f440);
    freeBgGraphics(&data_ov006_0229f458);
    freeBgGraphics(&data_ov006_0229f470);
    freeBgGraphics(&data_ov006_0229f488);
}

/* Clears the VRAM of both screens' backgrounds and sprites, their OAM and
 * their blending: the same as func_ov006_0227fd6c. */
void func_ov006_0227c088(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    G2_BlendNone();
    MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    G2S_BlendNone();
}

/* Removes the three buttons and their sprites. */
void func_ov006_0227bebc(struct TamerScreen *screen) {
    if (screen->buttons != -1) {
        closeButtonGroup(screen->buttons);
        screen->buttons = -1;
    }
    freeMainSprite(0);
    freeMainSprite(1);
    freeMainSprite(2);
}
