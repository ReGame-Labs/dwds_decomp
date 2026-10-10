#ifndef MENUS_FIELD_MENU_PARTY_PANEL_H
#define MENUS_FIELD_MENU_PARTY_PANEL_H

#include "types.h"

/* The party panels (one for each Digimon of the party), and the freeing of
 * both kinds of panel. */

#define PARTY_PANEL_WIDTH 13 /* in tiles */
#define PARTY_PANEL_HEIGHT 4

void closePanels(void);
void func_02049f18(s8 slot, s32 unk1);
void func_02049edc(void);
void freePartyPanelSprites(s16 index);
void closePartyPanel(s16 index);

#endif /* MENUS_FIELD_MENU_PARTY_PANEL_H */
