#ifndef LINK_TRAINING_MENU_H
#define LINK_TRAINING_MENU_H

/* The training menu's steps of the link session: its two-button prompt. */

#include "link/link_session.h"
#include "types.h"

void closeLinkPrompt(struct LinkSession *session);
void freeLinkSessionButtons(struct LinkSession *session);
void func_0206e38c(struct LinkSession *session);
void onLinkPromptButton(s32 touched, s32 cursor, struct ButtonGroup *group);
void openLinkPrompt(struct LinkSession *session);

#endif /* LINK_TRAINING_MENU_H */
