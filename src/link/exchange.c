#include "link/exchange.h"
#include "engine/digimon/digimon_records.h"
#include "engine/digimon/game_data.h"
#include "engine/digimon/species_flags.h"
#include "engine/libs.h"
#include "engine/text/font.h"
#include "farm/farm_groups.h"
#include "farm/farms.h"
#include "link/link_session.h"
#include "link/wifi.h"

/* Reads the partner's packet into the block its type names, and returns the
 * type. */
u8 readPartnerPacket(struct Exchange *exchange) {
    struct LinkPacket *packet;
    u8 *block;

    packet = (struct LinkPacket *) getReceivedPacket(func_020b65a0() == 1 ? 1 : 0);
    switch (packet->type) {
        default:
            block    = exchange->unk20;
            block[0] = 0;
            block[1] = 0;
            block[2] = 0;
            block[3] = 0;
            break;
        case 2:
            func_02030f78(exchange->unk20 + packet->offset, packet->data, packet->size);
            break;
        case 3:
            func_02030f78(exchange->unk28 + packet->offset, packet->data, packet->size);
            break;
    }
    return packet->type;
}

/* Takes in another player's Digimon for training in a new record, and marks
 * the one lent in its place as away. */
void receiveTrainingGuest(struct Digimon *lent, struct Digimon *guest) {
    struct Digimon *record;
    s32 id;

    func_020a0ee0(guest->unk4);
    record = getDigimonAt(addDigimon(guest->unk4));
    id     = record->id;
    func_02030f78(record, guest, sizeof(struct Digimon));
    record->id     = id;
    record->homeId = guest->homeId;
    record->unk10C = func_020719e0();
    func_020a2d34(record, DIGIMON_GUEST);
    func_020a2d34(lent, DIGIMON_LENT);
    removeFarmDigimon(lent->id);
    func_020b4cf8(record);
}

/* Takes back an own Digimon, home from training, and frees the guest's
 * record. */
void receiveTrainedDigimon(struct Digimon *guest, struct Digimon *home) {
    struct Digimon *record;

    record = getDigimon(home->homeId);
    func_02030f78(record, home, sizeof(struct Digimon));
    record->id     = home->homeId;
    record->homeId = 0;
    record->unk10C = 0;
    func_020a2cc0(record, DIGIMON_LENT);
    func_020a2cc0(record, DIGIMON_GUEST);
    func_020a2b94(guest->id);
    func_020b4cf8(record);
}

/* Loads the exchange's fonts. */
void loadExchangeFonts(void) {
    func_020a9c40(2, 0, 0xE);
    func_020a9c40(1, 1, 0xE);
    func_020a9c40(4, 3, 0xE);
    func_020a9c40(5, 2, 0xE);
    func_020a9ae0(2, 4, 0xE);
    func_020a9ae0(1, 5, 0xE);
    func_020a9ae0(5, 6, 0xE);
    func_020a9ae0(0, 7, 0xF);
    func_020a9ae0(4, 8, 0x1F);
}

/* Frees the exchange's fonts. */
void freeExchangeFonts(void) {
    func_020a98a8(2);
    func_020a98a8(1);
    func_020a98a8(4);
    func_020a98a8(5);
    func_020a9844(2);
    func_020a9844(1);
    func_020a9844(5);
    func_020a9844(0);
    func_020a9844(4);
}
