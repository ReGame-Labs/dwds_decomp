#include "menus/widgets/item_displays.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/text/text_object.h"
#include "items/inventory_queries.h"
#include "menus/widgets/text_list.h"

/* Frees the equipment display's images and empties it. */
void closeEquipmentDisplay(s16 index) {
    struct EquipmentDisplay *display = &EQUIPMENT_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->images[0].width != 0 && display->images[0].height != 0) {
        freeWindowImage(&display->images[0]);
        func_02030f18(&display->images[0], 0, sizeof(struct WindowImage));
    }
    if (display->images[1].width != 0 && display->images[1].height != 0) {
        freeWindowImage(&display->images[1]);
        func_02030f18(&display->images[1], 0, sizeof(struct WindowImage));
    }
    if (display->images[2].width != 0 && display->images[2].height != 0) {
        freeWindowImage(&display->images[2]);
        func_02030f18(&display->images[2], 0, sizeof(struct WindowImage));
    }
    func_02030f18(display, 0, sizeof(struct EquipmentDisplay));
}

/* Frees the equipment display's sprites. */
void freeEquipmentDisplaySprites(s16 index) {
    struct EquipmentDisplay *display = &EQUIPMENT_DISPLAY[index];
    s32 i;

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        for (i = 0; i < 2; i++) {
            freeSubSprite(display->sprites[i]);
        }
    } else {
        for (i = 0; i < 2; i++) {
            freeMainSprite(display->sprites[i]);
        }
    }
}

/* Sets the equipment display's unk6 and has it drawn again. */
void func_02052a98(s16 index, s16 value) {
    struct EquipmentDisplay *display = &EQUIPMENT_DISPLAY[index];

    if (display->flags & PANEL_IN_USE) {
        display->flags |= PANEL_CHANGED;
        display->unk6 = value;
    }
}

/* Empties the equipped display. */
void closeEquippedDisplay(s16 index) {
    struct EquippedDisplay *display = &EQUIPPED_DISPLAY[index];

    if (display->flags & PANEL_IN_USE) {
        func_02030f18(display, 0, sizeof(struct EquippedDisplay));
    }
}

/* Frees the equipped display's sprites. */
void freeEquippedDisplaySprites(s16 index) {
    struct EquippedDisplay *display = &EQUIPPED_DISPLAY[index];
    s32 i;

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        freeSubSprite(display->sprite);
        for (i = 0; i < 3; i++) {
            freeSubSprite(display->sprites[i]);
            freeSubSprite(display->sprites2[i]);
        }
    } else {
        freeMainSprite(display->sprite);
        for (i = 0; i < 3; i++) {
            freeMainSprite(display->sprites[i]);
            freeMainSprite(display->sprites2[i]);
        }
    }
}

/* Sets the equipped display's unk8 and has it drawn again. */
void func_02051dd8(s16 index, s32 value) {
    struct EquippedDisplay *display = &EQUIPPED_DISPLAY[index];

    if (display->flags & PANEL_IN_USE) {
        display->flags |= PANEL_CHANGED;
        display->unk8 = value;
    }
}

/* Frees the item record display's images and empties it. */
void closeItemRecordDisplay(s16 index) {
    struct ItemRecordDisplay *display = &ITEM_RECORD_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->images[0].width != 0 && display->images[0].height != 0) {
        freeWindowImage(&display->images[0]);
        func_02030f18(&display->images[0], 0, sizeof(struct WindowImage));
    }
    if (display->images[1].width != 0 && display->images[1].height != 0) {
        freeWindowImage(&display->images[1]);
        func_02030f18(&display->images[1], 0, sizeof(struct WindowImage));
    }
    func_02030f18(display, 0, sizeof(struct ItemRecordDisplay));
}

/* Frees the item record display's sprites. */
void freeItemRecordDisplaySprites(s16 index) {
    struct ItemRecordDisplay *display = &ITEM_RECORD_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        freeSubSprite(display->sprite);
        freeSubSprite(display->sprite2);
        freeSubSprite(display->sprite3);
    } else {
        freeMainSprite(display->sprite);
        freeMainSprite(display->sprite2);
        freeMainSprite(display->sprite3);
    }
}

/* Sets the item record display's unkA and has it drawn again. */
void func_02050edc(s16 index, s16 value) {
    struct ItemRecordDisplay *display = &ITEM_RECORD_DISPLAY[index];

    if (display->flags & PANEL_IN_USE) {
        display->flags |= PANEL_CHANGED;
        display->unkA = value;
    }
}

/* Closes the bag display's text lists and empties it. */
void closeBagDisplay(s16 index) {
    struct BagDisplay *display = &BAG_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    closeTextList(display->textList);
    closeTextList(display->textList2);
    func_02030f18(display, 0, sizeof(struct BagDisplay));
}

/* Frees the bag display's sprites. */
void freeBagDisplaySprites(s16 index) {
    struct BagDisplay *display = &BAG_DISPLAY[index];
    s32 i;

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        for (i = 0; i < 6; i++) {
            freeSubSprite(display->sprites[i]);
            freeSubSprite(display->sprites2[i]);
        }
    } else {
        for (i = 0; i < 6; i++) {
            freeMainSprite(display->sprites[i]);
            freeMainSprite(display->sprites2[i]);
        }
    }
}

/* The bag display's unk324, NULL if it is not in use. */
u8 *func_020501f4(s16 index) {
    struct BagDisplay *display = &BAG_DISPLAY[index];

    if (display->flags & PANEL_IN_USE) {
        return display->unk324;
    }
    return NULL;
}

/* Frees the item name display's images and empties it. */
void closeItemNameDisplay(s16 index) {
    struct ItemNameDisplay *display = &ITEM_NAME_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->images[0].width != 0 && display->images[0].height != 0) {
        freeWindowImage(&display->images[0]);
        func_02030f18(&display->images[0], 0, sizeof(struct WindowImage));
    }
    if (display->images[1].width != 0 && display->images[1].height != 0) {
        freeWindowImage(&display->images[1]);
        func_02030f18(&display->images[1], 0, sizeof(struct WindowImage));
    }
    func_02030f18(display, 0, sizeof(struct ItemNameDisplay));
}

/* Frees the item name display's sprite. */
void freeItemNameDisplaySprite(s16 index) {
    struct ItemNameDisplay *display = &ITEM_NAME_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        freeSubSprite(display->sprite);
    } else {
        freeMainSprite(display->sprite);
    }
}

/* Sets the item name display's unk6 and has it drawn again. */
void func_0204f8c8(s16 index, s16 value) {
    struct ItemNameDisplay *display = &ITEM_NAME_DISPLAY[index];

    if (display->flags & PANEL_IN_USE) {
        display->flags |= PANEL_CHANGED;
        display->unk6 = value;
    }
}

/* Closes the key item display's text list and empties it. */
void closeKeyItemDisplay(s16 index) {
    struct KeyItemDisplay *display = &KEY_ITEM_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    closeTextList(display->textList);
    func_02030f18(display, 0, sizeof(struct KeyItemDisplay));
}

/* Frees the key item display's sprites. */
void freeKeyItemDisplaySprites(s16 index) {
    struct KeyItemDisplay *display = &KEY_ITEM_DISPLAY[index];
    s32 i;

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    if (display->screenFlags & PANEL_ON_SUB_SCREEN) {
        for (i = 0; i < 6; i++) {
            freeSubSprite(display->sprites[i]);
        }
    } else {
        for (i = 0; i < 6; i++) {
            freeMainSprite(display->sprites[i]);
        }
    }
}

/* Lists the key items again (func_0205c164) and has the display drawn again.
 * Both modes do the same. */
void refreshKeyItemDisplay(s16 index, s32 mode, s16 value) {
    struct KeyItemDisplay *display = &KEY_ITEM_DISPLAY[index];

    if (!(display->flags & PANEL_IN_USE)) {
        return;
    }
    display->flags |= PANEL_CHANGED;
    switch (mode) {
        case 0:
            display->count = func_0205c164(display->list, &KEY_ITEMS);
            break;
        case 1:
            display->count = func_0205c164(display->list, &KEY_ITEMS);
            break;
    }
    display->unk52 = value;
}

/* The key item display's list, NULL if it is not in use. */
u8 *getKeyItemDisplayList(s16 index) {
    struct KeyItemDisplay *display = &KEY_ITEM_DISPLAY[index];

    if (display->flags & PANEL_IN_USE) {
        return display->list;
    }
    return NULL;
}
