#include "battle/battle_mode/panels.h"
#include "battle/battle_mode/data.h"
#include "battle/sprite_slots.h"
#include "battle/unit_panel_draw.h"
#include "engine/libs.h"
#include "engine/text/print_text.h"
#include "engine/text/text_banks.h"
#include "link/wifi.h"

/* Closes the first unit's panel. */
void closeFirstUnitPanel(void) {
    struct UnitPanel *panel = &data_ov002_0225a7c8;

    if (!(panel->flags & 1)) {
        return;
    }
    releaseSlotSprite(4);
    releaseSlotSprite(panel->sprites[2]);
    releaseSlotSprite(panel->sprites[1]);
    releaseSlotSprite(panel->sprites[0]);
    func_0209d954(panel->unk8);
    freeUnitPanelNumbers(panel);
    panel->sprites[0] = 0xFF;
    panel->sprites[1] = 0xFF;
    panel->flags &= ~1;
}

/* Closes one of the panels after the first. */
void closeUnitPanel(s32 index) {
    struct UnitPanel *panel = &data_ov002_0225a9e8[index];

    if (!(panel->flags & 1)) {
        return;
    }
    releaseSlotSprite(panel->sprites[2]);
    releaseSlotSprite(panel->sprites[1]);
    releaseSlotSprite(panel->sprites[0]);
    func_0209d900(panel->unk8);
    panel->flags &= ~1;
}

/* Whether the panel has stopped moving. */
BOOL func_ov002_022466fc(s32 index) {
    if (!(data_ov002_0225a9e8[index].flags & 2)) {
        return TRUE;
    }
    return FALSE;
}

/* Sets up the panel's two numbers, of four digits. */
void func_ov002_02245cb0(struct BattlePanel *panel) {
    struct NumberSprite *number;

    number          = &panel->numbers[0];
    number->unk00   = 0;
    number->unk01   = 4;
    number->unk02   = 0xFFFF;
    number->palette = 1;
    number->unk05   = 0;
    number->digits  = 4;
    number->value   = 0;
    number->unk0C   = 0;
    number->unk10   = 1;
    number->unk14   = 0;
    number->unk16   = 0;
    func_020a503c((u8 *) number);
    number          = &panel->numbers[1];
    number->unk00   = 1;
    number->unk01   = 4;
    number->unk02   = 0xFFFF;
    number->palette = 1;
    number->unk05   = 0;
    number->digits  = 4;
    number->value   = 0;
    number->unk0C   = 0;
    number->unk10   = 1;
    number->unk14   = 0;
    number->unk16   = 0;
    func_020a503c((u8 *) number);
}

/* Copies what a packet from the other DS carries into the battle. */
void receiveBattlePacket(struct BattleTask *task) {
    s32 aid;
    struct LinkPacket *packet;

    if (func_020b65a0() == 1) {
        aid = 1;
    } else {
        aid = 0;
    }
    packet = (struct LinkPacket *) getReceivedPacket(aid);
    switch (packet->type) {
        case 9:
            func_02030f78(BATTLE->unk6FCC + packet->offset, packet->data, packet->size);
            break;
        case LINK_PACKET_RANDOM_TABLE:
            func_02030f78((u8 *) BATTLE->randomTable + packet->offset, packet->data, packet->size);
            task->received = 1;
            break;
        case 11:
            func_02030f78(BATTLE->unk3DF0 + packet->offset, packet->data, packet->size);
            task->received = 2;
            break;
        case 12:
            func_02030f78(&BATTLE->unk6FCF + packet->offset, packet->data, packet->size);
            break;
    }
    task->packetType = packet->type;
}
