#include "engine/text/window_text.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_banks.h"
#include "engine/window/window.h"

#define TEXT_BOX_SPRITES 3
#define TILE_BYTES_SHIFT 5 /* a 4bpp 8x8 tile is 32 bytes */

/* Closes the text box of data_021e33d8 (func_020a74ec), if one is open. */
void func_020a6e54(void) {
    struct TextBox *box = findTask(data_021e33d8);
    s32 text;

    if (box == NULL) {
        return;
    }
    if (box->sprites[2] != 0xFFFF) {
        freeMainSprite(box->sprites[2]);
    }
    if (box->sprites[1] != 0xFFFF) {
        freeMainSprite(box->sprites[1]);
    }
    if (box->sprites[0] != 0xFFFF) {
        freeMainSprite(box->sprites[0]);
    }
    text = box->spriteText;
    if (text != 0) {
        func_0209d954(text);
    }
    closeWindow(box->window);
    releaseGfxSlot(box->gfxSlot);
    func_020a98a8(1);
    func_020a98a8(2);
    freeTextBank();
    endTask(box);
    data_021d8cb8 &= ~5;
    data_021e33d8 = 0;
}

/* Fills tiles with one color: the 4-bit color in each pixel. */
void func_020a6ae8(void *tiles, s32 color, s32 count) {
    func_020e22dc((u16) (color | (color << 4) | (color << 8) | (color << 12)), tiles, count << TILE_BYTES_SHIFT);
}
