#ifndef LINK_EXCHANGE_SCREEN_H
#define LINK_EXCHANGE_SCREEN_H

/* The save menu's end, and the exchange's screen: its font slots and its
 * windows. */

#include "link/exchange.h"
#include "types.h"

/* A window slot that is not open (closeWindow closes the others). */
#define NO_WINDOW 0xFF

void onSaveMenuEnd(void);
void closeExchangeWindows(struct Exchange *exchange);
void loadExchangeFontSlots(struct Exchange *exchange);
void freeExchangeFontSlots(struct Exchange *exchange);

#endif /* LINK_EXCHANGE_SCREEN_H */
