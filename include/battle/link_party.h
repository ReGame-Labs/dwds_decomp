#ifndef BATTLE_LINK_PARTY_H
#define BATTLE_LINK_PARTY_H

#include "types.h"

/* The link partner's party in a link battle, and starting the battle and
 * returning from it. */

struct Digimon;

struct Digimon *findLinkPartyDigimon(s32 id);
struct Digimon *getLinkPartyDigimon(s32 index);
s32 *getLinkPartyIds(void);
void func_02081290(s8 value);
s32 func_020812a0();
s32 func_020816e8();
void setLinkPartyDigimon(s8 index, const struct Digimon *digimon);
void setLinkPartyIds(const s32 *ids);
s32 addLinkPartyItem0(s32 id, u16 item);
u16 getLinkPartyItem0(s32 id);
void clearLinkParty(void);

#endif /* BATTLE_LINK_PARTY_H */
