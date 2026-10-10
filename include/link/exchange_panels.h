#ifndef LINK_EXCHANGE_PANELS_H
#define LINK_EXCHANGE_PANELS_H

/* The exchange's Digimon panels: their buttons and sprites. */

#include "link/exchange.h"
#include "types.h"

void resumeExchangePanelButtons(struct Exchange *exchange);
void pauseExchangePanelButtons(struct Exchange *exchange);
void freeExchangePanels(struct Exchange *exchange);

#endif /* LINK_EXCHANGE_PANELS_H */
