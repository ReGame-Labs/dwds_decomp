#ifndef BATTLE_BATTLE_MODE_LINK_WAIT_H
#define BATTLE_BATTLE_MODE_LINK_WAIT_H

/* The start of a link battle: the wait for the link to the other DS, and the
 * start of the preparation. */

#include "types.h"

u8 getLinkSetupResult(void);
u8 getLinkWaitResult(void);
void tickLinkWaitTask(void);
void startLinkSetupTask(void);
void startLinkWaitTask(void);

#endif /* BATTLE_BATTLE_MODE_LINK_WAIT_H */
