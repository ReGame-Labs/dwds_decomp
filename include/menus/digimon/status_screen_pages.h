#ifndef MENUS_DIGIMON_STATUS_SCREEN_PAGES_H
#define MENUS_DIGIMON_STATUS_SCREEN_PAGES_H

/* The status screen's pages: the windows and displays each page shows, and the
 * page's buttons. */

#include "types.h"

struct StatusScreen;

u8 func_ov006_0228c2ec(struct StatusScreen *screen);
void func_ov006_0228c358(struct StatusScreen *screen);
void func_ov006_0228c630(void);
void func_ov006_0228c740(void);
void func_ov006_0228c940(void);
void func_ov006_0228ca14(void);
void func_ov006_0228c308(struct StatusScreen *screen);

#endif /* MENUS_DIGIMON_STATUS_SCREEN_PAGES_H */
