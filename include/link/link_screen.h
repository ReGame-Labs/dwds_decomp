#ifndef LINK_LINK_SCREEN_H
#define LINK_LINK_SCREEN_H

/* The link screen: its list of partners, its fonts and its link level
 * icons. */

#include "link/link_session.h"
#include "types.h"

void showMainLinkIcon(s32 palette, s32 unk12);
void freeLinkScreenFonts(void);
void loadLinkScreenFonts(void);
void clearLinkScreens(void);
void func_0206f55c(struct LinkSession *session, s32 show);
s32 freeMainLinkIcon(void);
s32 freeSubLinkIcon(void);
void updateLocalLinkIcons(void);
void showSubLinkIcon(s32 palette, s32 unk12);
void closeLinkList(struct LinkSession *session);
void onLinkListButton();
void openLinkList(struct LinkSession *session);

#endif /* LINK_LINK_SCREEN_H */
