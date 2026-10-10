#include "link/exchange_programs.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/digimon_list.h"
#include "engine/window/message_box.h"
#include "farm/panel_digimon.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_tasks.h"
#include "link/exchange.h"
#include "link/exchange_panels_task.h"
#include "link/link_screen.h"

/* The exchange's onEnd: frees its blocks. */
void onExchangeEnd(void) {
    struct Exchange *exchange;
    void *block;

    exchange = (struct Exchange *) getCurrentTask();
    block    = exchange->work;
    heapFree(block);
    exchange->work = NULL;
    block          = exchange->unk20;
    heapFree(block);
    exchange->unk20 = NULL;
    block           = exchange->unk24;
    heapFree(block);
    exchange->unk24 = NULL;
    block           = exchange->unk28;
    heapFree(block);
    exchange->unk28 = NULL;
    block           = exchange->unk2C;
    heapFree(block);
    exchange->unk2C = NULL;
    block           = exchange->unk34;
    heapFree(block);
    exchange->unk34 = NULL;
    block           = exchange->unk38;
    heapFree(block);
    exchange->unk38 = NULL;
    block           = exchange->unk4C;
    heapFree(block);
    exchange->unk4C = NULL;
    block           = exchange->unk50;
    heapFree(block);
    exchange->unk50 = NULL;
    block           = exchange->unk54;
    heapFree(block);
    exchange->unk54 = NULL;
    block           = exchange->unk40;
    heapFree(block);
    exchange->unk40  = NULL;
    EXCHANGE_TASK_ID = -1;
    EXCHANGE_ACTIVE  = 0;
}

/* Frees the exchange's windows, panels, sprites, backgrounds, pictures and
 * fonts, then clears both screens. */
void freeExchange(struct Exchange *exchange) {
    closeDigimonList();
    func_ov005_0227fd00();
    func_020ac6f8();
    func_02068638(exchange);
    freeSubLinkIcon();
    freeMainSprites();
    freeSubSprites();
    deleteMainActors();
    deleteSubActors();
    endMainActorTask();
    endSubActorTask();
    freeBgGraphics(&exchange->work->bgs[0]);
    freeBgGraphics(&exchange->work->bgs[1]);
    freeBgGraphics(&exchange->work->bgs[2]);
    stopSubPaletteEffectsButFades(exchange->unk74[0]);
    stopSubPaletteEffectsButFades(exchange->unk74[1]);
    stopMainPaletteEffectsButFades(exchange->unk7C[0]);
    stopMainPaletteEffectsButFades(exchange->unk7C[1]);
    freeExchangeFonts();
    clearExchangeScreens();
}

/* Whether the exchange has ended. */
u8 isExchangeEnded(void) {
    u8 ended;

    if (EXCHANGE_ACTIVE == 0) {
        ended = TRUE;
    } else {
        ended = FALSE;
    }
    return ended;
}
