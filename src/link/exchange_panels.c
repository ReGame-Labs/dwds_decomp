#include "link/exchange_panels.h"
#include "engine/sprite/sprite_create.h"
#include "engine/ui/buttons.h"

/* Frees the exchange's buttons and its three sprites. */
void freeExchangePanels(struct Exchange *exchange) {
    s32 i;

    if (exchange->buttons != -1) {
        closeButtonGroup(exchange->buttons);
        exchange->buttons = -1;
    }
    for (i = 0; i < 3; i++) {
        freeSubSprite(exchange->work->sprites[i]);
    }
}

/* Pauses the exchange's buttons. */
void pauseExchangePanelButtons(struct Exchange *exchange) {
    pauseButtonGroup(exchange->buttons);
}

/* Resumes the exchange's buttons. */
void resumeExchangePanelButtons(struct Exchange *exchange) {
    resumeButtonGroup(exchange->buttons);
}
