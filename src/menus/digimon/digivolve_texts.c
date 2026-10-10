#include "menus/digimon/digivolve_texts.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/display.h"
#include "engine/text/print_text.h"
#include "engine/text/text_args.h"
#include "engine/text/text_object.h"
#include "engine/text/window_text.h"
#include "engine/window/window_draw.h"
#include "menus/digimon/data.h"

/* Frees the screen's text windows, those allocated, and clears a rectangle of
 * 13 by 6 tiles of the preview window (func_020a8a98). */
void func_ov006_02291d78(struct DigivolveScreen *screen) {
    if (screen->work->texts[0].width != 0 && screen->work->texts[0].height != 0) {
        freeWindowImage(&screen->work->texts[0]);
        func_02030f18(&screen->work->texts[0], 0, sizeof(struct TextWindow));
    }
    if (screen->work->texts[1].width != 0 && screen->work->texts[1].height != 0) {
        freeWindowImage(&screen->work->texts[1]);
        func_02030f18(&screen->work->texts[1], 0, sizeof(struct TextWindow));
    }
    if (screen->work->texts[2].width != 0 && screen->work->texts[2].height != 0) {
        freeWindowImage(&screen->work->texts[2]);
        func_02030f18(&screen->work->texts[2], 0, sizeof(struct TextWindow));
    }
    func_020a8a98(screen->previewWindow, 1, 9, 0xD, 6, 0);
    redrawWindow(screen->previewWindow);
}

/* Draws text 0xF in a text window of 20 by 4 tiles at tile (9, 2), then frees
 * the window. */
void func_ov006_02291c84(void) {
    struct TextWindow window;
    void *text;

    text = func_0209cd08(0xF);
    func_020a5848();
    window.width  = 20;
    window.height = 4;
    window.unk4   = 0;
    window.unkA   = 0x380;
    window.font   = 2;
    window.unk1C  = allocVramTransferData(window.width * window.height * 32);
    window.unk20  = allocVramTransferData(window.width * window.height * 2);
    window.flags  = 1;
    func_020a6b10(&window);
    func_020a5338(&window, text, 0, 9999);
    func_020a5d1c(9, 2, &window);
    if (window.width != 0 && window.height != 0) {
        freeWindowImage(&window);
        CLEAR(&window, sizeof(window));
    }
    func_020a5830();
}
