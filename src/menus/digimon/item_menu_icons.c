#include "menus/digimon/item_menu_icons.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/display.h"
#include "menus/digimon/data.h"
#include "nitro/g2d.h"

/* Queues the copy of background 3's characters to background 0's VRAM, past
 * 0x3000, and loads its palette: the same as func_ov006_02281f70, for the item
 * menu. */
void func_ov006_0227d780(void) {
    struct ItemMenu *menu = ITEM_MENU;
    struct VramCopy copy  = {0};
    struct CharacterData *chars;
    struct NNSG2dPaletteData *palette;

    chars     = menu->graphics->bg[3].chars;
    copy.src  = chars->data;
    copy.dest = (void *) (func_020db56c() + 0x3000);
    copy.size = chars->size;
    if (copy.size >= 0x1000) {
        copy.size = 0x1000;
    }
    queueVramTransfer(&copy);
    palette = menu->graphics->bg[3].palette;
    loadMainPalette(0x60, (u16) (getPaletteSize((s32) menu->graphics->bg[3].paletteFile, palette) >> 1),
                    (s32) palette->pRawData);
}

/* Draws, on background 0, the icons of 6 by 8 tiles whose flag is set and
 * clears the others: five of them in mode 0, else only flag1 to flag3 at the
 * three places after those five. The same as func_ov006_02281dd8, for the item
 * menu. */
void func_ov006_0227d600(u8 flag0, u8 flag1, u8 flag2, u8 flag3, u8 flag4, u8 mode) {
    u8 flags[5]            = {flag0, flag1, flag2, flag3, flag4};
    struct ItemMenu *menu  = ITEM_MENU;
    struct ScreenCopy copy = {0};
    struct ScreenData *screen;
    s32 i;

    screen         = menu->graphics->bg[3].screen;
    copy.bg        = 0;
    copy.unk2      = 0x180;
    copy.unk4      = 6;
    copy.srcWidth  = 32;
    copy.srcHeight = 32;
    if (mode == 0) {
        for (i = 0; i < 5; i++) {
            copy.srcX   = 0;
            copy.x      = data_ov006_0229efd0[i * 2];
            copy.srcY   = 0;
            copy.width  = 6;
            copy.height = 8;
            copy.y      = data_ov006_0229efd0[i * 2 + 1];
            if (flags[i] != 0) {
                copy.src = screen->data;
            } else {
                copy.src = NULL;
            }
            copyMainBgScreenAndFlush((u8 *) &copy);
        }
    } else {
        for (i = 1; i < 4; i++) {
            copy.srcX   = 0;
            copy.x      = data_ov006_0229efd0[(i - 1) * 2 + 10];
            copy.srcY   = 0;
            copy.width  = 6;
            copy.height = 8;
            copy.y      = data_ov006_0229efd0[(i - 1) * 2 + 11];
            if (flags[i] != 0) {
                copy.src = screen->data;
            } else {
                copy.src = NULL;
            }
            copyMainBgScreenAndFlush((u8 *) &copy);
        }
    }
}
