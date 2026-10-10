#include "menus/digiconvert/digiconvert_view.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/dial.h"
#include "engine/window/window.h"
#include "menus/digiconvert/digiconvert_data.h"
#include "menus/widgets/scroll_bar.h"
#include "menus/widgets/text_list.h"

/* Loads the Digiconvert screen's fonts. */
void func_0205f630(void) {
    func_020a9ae0(1, 2, 0xF);
    func_020a9ae0(2, 4, 0xF);
    func_020a9ae0(4, 7, 0xF);
    func_020a9ae0(5, 8, 0xF);
    func_020a9c40(1, 3, 0xF);
    func_020a9c40(2, 5, 0xF);
    func_020a9c40(3, 6, 0xF);
}

/* Frees the Digiconvert screen's fonts. */
void func_0205f5e8(void) {
    func_020a9844(1);
    func_020a9844(2);
    func_020a9844(4);
    func_020a9844(5);
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a98a8(3);
}

/* Opens an 18 by 18 window at x, y. */
void func_0205f588(s16 x, s16 y) {
    struct WindowParams params;

    params.x        = x;
    params.flags    = 0;
    params.y        = y;
    params.gfxSlot  = 0;
    params.unk8     = 0;
    params.unkA     = 0;
    params.width    = 18;
    params.height   = 18;
    params.unk10    = 0;
    params.unk12    = 0;
    params.unk14    = 0xFFFF;
    params.unk16    = 0xFFFF;
    params.unk18    = 0xFFFF;
    params.callback = NULL;
    func_020a91c4(&params);
}

/* Opens a 26 by 8 window at x, y. */
void func_0205f51c(s16 x, s16 y) {
    struct WindowParams params;

    params.x        = x;
    params.flags    = 0;
    params.y        = y;
    params.gfxSlot  = 0;
    params.unk8     = 17;
    params.unkA     = 20;
    params.width    = 26;
    params.height   = 8;
    params.unk10    = 0;
    params.unk12    = 0;
    params.unk14    = 0xFFFF;
    params.unk16    = 0xFFFF;
    params.unk18    = 0xFFFF;
    params.callback = NULL;
    func_020a91c4(&params);
}

/* Opens a 26 by 4 window at x, y. */
void func_0205f4b0(s16 x, s16 y) {
    struct WindowParams params;

    params.x        = x;
    params.flags    = 0;
    params.y        = y;
    params.gfxSlot  = 0;
    params.unk8     = 17;
    params.unkA     = 28;
    params.width    = 26;
    params.height   = 4;
    params.unk10    = 0;
    params.unk12    = 0;
    params.unk14    = 0xFFFF;
    params.unk16    = 0xFFFF;
    params.unk18    = 0xFFFF;
    params.callback = NULL;
    func_020a91c4(&params);
}

/* Makes the Digiconvert screen's openDial object on its order. */
void func_0205f364(struct Digiconvert *digiconvert) {
    s16 params[8];

    params[0]          = 4;
    params[1]          = 0x92;
    params[2]          = 0x64;
    params[3]          = 0x21;
    params[5]          = 4;
    params[4]          = 0x30;
    params[6]          = digiconvert->order->order;
    digiconvert->unk40 = openDial(params);
}

/* Frees the Digiconvert screen's openDial object. */
void func_0205f348(struct Digiconvert *digiconvert) {
    closeDial(digiconvert->unk40);
    digiconvert->unk40 = -1;
}

/* Makes the list's scroll bar and its sprite. */
void createDigiconvertScrollBar(struct Digiconvert *digiconvert) {
    struct {
        s16 top;
        s16 rows;
        s16 end;
        s16 x;
        s16 y;
        s16 unkA;
        s16 height;
        s16 unkE;
        u32 sprite;
        s16 unk14;
        s16 unk16;
    } params;

    digiconvert->scrollBarSprite = createMainSprite(0x3A1, 0, 0, 5, 0);
    params.top                   = digiconvert->scroll->top;
    params.rows                  = digiconvert->scroll->rows;
    params.end                   = digiconvert->scroll->maxTop + digiconvert->scroll->rows;
    params.x                     = 0xE8;
    params.y                     = 0x10;
    params.unkA                  = 0x10;
    params.height                = 0x80;
    params.sprite                = digiconvert->scrollBarSprite;
    params.unk14                 = 0;
    params.unk16                 = -8;
    digiconvert->scrollBar       = createScrollBar(0, &params);
}

/* Frees the scroll bar and its sprite. */
void freeDigiconvertScrollBar(struct Digiconvert *digiconvert) {
    freeMainSprite(digiconvert->scrollBarSprite);
    closeScrollBar(digiconvert->scrollBar);
    digiconvert->scrollBar = -1;
}

/* Makes the list of names in the order picked and the list of their scan
 * data beside it. */
void createDigiconvertLists(struct Digiconvert *digiconvert) {
    struct {
        void *unk0;
        void *unk4;
        u8 unk8;
        u8 unk9;
        s16 unkA;
        s16 unkC;
        s16 unkE;
        s16 unk10;
        s16 unk12;
        void *unk14;
        s16 unk18;
        s16 unk1A;
        s16 unk1C;
        void *unk20;
        u8 unk24;
        u8 unk25[8];
    } params;
    struct DigiconvertWork *work;
    struct DigiconvertScroll *scroll;
    s32 i;

    if (digiconvert->work->names == NULL) {
        digiconvert->work->names = func_0204bef8();
    }
    switch (digiconvert->order->order + 1) {
        case 1:
            work       = digiconvert->work;
            work->list = work->lists[0];
            break;
        case 4:
            work       = digiconvert->work;
            work->list = work->lists[1];
            break;
        case 3:
            work       = digiconvert->work;
            work->list = work->lists[2];
            break;
        case 2:
            work       = digiconvert->work;
            work->list = work->lists[3];
            break;
        case 0:
            work       = digiconvert->work;
            work->list = work->lists[4];
            break;
    }
    digiconvert->scroll->rows = 8;
    scroll                    = digiconvert->scroll;
    scroll->maxTop            = countListedSpecies() - scroll->rows;
    params.unk8               = 2;
    params.unk9               = 9;
    params.unkA               = 1;
    params.unkC               = 1;
    params.unk0               = digiconvert->work->names;
    params.unk4               = digiconvert->work->list;
    params.unkE               = -1;
    params.unk10              = digiconvert->scroll->rows;
    params.unk12              = digiconvert->scroll->maxTop + digiconvert->scroll->rows;
    params.unk14              = data_021168a0;
    params.unk1C              = digiconvert->scroll->top;
    params.unk24              = digiconvert->windows[1];
    params.unk18              = 0;
    params.unk1A              = 0;
    params.unk20              = digiconvert->work->nameRows;
    for (i = 0; i < 8; i++) {
        params.unk25[i] = 0;
    }
    digiconvert->nameList = createTextList(&params);
    makeScanTexts(digiconvert->work->scanTexts, digiconvert->work->list, digiconvert->scroll->top);
    for (i = 0; i < 8; i++) {
        digiconvert->work->scanRows[i] = i;
    }
    params.unk8  = 2;
    params.unk9  = 5;
    params.unkA  = 0x91;
    params.unkC  = 3;
    params.unk0  = digiconvert->work->scanTexts;
    params.unk4  = digiconvert->work->scanRows;
    params.unkE  = -1;
    params.unk1C = 0;
    params.unk10 = 8;
    params.unk14 = data_021168c0;
    params.unk12 = 8;
    params.unk24 = digiconvert->windows[1];
    params.unk18 = 0;
    params.unk1A = 1;
    params.unk20 = digiconvert->work->scanRowsList;
    for (i = 0; i < 8; i++) {
        params.unk25[i] = 0;
    }
    digiconvert->scanList = createTextList(&params);
}

/* Frees the names and both lists. */
void freeDigiconvertLists(struct Digiconvert *digiconvert) {
    void *names;

    names = digiconvert->work->names;
    heapFree(names);
    digiconvert->work->names = NULL;
    closeTextList(digiconvert->nameList);
    digiconvert->nameList = -1;
    closeTextList(digiconvert->scanList);
    digiconvert->scanList = -1;
}
