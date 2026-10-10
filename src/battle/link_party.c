#include "battle/link_party.h"
#include "engine/data.h"
#include "engine/libs.h"

void func_02081290(s8 value) {
    data_021bc1b0 = value;
}

/* The ids of the link partner's party. */
s32 *getLinkPartyIds(void) {
    return LINK_PARTY_IDS;
}

/* Sets the ids of the link partner's party: its first five slots, 0 for
 * none. */
void setLinkPartyIds(const s32 *ids) {
    s32 i;

    for (i = 0; i < LINK_PARTY_SLOT_COUNT; i++) {
        LINK_PARTY_IDS[i] = *ids;
        ids++;
    }
}

/* The link partner's Digimon with the index. */
struct Digimon *getLinkPartyDigimon(s32 index) {
    return &LINK_PARTY_DIGIMON[index];
}

/* Sets the link partner's Digimon with the index. */
void setLinkPartyDigimon(s8 index, const struct Digimon *digimon) {
    func_02030f78(&LINK_PARTY_DIGIMON[index], digimon, sizeof(struct Digimon));
}

/* The item the link partner's Digimon with the id equips in its first slot. */
u16 getLinkPartyItem0(s32 id) {
    s32 i;
    struct LinkPartyItem *slot;

    slot = LINK_PARTY_ITEMS0;
    for (i = 0; i < LINK_PARTY_DIGIMON_COUNT; i++) {
        if (slot->id == id) {
            return slot->item;
        }
        slot++;
    }
    return NO_ITEM;
}

/* Records the item the link partner's Digimon with the id equips in its first
 * slot. */
s32 addLinkPartyItem0(s32 id, u16 item) {
    s32 i;
    struct LinkPartyItem *slot;

    slot = LINK_PARTY_ITEMS0;
    for (i = 0; i < LINK_PARTY_DIGIMON_COUNT; i++) {
        if (slot->id == 0) {
            slot->id   = id;
            slot->item = item;
            return TRUE;
        }
        slot++;
    }
    return FALSE;
}
