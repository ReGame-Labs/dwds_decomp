#ifndef LINK_EXCHANGE_PROGRAMS_H
#define LINK_EXCHANGE_PROGRAMS_H

/* The exchange's end. */

#include "link/exchange.h"
#include "types.h"

u8 isExchangeEnded(void);
void freeExchange(struct Exchange *exchange);
void onExchangeEnd(void);

#endif /* LINK_EXCHANGE_PROGRAMS_H */
