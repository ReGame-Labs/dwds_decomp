#ifndef MENUS_DIGICONVERT_DIGICONVERT_BUTTONS_H
#define MENUS_DIGICONVERT_DIGICONVERT_BUTTONS_H

/* The Digiconvert screen's buttons and messages. */

#include "types.h"

struct Digiconvert;

void func_0205ee24(void);
void func_0205e638(struct Digiconvert *digiconvert);
void freeDigiconvertArrows(struct Digiconvert *digiconvert);
void closeScanTooLowMessage(struct Digiconvert *digiconvert);
void closeBefriendLimitMessage(struct Digiconvert *digiconvert);
void closeDigiconvertPrompt(struct Digiconvert *digiconvert);
void func_0205e758();
void createDigiconvertArrows(struct Digiconvert *digiconvert);
void showScanTooLowMessage(struct Digiconvert *digiconvert);
void showBefriendLimitMessage(struct Digiconvert *digiconvert);
void showDigiconvertPrompt(struct Digiconvert *digiconvert);

#endif /* MENUS_DIGICONVERT_DIGICONVERT_BUTTONS_H */
