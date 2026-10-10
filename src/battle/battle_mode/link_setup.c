#include "battle/battle_mode/link_setup.h"
#include "battle/battle_mode/battle.h"
#include "battle/battle_mode/data.h"
#include "battle/battle_state.h"
#include "battle/characters/chr.h"
#include "battle/characters/chr_draw.h"
#include "battle/exp_level_up.h"
#include "battle/link_party.h"
#include "battle/sprite_slots.h"
#include "battle/unit_panel_draw.h"
#include "battle/unit_panels.h"
#include "engine/bg/bg_layers.h"
#include "engine/bg/bg_screen.h"
#include "engine/digimon/game_data.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display.h"
#include "engine/system/display_modes.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/print_text.h"
#include "engine/text/text_banks.h"
#include "engine/text/text_object.h"
#include "engine/text/window_text.h"
#include "engine/ui/digimon_list.h"
#include "engine/window/message_box.h"
#include "engine/window/window.h"
#include "items/inventory.h"
#include "link/link_screen.h"
#include "link/link_session.h"
#include "link/link_transfer.h"
#include "link/wifi.h"
#include "menus/widgets/menu_displays.h"
#include "menus/widgets/status_window.h"
#include "menus/widgets/window_anim.h"
#include "nitro/fs.h"
#include "nitro/g2d.h"
#include "nitro/pad.h"

/* Runs the link battle's preparation. While the link holds, the packets from
 * the other DS are read before the state runs and this DS's are sent after;
 * once it is lost, the state that waits on the other DS gives up. */
void tickLinkSetupTask(void) {
    struct LinkSetupTask *task = (struct LinkSetupTask *) getCurrentTask();
    s32 link                   = func_02071b5c();

    if (task->linkLost == 0) {
        if (link == 3) {
            if (task->state < LINK_SETUP_CLOSE_OPTIONS) {
                func_02071b4c();
            }
            task->linkLost = 1;
        }
    } else if (task->linkLost == 1) {
        if (task->state == LINK_SETUP_ARRANGE_PARTY || task->state == LINK_SETUP_WAIT_PARTY) {
            task->linkLost = 2;
            task->state    = LINK_SETUP_PARTY_LINK_LOST;
            task->step     = 0;
        } else if (task->state == LINK_SETUP_CHOOSE_OPTION || task->state == LINK_SETUP_WAIT_OPTION) {
            task->linkLost = 2;
            task->state    = LINK_SETUP_OPTION_LINK_LOST;
            task->step     = 0;
        }
    }
    if (task->linkLost == 0) {
        task->packetType = func_ov002_02253fec(task);
    }
    switch (task->state) {
        case LINK_SETUP_INIT_PARTY:
            func_ov002_02253754(task);
            data_ov002_0225a5c0 = 0;
            break;
        case LINK_SETUP_SHOW_PARTY:
            func_ov002_02253624(task);
            break;
        case LINK_SETUP_ARRANGE_PARTY:
            func_ov002_02253204(task);
            break;
        case LINK_SETUP_WAIT_PARTY:
            func_ov002_02252b44(task);
            break;
        case LINK_SETUP_PARTY_LINK_LOST:
            func_ov002_02252aa8(task);
            break;
        case LINK_SETUP_CLOSE_PARTY:
            func_ov002_02252808(task);
            break;
        case LINK_SETUP_INIT_OPTIONS:
            func_ov002_022521bc(task);
            break;
        case LINK_SETUP_SHOW_OPTIONS:
            func_ov002_0225209c(task);
            break;
        case LINK_SETUP_CHOOSE_OPTION:
            func_ov002_02251ec8(task);
            break;
        case LINK_SETUP_WAIT_OPTION:
            func_ov002_02251e18(task);
            break;
        case LINK_SETUP_OPTION_LINK_LOST:
            func_ov002_02251d7c(task);
            break;
        case LINK_SETUP_CLOSE_OPTIONS:
            func_ov002_02251b2c(task);
            break;
        case LINK_SETUP_END:
            func_ov002_02251910(task);
            endTask((void *) getCurrentTask());
            break;
    }
    if (task->state <= LINK_SETUP_CLOSE_PARTY) {
        func_ov002_02252d48(task);
    }
    if (task->state <= LINK_SETUP_CLOSE_PARTY) {
        updateUnitPanels();
    }
    updateSpriteSlots();
    func_ov002_02253f0c(task);
}

/* Copies what a packet from the other DS carries into the buffer its type
 * names, and returns the type. */
u8 func_ov002_02253fec(struct LinkSetupTask *task) {
    s32 aid;
    struct LinkPacket *packet;

    if (func_020b65a0() == 1) {
        aid = 1;
    } else {
        aid = 0;
    }
    packet = (struct LinkPacket *) getReceivedPacket(aid);
    switch (packet->type) {
        case LINK_PACKET_SETUP_STATUS:
            func_02030f78(task->otherStatus + packet->offset, packet->data, packet->size);
            break;
        case LINK_PACKET_SETUP_PARTY:
            func_02030f78((u8 *) task->otherPartyData + packet->offset, packet->data, packet->size);
            task->received = 1;
            break;
        case LINK_PACKET_SETUP_OPTION:
            func_02030f78(task->otherOption + packet->offset, packet->data, packet->size);
            task->received = 2;
            break;
    }
    return packet->type;
}

/* Sends the other DS the party or the option once picked, and this DS's
 * state otherwise, when the last send is done. */
void func_ov002_02253f0c(struct LinkSetupTask *task) {
    if (isLinkTransferBusy() != 0) {
        return;
    }
    if (task->send == 0) {
        task->status[0] = task->state;
        if (task->state < LINK_SETUP_INIT_OPTIONS) {
            task->status[1] = LINK_SETUP_ARRANGING;
        } else {
            task->status[1] = LINK_SETUP_CHOOSING;
        }
        if (task->packetType == LINK_PACKET_SETUP_STATUS) {
            if (task->received == 1) {
                task->status[1] = LINK_SETUP_HAS_PARTY;
            } else if (task->received == 2) {
                task->status[1] = LINK_SETUP_HAS_OPTION;
            }
        }
        startLinkTransfer((s32) task->status, 2, LINK_PACKET_SETUP_STATUS);
    } else if (task->send == 1) {
        startLinkTransfer((s32) task->partyData, sizeof(struct LinkParty), LINK_PACKET_SETUP_PARTY);
        task->send = 0;
    } else if (task->send == 2) {
        startLinkTransfer((s32) task->option, 1, LINK_PACKET_SETUP_OPTION);
        task->send = 0;
    }
}

/* Copies a layout's setup into a text window, as copyWindowLayout does. */
void copyLinkWindowLayout(struct WindowLayout *layout, struct TextWindow *window) {
    window->unk4   = layout->window.unk4;
    window->unkA   = layout->window.unkA;
    window->font   = layout->window.font;
    window->width  = layout->window.width;
    window->height = layout->window.height;
    window->unk1C  = layout->window.unk1C;
    window->unk20  = layout->window.unk20;
    window->flags  = layout->window.flags;
}

/* Shows the screens and fades the party in. */
void func_ov002_02253624(struct LinkSetupTask *task) {
    switch (task->step) {
        case 0:
            unlockMainPalettes();
            unlockSubPalettes();
            showMainLayers(0x1F);
            showSubLayers(0x1F);
            task->wait = 30;
            fadeInMainPalette(0, 0x100, 0, 0, 4);
            fadeInMainPalette(0x900, 0x100, 0, 0, 4);
            fadeInMainPalette(0xA00, 0x800, 0, 0, 4);
            fadeInSubPalette(0, 0x100, 0, 0, 4);
            fadeInSubPalette(0x900, 0x100, 0, 0, 4);
            fadeInSubPalette(0xA00, 0x800, 0, 0, 4);
            task->step++;
            break;
        case 1:
            task->wait--;
            if (task->wait <= 0) {
                task->state = LINK_SETUP_ARRANGE_PARTY;
                task->step  = 0;
            }
            break;
    }
}

/* Lets the player arrange the party: the cursor moves over the five slots
 * that battle and the three below, X picks a Digimon up and puts it down
 * again, swapping it with the one there, and A sends the party. */
void func_ov002_02253204(struct LinkSetupTask *task) {
    struct Digimon *digimon;
    s32 i;
    s32 id;
    s32 action;
    u8 oldCursor;
    u8 touched;
    u8 count; /* also the sprite slot when the party is drawn again; two variables change the registers */
    BOOL moved;

    if (data_ov002_0225a5c0 != 0) {
        data_ov002_0225a5c0--;
    }
    if (task->step == 0) {
        oldCursor = task->cursor;
        action    = 0;
        if ((getTouchedRects(data_ov002_0225a5c4, 1) >> 8) != 0xFF) {
            action = 1;
        }
        if (getPadPressed() & PAD_BUTTON_A) {
            data_ov002_0225a5c0 = 0;
            action              = 1;
        } else if (getPadPressed() & PAD_BUTTON_B) {
            data_ov002_0225a5c0 = 0;
            action              = 2;
        } else if (getPadPressed() & PAD_BUTTON_X) {
            action = 3;
        } else {
            touched = getTouchedRects(data_ov002_0225a710, 8);
            if (touched != 0xFF) {
                task->cursor = touched;
            }
            if (getPadPressed() & PAD_KEY_UP) {
                if (task->cursor >= 5) {
                    task->cursor -= 3;
                }
            }
            if (getPadPressed() & PAD_KEY_DOWN) {
                if (task->cursor <= 2) {
                    task->cursor = 5;
                } else if (task->cursor < 5) {
                    task->cursor += 3;
                }
            }
            if (getPadPressed() & PAD_KEY_LEFT) {
                if (task->cursor != 0) {
                    if (task->cursor == 5) {
                        task->cursor = 1;
                    } else {
                        task->cursor--;
                    }
                }
            }
            if (getPadPressed() & PAD_KEY_RIGHT) {
                if (task->cursor != 4 && task->cursor != 7) {
                    task->cursor++;
                }
            }
        }
        if (action == 1) {
            func_ov002_02252f00();
            func_020a1160(task->party);
            func_ov002_02253068(task);
            openFarmMessage(0xE2, 0, -1, 0xE, 0xF, 6);
            task->state = LINK_SETUP_WAIT_PARTY;
            task->step  = 0;
        } else if (action == 2) {
            /* B does nothing on this screen. */
        } else if (action == 3) {
            if (data_ov002_0225a5c0 == 0) {
                data_ov002_0225a5c0 = 20;
                if (task->holding == 0) {
                    if (task->party[task->cursor] != 0) {
                        task->holding = 1;
                        task->held    = task->cursor;
                        task->flash   = 0;
                    }
                } else {
                    moved = FALSE;
                    if (task->party[task->cursor] == 0) {
                        /* Onto an empty slot: only among the five that
                         * battle, and not to leave fewer than three there. */
                        if (task->cursor < LINK_BATTLE_SLOT_COUNT) {
                            count = 0;
                            for (i = 0; i < LINK_BATTLE_SLOT_COUNT; i++) {
                                if (task->party[i] != 0) {
                                    count++;
                                }
                            }
                            if (task->held < LINK_BATTLE_SLOT_COUNT || count < 3) {
                                task->party[task->cursor] = task->party[task->held];
                                task->party[task->held]   = 0;
                                moved                     = TRUE;
                            }
                        }
                    } else if (task->held < LINK_BATTLE_SLOT_COUNT ||
                               (task->held >= LINK_BATTLE_SLOT_COUNT && task->cursor < LINK_BATTLE_SLOT_COUNT)) {
                        id                        = task->party[task->cursor];
                        task->party[task->cursor] = task->party[task->held];
                        task->party[task->held]   = id;
                        if (task->cursor != task->held) {
                            moved = TRUE;
                        } else {
                            task->holding = 0;
                        }
                    }
                    if (moved == TRUE) {
                        count = 0;
                        for (i = 0; i < LINK_PARTY_SLOT_COUNT; i++) {
                            if (task->party[i] != 0) {
                                digimon = getDigimon(task->party[i]);
                                func_0207d920(count);
                                func_0207d404(count, digimon->id, digimon->maxHp, digimon->maxMp);
                                func_0207debc(count);
                                if (i < LINK_BATTLE_SLOT_COUNT) {
                                    func_0207d990(count, i * 0x30 + 8, 0x60);
                                } else {
                                    func_0207d990(count, (i - 5) * 0x30 + 0x68, 0x90);
                                }
                                func_0207d524(count, 2);
                                count++;
                            }
                        }
                        task->holding  = 0;
                        task->showStep = 1;
                    }
                }
            }
        } else if (oldCursor != task->cursor) {
            func_ov002_02252f00();
            func_ov002_02252f44(task->cursor);
            if (task->party[task->cursor] != 0) {
                task->showStep = 1;
            } else if (task->statusShown == 1) {
                func_ov002_02252cf4(task);
            }
        }
    }
    func_ov002_02252bf4(task);
}

/* Fills the party to send with the party's first five slots, each Digimon in
 * them and the items it equips, and blank Digimon after them. */
void func_ov002_02253068(struct LinkSetupTask *task) {
    struct Digimon blank;
    struct EquipSlot *slot;
    s32 i;
    u8 n;

    n = 0;
    for (i = 0; i < LINK_BATTLE_SLOT_COUNT; i++) {
        task->partyData->ids[i] = task->party[i];
        if (task->party[i] != 0) {
            func_02030f78(&task->partyData->digimon[n], getDigimon(task->party[i]), sizeof(struct Digimon));
            slot = findEquippedWeapon(task->party[i]);
            if (slot != NULL) {
                task->partyData->items[0][n] = slot->item;
            } else {
                task->partyData->items[0][n] = 0xFFFF;
            }
            slot = findEquippedArmor(task->party[i]);
            if (slot != NULL) {
                task->partyData->items[1][n] = slot->item;
            } else {
                task->partyData->items[1][n] = 0xFFFF;
            }
            slot = findEquippedAccessory(task->party[i]);
            if (slot != NULL) {
                task->partyData->items[2][n] = slot->item;
            } else {
                task->partyData->items[2][n] = 0xFFFF;
            }
            n++;
        }
    }
    blank.id = 0;
    for (i = n; i < LINK_PARTY_DIGIMON_COUNT; i++) {
        func_02030f78(&task->partyData->digimon[i], &blank, sizeof(struct Digimon));
        task->partyData->items[0][i] = 0xFFFF;
        task->partyData->items[1][i] = 0xFFFF;
        task->partyData->items[2][i] = 0xFFFF;
    }
    task->send = 1;
}

/* Draws the frame around a slot of the party on background 1: the first five
 * slots on one row and the next three under the last three. */
void func_ov002_02252f44(u8 slot) {
    struct BattleBg *bg;
    struct ScreenCopy copy;
    s32 size;
    s16 y;

    func_020867fc(1, 0, 5, 0x20, 0xE, 0);
    bg         = &data_ov002_022624d8;
    bg->unk218 = loadMainBgChars(1, -1, bg->gfx.chars);
    size       = getPaletteSize((s32) bg->gfx.paletteFile, bg->gfx.palette);
    loadMainPalette(0x40, (u16) (size >> 1), (s32) bg->gfx.palette->pRawData);
    copy.bg   = 1;
    copy.unk2 = bg->unk218;
    copy.unk4 = 4;
    if (slot < 5) {
        y = 5;
    } else {
        y = 11;
        slot -= 3;
    }
    copy.x         = slot * 6 + 1;
    copy.y         = y;
    copy.srcX      = 0;
    copy.srcY      = 0;
    copy.width     = 6;
    copy.height    = 8;
    copy.src       = bg->gfx.screen->data;
    copy.srcWidth  = bg->gfx.screen->width / 8;
    copy.srcHeight = bg->gfx.screen->height / 8;
    copyMainBgScreenAndFlush((u8 *) &copy);
    setMainBgOffset(1, 0, 0);
}

/* Takes off what func_ov002_02252f44 draws on background 1. */
void func_ov002_02252f00(void) {
    func_020867fc(1, 0, 5, 0x20, 0xE, 0);
    func_0208577c(1, data_ov002_022624d8.unk218);
}

/* Shows the status of the Digimon under the cursor, then its picture four
 * frames later. */
void func_ov002_02252d48(struct LinkSetupTask *task) {
    struct StatusParams params;
    struct Digimon *digimon;
    struct SpriteOffset *offset;
    s32 chr;

    switch (task->showStep) {
        case 1:
            task->showStep = 2;
            break;
        case 2:
            digimon     = getDigimon(task->party[task->cursor]);
            task->unk40 = digimon->unk4;
            if (task->statusShown == 0) {
                params.window   = task->unk29;
                params.x        = 1;
                params.y        = 5;
                params.unk6     = 1;
                params.unk8     = 1;
                params.digimon  = digimon;
                params.unk10    = 0;
                params.unk12    = 1;
                params.unk14    = 2;
                params.unk16    = 3;
                params.unk18[0] = 0;
                params.unk18[1] = 0;
                params.unk18[2] = 0;
                params.unk18[3] = 0;
                params.unk18[4] = 0;
                params.unk22    = 1;
                params.unk24    = 0;
                params.unk26    = 100;
                params.unk28    = 2;
                params.unk2A    = 3;
                params.unk2C    = 1;
                drawStatusWindow(0, &params);
                task->statusShown = 1;
            } else {
                func_02058590(0, digimon);
                removeSubBattleChr(0);
            }
            task->showStep++;
            task->showWait = 4;
            break;
        case 3:
            if (task->showWait > 0) {
                task->showWait--;
                break;
            }
            chr    = func_020a31d8(task->unk40);
            offset = getSpriteOffset(chr);
            placeSubBattleChr(chr, offset->x + 0xC0, offset->y + offset->y / 2 + 0xB8, 0, 0, 0, 0, 0);
            clearSubBattleChrFlags(0, 0x10);
            setSubBattleChrPriority(0, 3);
            task->showStep = 0;
            break;
    }
}

/* Takes the status and the picture of the Digimon under the cursor off the
 * screen. */
void func_ov002_02252cf4(struct LinkSetupTask *task) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
    func_02086758(0, 1, 8, 0xF, 0x10, 0);
    removeSubBattleChr(0);
    task->statusShown = 0;
}

/* Flashes the palette of the Digimon held, a Digimon's sprite being its place
 * among the party's, and sets it back once the Digimon is let go. */
void func_ov002_02252bf4(struct LinkSetupTask *task) {
    s32 i;
    u8 sprite;
    u16 palette;

    if (task->held == LINK_NOT_HELD) {
        return;
    }
    for (sprite = 0, i = 0; i < task->held; i++) {
        if (task->party[i] != 0) {
            sprite++;
        }
    }
    palette = (sprite + 5) * 16 + 0x900;
    if (task->holding == 0) {
        task->held = LINK_NOT_HELD;
        func_020846bc(palette, 16, 0);
    } else {
        func_020846bc(palette, 16, 14 - (task->flash & ~0x80) / 2);
    }
    markMainPalettesDirty();
    if (task->flash & 0x80) {
        task->flash -= 2;
        if ((task->flash & ~0x80) == 0) {
            task->flash &= ~0x80;
        }
    } else {
        task->flash += 2;
        if (task->flash >= 0x20) {
            task->flash = 0x9C;
        }
    }
}

/* Waits for both DSs to have the other's party, then says so for three
 * seconds. */
void func_ov002_02252b44(struct LinkSetupTask *task) {
    switch (task->step) {
        case 0:
            if (task->status[0] != LINK_SETUP_WAIT_PARTY || task->status[1] != LINK_SETUP_HAS_PARTY) {
                return;
            }
            if (task->otherStatus[0] != LINK_SETUP_WAIT_PARTY || task->otherStatus[1] != LINK_SETUP_HAS_PARTY) {
                return;
            }
            func_020ac650(0xE3, -1, 2);
            task->wait = 180;
            task->step++;
            break;
        case 1:
            task->wait--;
            if (task->wait > 0) {
                return;
            }
            func_020ac6f8();
            task->state = LINK_SETUP_CLOSE_PARTY;
            task->step  = 0;
            break;
    }
}

/* Says the link was lost and waits for the A button. */
void func_ov002_02252aa8(struct LinkSetupTask *task) {
    switch (task->step) {
        case 0:
            openFarmMessage(0xE7, 0, -1, 0xE, 0xF, 6);
            task->step++;
            break;
        case 1:
            if (getPadPressed() & PAD_BUTTON_A) {
                func_020ac6f8();
                task->step++;
            }
            break;
        case 2:
            task->state = LINK_SETUP_CLOSE_PARTY;
            task->step  = 0;
            break;
    }
}

/* Fades the party screen out and takes it down, then goes on to the options
 * or, once the link is lost, ends. */
void func_ov002_02252808(struct LinkSetupTask *task) {
    s32 i;
    struct LinkBg *bg;
    struct BattleBg *data;

    switch (task->step) {
        case 0:
            task->wait = 30;
            fadeOutMainPalette(0, 0x100, 0, 0, 4);
            fadeOutMainPalette(0x900, 0x100, 0, 0, 4);
            fadeOutMainPalette(0xA00, 0x800, 0, 0, 4);
            fadeOutSubPalette(0, 0x100, 0, 0, 4);
            fadeOutSubPalette(0x900, 0x100, 0, 0, 4);
            fadeOutSubPalette(0xA00, 0x800, 0, 0, 4);
            task->step++;
            break;
        case 1:
            task->wait--;
            if (task->wait > 0) {
                break;
            }
            lockMainPalettes();
            lockSubPalettes();
            for (i = 0; i < 6; i++) {
                func_0207d920(i);
            }
            freeUnitPanelTexts();
            freeStatusWindowSprites(0);
            func_020587fc(0);
            unloadSubWindowFrame();
            releaseMenuDisplays();
            closeWindow(task->unk29);
            removeAllSubBattleChrs();
            endBattleChrs();
            freeBattleBgGraphics(&data_ov002_022624d8.gfx);
            for (i = 3; i >= 0; i--) {
                bg = &data_ov002_02262f74[i];
                if (bg->loaded == 1) {
                    data = &bg->data;
                    func_02085710(bg->layer, data->unk218);
                    freeBattleBgGraphics(&data->gfx);
                    func_02086758(bg->layer, 0, 0, 0x20, 0x18, 0);
                    bg->loaded = 0;
                }
            }
            for (i = 3; i >= 0; i--) {
                bg = &data_ov002_022626f4[i];
                if (bg->loaded == 1) {
                    data = &bg->data;
                    func_0208577c(bg->layer, data->unk218);
                    freeBattleBgGraphics(&data->gfx);
                    func_020867fc(bg->layer, 0, 0, 0x20, 0x18, 0);
                    bg->loaded = 0;
                }
            }
            releaseSlotSprite(0x80);
            releaseSlotSprite(0);
            releaseSlotSprite(1);
            stopMainPaletteEffects(task->unk2C);
            stopSubPaletteEffects(task->unk34);
            func_02086758(0, 0, 0, 0x20, 0x20, 0);
            if (task->linkLost == 2) {
                task->result = LINK_FAILED;
                task->state  = LINK_SETUP_END;
            } else {
                task->state = LINK_SETUP_INIT_OPTIONS;
            }
            break;
    }
}

/* Sets up the options screen: its backgrounds on both screens, the sprites
 * of the four options and the window texts. */
void func_ov002_022521bc(struct LinkSetupTask *task) {
    struct ScreenCopy copy;
    struct TextWindow text;
    /* The order of these declarations gives the registers of the first loop. */
    u32 i;
    u8 n;
    u32 colors;
    u32 color;
    struct BattleBg *data;
    struct LinkBgSource *source;
    struct LinkBg *bg;

    setSubBgOffset(0, 0, 0);
    setSubBgOffset(1, 0, 0);
    setSubBgOffset(2, 0, 0);
    setSubBgOffset(3, 0, 0);
    setMainBgOffset(0, 0, 0);
    setMainBgOffset(1, 0, 0);
    setMainBgOffset(2, 0, 0);
    setMainBgOffset(3, 0, 0);
    setMainBgPriorities(0, 1, 2, 3);
    setSubBgPriorities(0, 2, 1, 3);
    color = 0;
    n     = 0;
    for (i = 0; i < 2; i++) {
        bg = &data_ov002_022626f4[i];
        if (bg->loaded == 0) {
            source    = &data_ov002_0225a5ec[n];
            data      = &bg->data;
            bg->layer = source->layer;
            loadBattleBgGraphics(source->file, &data->gfx);
            data->unk218 = loadMainBgChars(bg->layer, -1, data->gfx.chars);
            colors       = getPaletteSize((s32) bg->data.gfx.paletteFile, data->gfx.palette) >> 1;
            loadMainPalette((u16) color, (u16) colors, (s32) data->gfx.palette->pRawData);
            copy.bg        = bg->layer;
            copy.unk2      = data->unk218;
            copy.unk4      = color >> 4;
            copy.x         = source->x;
            copy.y         = source->y;
            copy.srcX      = 0;
            copy.srcY      = 0;
            copy.width     = data->gfx.screen->width / 8;
            copy.height    = data->gfx.screen->height / 8;
            copy.src       = data->gfx.screen->data;
            copy.srcWidth  = data->gfx.screen->width / 8;
            copy.srcHeight = data->gfx.screen->height / 8;
            copyMainBgScreenAndFlush((u8 *) &copy);
            setMainBgOffset(bg->layer, 0, 0);
            n++;
            color += colors;
            bg->loaded = 1;
        }
    }
    task->unk2C = func_02083ea8(1, 0xC, 6, 1, 10000);
    task->unk30 = func_02083ea8(0x11, 8, 6, 1, 10000);
    color       = 0;
    n           = 0;
    for (i = 0; i < 2; i++) {
        bg = &data_ov002_02262f74[i];
        if (bg->loaded == 0) {
            source    = &data_ov002_0225a604[n];
            data      = &bg->data;
            bg->layer = source->layer;
            loadBattleBgGraphics(source->file, &data->gfx);
            data->unk218 = loadSubBgChars(bg->layer, -1, data->gfx.chars);
            colors       = getPaletteSize((s32) bg->data.gfx.paletteFile, data->gfx.palette) >> 1;
            loadSubPalette((u16) color, (u16) colors, (s32) data->gfx.palette->pRawData);
            copy.bg        = bg->layer;
            copy.unk2      = data->unk218;
            copy.unk4      = color >> 4;
            copy.x         = source->x;
            copy.y         = source->y;
            copy.srcX      = 0;
            copy.srcY      = 0;
            copy.width     = data->gfx.screen->width / 8;
            copy.height    = data->gfx.screen->height / 8;
            copy.src       = data->gfx.screen->data;
            copy.srcWidth  = data->gfx.screen->width / 8;
            copy.srcHeight = data->gfx.screen->height / 8;
            copySubBgScreenAndFlush((u8 *) &copy);
            setSubBgOffset(bg->layer, 0, 0);
            n++;
            color += colors;
            bg->loaded = 1;
        }
    }
    task->unk34 = func_02083e78(1, 0xC, 6, 1, 10000);
    task->unk38 = func_02083e78(0x11, 8, 6, 1, 10000);
    queueSlotSprite(0x41B, 0, 8, 0xF, 0, 0x80);
    showSlotSprite(0x80);
    task->cursor = 0;
    queueSlotSprite(0x417, 0x40, 0x10, 3, 0, 2);
    showSlotSprite(2);
    setSlotSpriteAnimation(2, 1);
    setSlotSpritePriority(2, 1);
    queueSlotSprite(0x417, 0x40, 0x30, 3, 0, 3);
    showSlotSprite(3);
    setSlotSpriteAnimation(3, 2);
    setSlotSpritePriority(3, 1);
    queueSlotSprite(0x417, 0x40, 0x50, 3, 0, 4);
    showSlotSprite(4);
    setSlotSpriteAnimation(4, 4);
    setSlotSpritePriority(4, 1);
    queueSlotSprite(0x417, 0x40, 0x70, 3, 0, 5);
    showSlotSprite(5);
    setSlotSpriteAnimation(5, 6);
    setSlotSpritePriority(5, 1);
    queueSlotSprite(0x418, 0x10, 0xA8, 0xD, 0, 1);
    showSlotSprite(1);
    setSlotSpritePriority(1, 1);
    loadTextBank(7);
    copyLinkWindowLayout(&data_ov002_0225a660, &text);
    func_020a6b10(&text);
    func_020a5338(&text, func_0209d6f8(0x3F), 0, 9999);
    func_020a5d1c(data_ov002_0225a660.x, data_ov002_0225a660.y, &text);
    freeWindowImage(&text);
    copyLinkWindowLayout(&data_ov002_0225a68c, &text);
    func_020a6b10(&text);
    func_020a5338(&text, func_0209d6f8(0x40), 0, 9999);
    func_020a5d1c(data_ov002_0225a68c.x, data_ov002_0225a68c.y, &text);
    freeWindowImage(&text);
    task->state = LINK_SETUP_SHOW_OPTIONS;
    task->step  = 0;
}

/* Fades the options in. */
void func_ov002_0225209c(struct LinkSetupTask *task) {
    switch (task->step) {
        case 0:
            unlockMainPalettes();
            unlockSubPalettes();
            task->wait = 30;
            fadeInMainPalette(0, 0x100, 0, 0, 4);
            fadeInMainPalette(0x900, 0x100, 0, 0, 4);
            fadeInMainPalette(0xA00, 0x800, 0, 0, 4);
            fadeInSubPalette(0, 0x100, 0, 0, 4);
            fadeInSubPalette(0x900, 0x100, 0, 0, 4);
            fadeInSubPalette(0xA00, 0x800, 0, 0, 4);
            task->step++;
            break;
        case 1:
            task->wait--;
            if (task->wait <= 0) {
                task->state = LINK_SETUP_CHOOSE_OPTION;
                task->step  = 0;
            }
            break;
    }
}

/* Lets the player pick one of the four options, with the d-pad or by touch,
 * and explains the one under the cursor. */
void func_ov002_02251ec8(struct LinkSetupTask *task) {
    struct TextWindow text;
    s32 action;
    u8 oldCursor;
    u8 touched;

    if (task->step != 0) {
        return;
    }
    oldCursor = task->cursor;
    action    = 0;
    if ((getTouchedRects(data_ov002_0225a5cc, 1) >> 8) != 0xFF) {
        action = 1;
    }
    if (getPadPressed() & PAD_BUTTON_A) {
        action = 1;
    } else if (getPadPressed() & PAD_BUTTON_B) {
        action = 2;
    } else {
        touched = getTouchedRects(data_ov002_0225a61c, 4);
        if (touched != 0xFF) {
            task->cursor = touched;
        }
        if (getPadPressed() & PAD_KEY_UP) {
            if (task->cursor != 0) {
                task->cursor--;
            }
        }
        if (getPadPressed() & PAD_KEY_DOWN) {
            if (task->cursor < 3) {
                task->cursor++;
            }
        }
    }
    if (action == 1) {
        openFarmMessage(0xE5, 0, -1, 0xE, 0xF, 6);
        *task->option = task->cursor;
        task->send    = 2;
        task->state   = LINK_SETUP_WAIT_OPTION;
        task->step    = 0;
        return;
    }
    if (action == 2) {
        return;
    }
    if (oldCursor == task->cursor) {
        return;
    }
    setSlotSpriteAnimation(oldCursor + 2, (u16) (oldCursor * 2));
    setSlotSpriteAnimation(task->cursor + 2, (u16) (task->cursor * 2 + 1));
    func_02086758(0, 9, 0xD, 0xE, 4, 0);
    copyLinkWindowLayout(&data_ov002_0225a6e4, &text);
    func_020a6b10(&text);
    func_020a5338(&text, func_0209d6f8(task->cursor + 0x40), 0, 9999);
    func_020a5d1c(data_ov002_0225a6e4.x, data_ov002_0225a6e4.y, &text);
    freeWindowImage(&text);
}

/* Waits for both DSs to have the other's option, then says so for three
 * seconds. */
void func_ov002_02251e18(struct LinkSetupTask *task) {
    switch (task->step) {
        case 0:
            if (task->status[0] != LINK_SETUP_WAIT_OPTION || task->status[1] != LINK_SETUP_HAS_OPTION) {
                return;
            }
            if (task->otherStatus[0] != LINK_SETUP_WAIT_OPTION || task->otherStatus[1] != LINK_SETUP_HAS_OPTION) {
                return;
            }
            func_020ac650(0xE6, -1, 2);
            task->wait = 180;
            task->step++;
            break;
        case 1:
            task->wait--;
            if (task->wait > 0) {
                return;
            }
            func_020ac6f8();
            task->state = LINK_SETUP_CLOSE_OPTIONS;
            task->step  = 0;
            break;
    }
}

/* Says the link was lost and waits for the A button. */
void func_ov002_02251d7c(struct LinkSetupTask *task) {
    switch (task->step) {
        case 0:
            openFarmMessage(0xE7, 0, -1, 0xE, 0xF, 6);
            task->step++;
            break;
        case 1:
            if (getPadPressed() & PAD_BUTTON_A) {
                func_020ac6f8();
                task->step++;
            }
            break;
        case 2:
            task->state = LINK_SETUP_CLOSE_OPTIONS;
            task->step  = 0;
            break;
    }
}

/* Fades the screens out and takes them down, then ends the preparation. */
void func_ov002_02251b2c(struct LinkSetupTask *task) {
    s32 i;
    struct LinkBg *bg;
    struct BattleBg *data;

    switch (task->step) {
        case 0:
            task->wait = 30;
            fadeOutMainPalette(0, 0x100, 0, 0, 4);
            fadeOutMainPalette(0x900, 0x100, 0, 0, 4);
            fadeOutMainPalette(0xA00, 0x800, 0, 0, 4);
            fadeOutSubPalette(0, 0x100, 0, 0, 4);
            fadeOutSubPalette(0x900, 0x100, 0, 0, 4);
            fadeOutSubPalette(0xA00, 0x800, 0, 0, 4);
            task->step++;
            break;
        case 1:
            task->wait--;
            if (task->wait > 0) {
                break;
            }
            for (i = 3; i >= 0; i--) {
                bg = &data_ov002_02262f74[i];
                if (bg->loaded == 1) {
                    data = &bg->data;
                    func_02085710(bg->layer, data->unk218);
                    freeBattleBgGraphics(&data->gfx);
                    func_02086758(bg->layer, 0, 0, 0x20, 0x18, 0);
                    bg->loaded = 0;
                }
            }
            for (i = 3; i >= 0; i--) {
                bg = &data_ov002_022626f4[i];
                if (bg->loaded == 1) {
                    data = &bg->data;
                    func_0208577c(bg->layer, data->unk218);
                    freeBattleBgGraphics(&data->gfx);
                    func_020867fc(bg->layer, 0, 0, 0x20, 0x18, 0);
                    bg->loaded = 0;
                }
            }
            releaseSlotSprite(1);
            releaseSlotSprite(5);
            releaseSlotSprite(4);
            releaseSlotSprite(3);
            releaseSlotSprite(2);
            releaseSlotSprite(0x80);
            stopMainPaletteEffects(task->unk2C);
            stopMainPaletteEffects(task->unk30);
            stopSubPaletteEffects(task->unk34);
            stopSubPaletteEffects(task->unk38);
            if (task->linkLost == 2) {
                task->result = LINK_FAILED;
            } else {
                task->result = LINK_OK;
            }
            task->state = LINK_SETUP_END;
            break;
    }
}

/* Ends the preparation. For a battle, the other DS's party and the items its
 * Digimon equip become the enemy's; both options are kept and the buffers
 * freed. */
void func_ov002_02251910(struct LinkSetupTask *task) {
    s32 i;
    u8 n;

    func_020a98a8(2);
    func_020a98a8(1);
    func_020a98a8(4);
    func_020a98a8(5);
    func_020a9844(2);
    func_020a9844(1);
    func_020a9844(4);
    func_020a9844(5);
    func_020a9844(1);
    func_020a9844(4);
    func_020a9844(5);
    freeTextBank();
    stopMainPaletteEffects(-1);
    stopSubPaletteEffects(-1);
    if (task->result == LINK_OK) {
        clearLinkParty();
        setLinkPartyIds(task->otherPartyData->ids);
        n = 0;
        for (i = 0; i < LINK_BATTLE_SLOT_COUNT; i++) {
            if (task->otherPartyData->ids[i] != 0) {
                setLinkPartyDigimon(n, &task->otherPartyData->digimon[n]);
                addLinkPartyItem0(task->otherPartyData->ids[i], task->otherPartyData->items[0][n]);
                addLinkPartyItem1(task->otherPartyData->ids[i], task->otherPartyData->items[1][n]);
                addLinkPartyItem2(task->otherPartyData->ids[i], task->otherPartyData->items[2][n]);
                n++;
            }
        }
    }
    func_02081004(0, *task->option);
    func_02081004(1, *task->otherOption);
    freeMainLinkIcon();
    heapFree(task->status);
    heapFree(task->otherStatus);
    heapFree(task->partyData);
    heapFree(task->otherPartyData);
    heapFree(task->option);
    heapFree(task->otherOption);
    LINK_SETUP_RESULT = task->result;
}

/* Opens the file at path and starts reading all of it into dest. FALSE if
 * the read could not start; a file that does not open passes. */
BOOL readFileAsync(void *dest, const char *path) {
    s32 length;

    func_020d93bc(&data_ov002_02262488);
    if (func_020d906c(&data_ov002_02262488, path) != 0) {
        length = FS_GetLength(&data_ov002_02262488);
        if (length != func_020d8ef8(&data_ov002_02262488, dest, length)) {
            return FALSE;
        }
    }
    return TRUE;
}
