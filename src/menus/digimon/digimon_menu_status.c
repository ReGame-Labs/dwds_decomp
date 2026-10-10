#include "menus/digimon/digimon_menu_status.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "menus/digimon/data.h"
#include "menus/widgets/digimon_detail.h"
#include "menus/widgets/status_window.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Frees the backgrounds' graphics that func_ov006_022880d0 and
 * loadDigimonMenuBgs set up. */
void freeDigimonMenuBgs(struct DigimonMenu *menu) {
    stopSubPaletteEffectsButFades(menu->subPaletteEffect);
    stopMainPaletteEffectsButFades(menu->mainPaletteEffect);
    if (menu->work->bg[0].paletteFile != NULL) {
        heapFree(menu->work->bg[0].paletteFile);
        menu->work->bg[0].paletteFile = NULL;
    }
    if (menu->work->bg[0].charFile != NULL) {
        heapFree(menu->work->bg[0].charFile);
        menu->work->bg[0].charFile = NULL;
    }
    if (menu->work->bg[0].screenFile != NULL) {
        heapFree(menu->work->bg[0].screenFile);
        menu->work->bg[0].screenFile = NULL;
    }
    if (menu->work->bg[1].paletteFile != NULL) {
        heapFree(menu->work->bg[1].paletteFile);
        menu->work->bg[1].paletteFile = NULL;
    }
    if (menu->work->bg[1].charFile != NULL) {
        heapFree(menu->work->bg[1].charFile);
        menu->work->bg[1].charFile = NULL;
    }
    if (menu->work->bg[1].screenFile != NULL) {
        heapFree(menu->work->bg[1].screenFile);
        menu->work->bg[1].screenFile = NULL;
    }
    if (menu->work->bg[2].paletteFile != NULL) {
        heapFree(menu->work->bg[2].paletteFile);
        menu->work->bg[2].paletteFile = NULL;
    }
    if (menu->work->bg[2].charFile != NULL) {
        heapFree(menu->work->bg[2].charFile);
        menu->work->bg[2].charFile = NULL;
    }
    if (menu->work->bg[2].screenFile != NULL) {
        heapFree(menu->work->bg[2].screenFile);
        menu->work->bg[2].screenFile = NULL;
    }
    if (menu->work->bg[3].paletteFile != NULL) {
        heapFree(menu->work->bg[3].paletteFile);
        menu->work->bg[3].paletteFile = NULL;
    }
    if (menu->work->bg[3].charFile != NULL) {
        heapFree(menu->work->bg[3].charFile);
        menu->work->bg[3].charFile = NULL;
    }
    if (menu->work->bg[3].screenFile != NULL) {
        heapFree(menu->work->bg[3].screenFile);
        menu->work->bg[3].screenFile = NULL;
    }
}

/* Clears the VRAM of both screens' backgrounds and sprites, their OAM and
 * their blending: the same as func_ov006_0227fd6c. */
void func_ov006_02288020(void) {
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

/* Loads the fonts the Digimon menu writes with (data_02127184's): font_dg,
 * font00, font_s, font_s2 and font_n on the main screen, font_s and font_s2
 * once more with palette 0x10, and the first four on the sub screen. */
void loadDigimonMenuFonts(void) {
    func_020a9c40(1, 3, 0xF);
    func_020a9c40(2, 5, 0xF);
    func_020a9c40(4, 7, 0xF);
    func_020a9c40(5, 9, 0xF);
    func_020a9c40(3, 0xA, 0xF);
    func_020a9c40(4, 0xB, 0x10);
    func_020a9c40(5, 0xC, 0x10);
    func_020a9ae0(1, 2, 0xF);
    func_020a9ae0(2, 4, 0xF);
    func_020a9ae0(4, 6, 0xF);
    func_020a9ae0(5, 8, 0xF);
}

/* Unloads the fonts of loadDigimonMenuFonts. */
void unloadDigimonMenuFonts(void) {
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a98a8(4);
    func_020a98a8(3);
    func_020a98a8(5);
    func_020a98a8(4);
    func_020a98a8(5);
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(4);
    func_020a9844(5);
}

/* Shows the Digimon in drawDigimonDetail's display, in the second window. */
void func_ov006_02287e74(struct DigimonMenu *menu) {
    struct Params02059d8c params;

    params.digimon  = menu->work->digimon;
    params.window   = menu->windows[1];
    params.x        = 1;
    params.y        = 1;
    params.unkC     = 0;
    params.unkE     = 1;
    params.unk10    = 2;
    params.unk12    = 0xE;
    params.unk14[0] = 0;
    params.unk14[1] = 0;
    params.unk14[2] = 0;
    params.unk14[3] = 0;
    params.unk14[4] = 0;
    params.unk1E    = 2;
    params.unk20    = 2;
    params.unk22    = 0x50;
    params.unk24    = 2;
    params.unk26    = 9;
    drawDigimonDetail(0, &params);
}

/* Closes the display of func_ov006_02287e74. */
void func_ov006_02287e54(void) {
    freeDigimonDetailSprites(0);
    func_02059c50(0);
}

/* Shows the Digimon's status in the third window. */
void func_ov006_02287dc4(struct DigimonMenu *menu) {
    struct StatusParams params;

    func_020e23c0(&params, 0, sizeof(params));
    params.digimon = menu->work->digimon;
    params.window  = menu->windows[2];
    params.x       = 1;
    params.y       = 5;
    params.unk6    = 1;
    params.unk8    = 1;
    params.unk10   = 0;
    params.unk12   = 1;
    params.unk14   = 2;
    params.unk16   = 0xE;
    params.unk24   = 2;
    params.unk26   = 0x50;
    params.unk28   = 2;
    params.unk2A   = 1;
    params.unk22   = 2;
    params.unk2C   = 1;
    drawStatusWindow(0, &params);
}

/* Redraws the status of the Digimon menu's Digimon, while the menu is open. */
void redrawDigimonMenuStatus(void) {
    struct DigimonMenu *menu;

    if (DIGIMON_MENU == NULL) {
        return;
    }
    menu = findTask(DIGIMON_MENU_TASK_ID);
    func_02058590(0, menu->work->digimon);
}

/* Closes the status display. */
void func_ov006_02287d5c(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
}

/* Shows the Digimon's status in the fifth window. */
void func_ov006_02287cc4(struct DigimonMenu *menu) {
    struct StatusParams params;

    func_020e23c0(&params, 0, sizeof(params));
    params.digimon = menu->work->digimon;
    params.window  = menu->windows[4];
    params.x       = 1;
    params.y       = 5;
    params.unk6    = 1;
    params.unk8    = 1;
    params.unk10   = 2;
    params.unk12   = 3;
    params.unk14   = 4;
    params.unk16   = 0xE;
    params.unk24   = 2;
    params.unk26   = 0x30;
    params.unk28   = 2;
    params.unk2A   = 0;
    params.unk22   = 1;
    params.unk2C   = 1;
    drawStatusWindow(0, &params);
}

/* Closes the status display. */
void func_ov006_02287ca4(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
}
