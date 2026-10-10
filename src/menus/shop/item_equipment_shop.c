#include "menus/shop/item_equipment_shop.h"
#include "battle/sprite_slots.h"
#include "battle/unit_panels.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/print_text.h"
#include "engine/text/text_banks.h"
#include "engine/text/text_object.h"
#include "engine/text/window_text.h"
#include "engine/ui/digimon_list.h"
#include "engine/window/window.h"
#include "engine/window/window_draw.h"
#include "field/actors/actor_commands.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_facing.h"
#include "field/actors/actor_files.h"
#include "field/actors/actor_tasks.h"
#include "menus/experience/experience_screen.h"
#include "menus/shop/farm_shops.h"
#include "menus/shop/shop.h"
#include "menus/shop/shop_ui.h"
#include "menus/widgets/item_displays.h"
#include "menus/widgets/menu_displays.h"
#include "menus/widgets/window_anim.h"
#include "nitro/pad.h"

/* Whether the player backs out: B, or a touch of the back button (sprite 0). */
s32 isShopBackPressed(void) {
    if ((getPadPressed() & PAD_BUTTON_B) || (isSpriteTapped(0) == 1)) {
        return 1;
    }
    return 0;
}

/* Draws label index (func_0209ec68) in a window of its own on background 2. */
void func_020d5108(s32 index) {
    struct TextWindow window;

    window.unk4   = 0;
    window.unk6   = 0xF;
    window.unkA   = 0xFFFF;
    window.font   = 2;
    window.width  = 0x14;
    window.height = 4;
    window.unk1C  = (void *) -1;
    window.unk20  = (void *) -1;
    window.flags  = 0x80;
    func_020a6b10(&window);
    func_020a5338(&window, func_0209ec68(index), 0, 9999);
    func_020a5d1c(0xB, 2, &window);
    freeWindowImage(&window);
}

/* The equipment shop (modes 0 and 1): runs its state. */
void runEquipmentShop(struct Shop *shop) {
    switch (shop->state) {
        case 0:
            func_020d4c18(shop);
            break;
        case 1:
            func_020d4b1c(shop);
            break;
        case 2:
            func_020d4990(shop);
            break;
        case 3:
            func_020d44e4(shop);
            break;
        case 4:
            func_020d4314(shop);
            break;
        case 5:
            func_020d4000(shop);
            break;
        case 6:
            func_020d3e64(shop);
            break;
    }
}

/* The equipment shop's fade in, then its menu (state 2). */
void func_020d4b1c(struct Shop *shop) {
    switch (shop->step) {
        case 0:
            shop->timer = SHOP_FADE_FRAMES;
            showMainLayers(0x1F);
            fadeInMainPalette(0, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeInMainPalette(0x900, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeInMainPalette(0xA00, 0x800, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            shop->step++;
            return;
        case 1:
            shop->timer--;
            if (shop->timer <= 0) {
                shop->choice = 0;
                shop->state  = 2;
            }
            return;
    }
}

/* The equipment shop's last state: fades out, takes the shop down and ends its
 * task. */
void func_020d3e64(struct Shop *shop) {
    s32 i;
    struct ShopBg *bg;

    switch (shop->step) {
        case 0:
            shop->timer = SHOP_FADE_FRAMES;
            fadeOutMainPalette(0, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeOutMainPalette(0x900, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeOutMainPalette(0xA00, 0x800, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            shop->step++;
            break;
        case 1:
            shop->timer--;
            if (shop->timer > 0) {
                break;
            }
            deleteMainActors();
            endMainActorTask();
            unloadMainWindowFrame();
            closeWindow(shop->unk25);
            releaseMenuDisplays();
            releaseGfxSlot(shop->unk22);
            closeWindow(shop->window);
            if (data_021f5d08.chars != 0xFFFF) {
                freeShopBg(&data_021f5d08);
            }
            bg = &SHOP_BGS[SHOP_BG_COUNT - 1];
            for (i = SHOP_BG_COUNT - 1; i >= 0; i--) {
                if (bg->chars != 0xFFFF) {
                    freeShopBg(bg);
                }
                bg--;
            }
            for (i = 0xFF; i >= 0; i--) {
                releaseSlotSprite(i);
            }
            func_020a98a8(2);
            func_020a9844(2);
            func_0207e6bc(1);
            endTask(getCurrentTask());
            shop->state = 7;
            break;
    }
}

/* Puts the equipment list data_021f6018 (func_020d324c) in the shop's list and
 * returns its count. */
s32 func_020d31ec(void) {
    s32 i;
    struct ShopEntryBytes *dst = (struct ShopEntryBytes *) SHOP_LIST;
    struct ShopEntryBytes *src = (struct ShopEntryBytes *) data_021f6018;

    for (i = 0; i < SHOP_EQUIPMENT_LIST_A; i++, dst++, src++) {
        *dst = *src;
    }
    return SHOP_EQUIPMENT_LIST_A;
}

/* Puts the equipment list data_021f6148 (func_020d324c) in the shop's list and
 * returns its count. */
s32 func_020d3188(void) {
    struct ShopEntryBytes *dst = (struct ShopEntryBytes *) SHOP_LIST;
    struct ShopEntryBytes *src = (struct ShopEntryBytes *) data_021f6148;
    s32 i;

    func_0207e694();
    for (i = 0; i < SHOP_EQUIPMENT_LIST_B; i++, dst++, src++) {
        *dst = *src;
    }
    return SHOP_EQUIPMENT_LIST_B;
}

/* Puts the first or the second equipment shop's list in the shop's list and
 * returns its count. */
s32 func_020d3114(void) {
    s32 i;
    struct ShopEntryBytes *dst = (struct ShopEntryBytes *) SHOP_LIST;
    struct ShopEntryBytes *src;
    s32 count;

    if (func_0207e694() == 0) {
        src   = (struct ShopEntryBytes *) data_021f68c8;
        count = SHOP_EQUIPMENT_LIST_C;
    } else {
        src   = (struct ShopEntryBytes *) data_021f6a18;
        count = SHOP_EQUIPMENT_LIST_D;
    }
    for (i = 0; i < count; i++, dst++, src++) {
        *dst = *src;
    }
    return count;
}

/* Has each Digimon shown in the shop take a pose for a piece of equipment:
 * SHOP_CAN_EQUIP_ANIMATION when its level and kind let it equip it, else
 * ACTOR_ANIM_DOWN. */
void showWhoCanEquip(s32 item, struct Shop *shop) {
    struct Digimon *digimon;
    s32 i;
    u8 count;
    struct Actor *actor;
    u8 *equipment;

    equipment = func_020a142c(item);
    count     = 0;
    for (i = 0; i < SHOP_DIGIMON_COUNT; i++) {
        if (data_021f5cf0[i] != 0) {
            digimon = getDigimon(data_021f5cf0[i]);
            actor   = getMainActor(shop->actors[count]);
            if (equipment[EQUIPMENT_LEVEL] <= digimon->level &&
                (equipment[EQUIPMENT_KIND] == EQUIPMENT_ANY_KIND || equipment[EQUIPMENT_KIND] == digimon->unk1A)) {
                if (actor->animation != SHOP_CAN_EQUIP_ANIMATION) {
                    fixMainActorFacing(shop->actors[count]);
                    setActorAnimation(actor, SHOP_CAN_EQUIP_ANIMATION);
                }
            } else if (actor->animation != ACTOR_ANIM_DOWN) {
                fixMainActorFacing(shop->actors[count]);
                setActorAnimation(actor, ACTOR_ANIM_DOWN);
            }
            count++;
        }
    }
}

/* How many of a piece of equipment the third equipment stock holds. */
u8 func_020d2b20(s32 item) {
    s32 i;
    u8 count;
    struct EquipSlot *slot;

    count = 0;
    slot  = WEAPON_STOCK;
    for (i = 0; i < EQUIP_STOCK_SIZE; i++, slot++) {
        if (slot->id != 0 && slot->id != -1 && slot->item == item) {
            count++;
        }
    }
    return count;
}

/* How many of a piece of equipment the second equipment stock holds. */
u8 func_020d2ac4(s32 item) {
    s32 i;
    u8 count;
    struct EquipSlot *slot;

    count = 0;
    slot  = ARMOR_STOCK;
    for (i = 0; i < EQUIP_STOCK_SIZE; i++, slot++) {
        if (slot->id != 0 && slot->id != -1 && slot->item == item) {
            count++;
        }
    }
    return count;
}

/* How many of a piece of equipment the first equipment stock holds. */
u8 func_020d2a68(s32 item) {
    s32 i;
    u8 count;
    struct EquipSlot *slot;

    count = 0;
    slot  = ACCESSORY_STOCK;
    for (i = 0; i < EQUIP_STOCK_SIZE; i++, slot++) {
        if (slot->id != 0 && slot->id != -1 && slot->item == item) {
            count++;
        }
    }
    return count;
}

/* Has each Digimon shown in the shop take an animation. */
void setShopDigimonAnimation(s16 animation, struct Shop *shop) {
    s32 i;
    u8 count;
    struct Actor *actor;

    count = 0;
    for (i = 0; i < SHOP_DIGIMON_COUNT; i++) {
        if (data_021f5cf0[i] != 0) {
            actor = getMainActor(shop->actors[count]);
            if (actor->animation != animation) {
                fixMainActorFacing(shop->actors[count]);
                setActorAnimation(actor, animation);
            }
            count++;
        }
    }
}

/* Shows func_02052c00's display of a piece of equipment in window unk25. */
void func_020d2980(s16 item, struct Shop *shop) {
    struct Params02052c00 params;

    params.item   = item;
    params.window = shop->unk25;
    params.x      = 0;
    params.y      = 0;
    params.unk8   = 2;
    params.unkA   = 3;
    params.unkC   = 0;
    params.unkE   = SHOP_BGS[1].chars + 0x50;
    params.unk10  = 2;
    params.unk12  = 0;
    func_02052c00(0, &params);
    shop->unk2E = 1;
}

/* Takes down func_020d2980's display and clears its window. */
void func_020d2910(struct Shop *shop) {
    freeEquipmentDisplaySprites(0);
    closeEquipmentDisplay(0);
    freeTextBank();
    func_020a8a98(shop->unk25, 0, 0, 0xD, 0x10, 0);
    func_020867fc(0, 0x12, 7, 0xD, 0x10, 0);
    shop->unk2E = 0;
}

/* Clears what func_020d0f30 wrote. */
void func_020d27cc(struct Shop *shop) {
    func_020d0ef8(shop);
}

/* The item shop (modes 2 and 3): runs its state. */
void runItemShop(struct Shop *shop) {
    switch (shop->state) {
        case 0:
            func_020d2354(shop);
            break;
        case 1:
            func_020d2258(shop);
            break;
        case 2:
            func_020d1ffc(shop);
            break;
        case 3:
            func_020d1c38(shop);
            break;
        case 4:
            func_020d1760(shop);
            break;
        case 5:
            func_020d1478(shop);
            break;
        case 6:
            func_020d12dc(shop);
            break;
    }
}

/* The item shop's fade in, then its menu (state 2). */
void func_020d2258(struct Shop *shop) {
    switch (shop->step) {
        case 0:
            shop->timer = SHOP_FADE_FRAMES;
            showMainLayers(0x1F);
            fadeInMainPalette(0, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeInMainPalette(0x900, 0x100, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            fadeInMainPalette(0xA00, 0x800, 0, 0, SHOP_FADE_FRAMES / shop->timer);
            shop->step++;
            return;
        case 1:
            shop->timer--;
            if (shop->timer <= 0) {
                shop->choice = 0;
                shop->state  = 2;
            }
            return;
    }
}
