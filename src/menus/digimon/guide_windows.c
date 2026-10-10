#include "menus/digimon/guide_windows.h"
#include "engine/bg/bg_affine.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/text/font.h"
#include "engine/ui/dial.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "menus/digimon/data.h"
#include "menus/widgets/scroll_bar.h"
#include "nitro/g2.h"
#include "title/title_menu.h"

/* Does nothing; the callbacks of the tab buttons and of sprites 12 and 13
 * call it. */
void func_ov006_0229be64(void) {}

/* Frees the sub screen sprite func_ov006_0229be94 makes for the cursor's
 * Digimon. */
void func_ov006_0229be68(void) {
    freeSubSprite(data_ov006_0229f540);
    data_ov006_0229f540 = -1;
}

/* The same as func_ov006_0229be68. */
void func_ov006_0229be38(void) {
    freeSubSprite(data_ov006_0229f540);
    data_ov006_0229f540 = -1;
}

/* Loads the window frame of /dat/bg/m_listbg00 (entry 0xD of data_0213537c)
 * into graphics slot 0 of the main screen and slot 1 of the sub screen,
 * emptying them first. */
void func_ov006_0229bdd4(void) {
    void *files = func_0204871c(0xD);

    func_020aa340(2, 1);
    func_020a9610(0);
    func_020aa2c0(files, 0, -1, 2);
    func_020aa308(2, 1);
    func_020a9610(1);
    func_020aa29c(files, 1, -1, 2);
}

/* The windows below are made off their screen, then slid in or out a tile a
 * frame by the functions after them, which return 1 once there (or once the
 * window is gone). */

/* The window of the list's rows. */
void func_ov006_0229bd64(struct DigimonGuide *guide) {
    struct WindowParams params;

    params.flags      = 0;
    params.x          = 32;
    params.y          = 1;
    params.gfxSlot    = 0;
    params.unk8       = 0;
    params.unkA       = 0;
    params.width      = 18;
    params.height     = 18;
    params.unk10      = 0;
    params.unk12      = 0;
    params.unk14      = 0xFFFF;
    params.unk16      = 0xFFFF;
    params.unk18      = 0xFFFF;
    params.callback   = NULL;
    guide->listWindow = func_020a91c4(&params);
}

/* Closes the list's window. */
void func_ov006_0229bd40(struct DigimonGuide *guide) {
    if (guide->listWindow != 0xFF) {
        closeWindow(guide->listWindow);
        guide->listWindow = 0xFF;
    }
}

/* Slides the list's window left, to x 14. */
s32 func_ov006_0229bce4(struct DigimonGuide *guide) {
    s32 done = 0;
    struct Window *window;
    s16 x;
    s16 y;

    window = getWindow(guide->listWindow);
    if (window == NULL) {
        return 1;
    }
    x = window->x - 1;
    y = window->y;
    if (x <= 14) {
        x    = 14;
        done = 1;
    }
    func_020a8e3c(guide->listWindow, x, y);
    return done;
}

/* Slides the list's window right, out to x 32. */
s32 func_ov006_0229bc88(struct DigimonGuide *guide) {
    s32 done = 0;
    struct Window *window;
    s16 x;
    s16 y;

    window = getWindow(guide->listWindow);
    if (window == NULL) {
        return 1;
    }
    x = window->x + 1;
    y = window->y;
    if (x >= 32) {
        x    = 32;
        done = 1;
    }
    func_020a8e3c(guide->listWindow, x, y);
    return done;
}

/* Window unk5F, 15 by 18 tiles, at x 32. */
void func_ov006_0229bc10(struct DigimonGuide *guide) {
    struct WindowParams params;

    params.flags    = 1;
    params.x        = 32;
    params.y        = 4;
    params.gfxSlot  = 1;
    params.unk8     = 18;
    params.unkA     = 0;
    params.width    = 15;
    params.height   = 18;
    params.unk10    = 0;
    params.unk12    = 0;
    params.unk14    = 0xFFFF;
    params.unk16    = 0xFFFF;
    params.unk18    = 0xFFFF;
    params.callback = NULL;
    guide->unk5F    = func_020a91c4(&params);
}

/* Closes window unk5F. */
void func_ov006_0229bbec(struct DigimonGuide *guide) {
    if (guide->unk5F != 0xFF) {
        closeWindow(guide->unk5F);
        guide->unk5F = 0xFF;
    }
}

/* Slides window unk5F left, to x 17. */
s32 func_ov006_0229bb90(struct DigimonGuide *guide) {
    s32 done = 0;
    struct Window *window;
    s16 x;
    s16 y;

    window = getWindow(guide->unk5F);
    if (window == NULL) {
        return 1;
    }
    x = window->x - 1;
    y = window->y;
    if (x <= 17) {
        x    = 17;
        done = 1;
    }
    func_020a8e3c(guide->unk5F, x, y);
    return done;
}

/* Window unk61, 17 by 14 tiles, at y -14. */
void func_ov006_0229bb14(struct DigimonGuide *guide) {
    struct WindowParams params;

    params.flags    = 1;
    params.x        = 16;
    params.y        = -14;
    params.gfxSlot  = 1;
    params.unk8     = 0;
    params.unkA     = 18;
    params.width    = 17;
    params.height   = 14;
    params.unk10    = 0;
    params.unk12    = 0;
    params.unk14    = 0xFFFF;
    params.unk16    = 0xFFFF;
    params.unk18    = 0xFFFF;
    params.callback = NULL;
    guide->unk61    = func_020a91c4(&params);
}

/* Closes window unk61. */
void func_ov006_0229baf0(struct DigimonGuide *guide) {
    if (guide->unk61 != 0xFF) {
        closeWindow(guide->unk61);
        guide->unk61 = 0xFF;
    }
}

/* Slides window unk61 down, to y 33. */
s32 func_ov006_0229ba94(struct DigimonGuide *guide) {
    s32 done = 0;
    struct Window *window;
    s16 x;
    s16 y;

    window = getWindow(guide->unk61);
    if (window == NULL) {
        return 1;
    }
    x = window->x;
    y = window->y + 1;
    if (y >= 33) {
        y    = 33;
        done = 1;
    }
    func_020a8e3c(guide->unk61, x, y);
    return done;
}

/* The name window, 17 by 14 tiles, at y -44. */
void func_ov006_0229ba18(struct DigimonGuide *guide) {
    struct WindowParams params;

    params.flags      = 0;
    params.x          = 16;
    params.y          = -44;
    params.gfxSlot    = 1;
    params.unk8       = 0;
    params.unkA       = 18;
    params.width      = 17;
    params.height     = 14;
    params.unk10      = 0;
    params.unk12      = 0;
    params.unk14      = 0xFFFF;
    params.unk16      = 0xFFFF;
    params.unk18      = 0xFFFF;
    params.callback   = NULL;
    guide->nameWindow = func_020a91c4(&params);
}

/* Slides the name window down, to y 3. */
s32 func_ov006_0229b9bc(struct DigimonGuide *guide) {
    s32 done = 0;
    struct Window *window;
    s16 x;
    s16 y;

    window = getWindow(guide->nameWindow);
    if (window == NULL) {
        return 1;
    }
    x = window->x;
    y = window->y + 1;
    if (y >= 3) {
        y    = 3;
        done = 1;
    }
    func_020a8e3c(guide->nameWindow, x, y);
    return done;
}

/* The tab window, 31 by 19 tiles, at x -32. */
void func_ov006_0229b940(struct DigimonGuide *guide) {
    struct WindowParams params;

    params.flags     = 1;
    params.x         = -32;
    params.y         = 4;
    params.gfxSlot   = 1;
    params.unk8      = 33;
    params.unkA      = 0;
    params.width     = 31;
    params.height    = 19;
    params.unk10     = 0;
    params.unk12     = 0;
    params.unk14     = 0xFFFF;
    params.unk16     = 0xFFFF;
    params.unk18     = 0xFFFF;
    params.callback  = NULL;
    guide->tabWindow = func_020a91c4(&params);
}

/* Slides the tab window right, two tiles a frame, to x 1, blending it over
 * the screen behind it. */
s32 func_ov006_0229b8c4(struct DigimonGuide *guide) {
    s32 done = 0;
    struct Window *window;
    s16 x;
    s16 y;

    window = getWindow(guide->tabWindow);
    if (window == NULL) {
        return 1;
    }
    x = window->x + 2;
    y = window->y;
    if (x >= 1) {
        x    = 1;
        done = 1;
    }
    func_020a8e3c(guide->tabWindow, x, y);
    G2S_SetBlendAlpha(2, 0x3D, 10, 6);
    return done;
}

/* Clears the inside of the tab window, 30 by 20 tiles from tile (2, 3). */
void func_ov006_0229b884(struct DigimonGuide *guide) {
    func_020a8a98(guide->tabWindow, 2, 3, 30, 20, 0);
    redrawWindow(guide->tabWindow);
}

/* The dial that picks the order of the list, set to the current one. */
void func_ov006_0229b830(struct DigimonGuide *guide) {
    struct {
        s16 unk0;
        s16 unk2;
        s16 unk4;
        s16 unk6;
        s16 unk8;
        s16 count; /* of positions */
        s16 value;
    } params;

    params.unk0      = 4;
    params.unk2      = 0x92;
    params.unk4      = 0x64;
    params.unk6      = 0x20;
    params.count     = 4;
    params.unk8      = 0x30;
    params.value     = guide->order;
    guide->orderDial = openDial(&params);
}

/* Closes the order dial. */
void func_ov006_0229b814(struct DigimonGuide *guide) {
    closeDial(guide->orderDial);
    guide->orderDial = -1;
}

/* The scroll bar of the list, and its sprite. */
void func_ov006_0229b780(struct DigimonGuide *guide) {
    struct {
        s16 value;
        s16 rows;  /* shown */
        s16 count; /* the bar's range is count less rows */
        s16 x;
        s16 y;
        s16 width;
        s16 height;
        u32 sprite;
        s16 spriteX; /* the sprite's offset */
        s16 spriteY;
    } params;

    guide->scrollBarSprite = createMainSprite(0x3A1, 0, 0, 1, 0);
    params.value           = guide->scroll;
    params.rows            = guide->rows;
    params.count           = guide->maxScroll + guide->rows;
    params.x               = 0xE8;
    params.y               = 0x10;
    params.width           = 0x10;
    params.height          = 0x80;
    params.sprite          = guide->scrollBarSprite;
    params.spriteX         = 0;
    params.spriteY         = -8;
    guide->scrollBar       = createScrollBar(0, &params);
}

/* Frees the scroll bar's sprite and closes the scroll bar. */
void func_ov006_0229b75c(struct DigimonGuide *guide) {
    freeMainSprite(guide->scrollBarSprite);
    closeScrollBar(guide->scrollBar);
    guide->scrollBar = -1;
}
