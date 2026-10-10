#include "link/wifi_matching_screen.h"
#include "engine/bg/bg_load.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display.h"
#include "engine/ui/buttons.h"

/* Clears the Wi-Fi matching screen's background 1 and frees its four
 * sprites. */
void clearWifiMatchingScreen(struct WifiMatching *matching) {
    struct ScreenCopy copy;

    copy.bg        = 1;
    copy.unk2      = 0;
    copy.unk4      = 3;
    copy.x         = 0;
    copy.y         = 0;
    copy.srcX      = 0;
    copy.srcY      = 0;
    copy.width     = 0x1F;
    copy.height    = 0x17;
    copy.src       = NULL;
    copy.srcWidth  = 0x20;
    copy.srcHeight = 0x20;
    copyMainBgScreenAndFlush((u8 *) &copy);
    func_02042ee0(0, 0, 0x20, 0x17);
    if (matching->work->sprites[2] != -1) {
        freeMainSprite(matching->work->sprites[2]);
        matching->work->sprites[2] = -1;
    }
    if (matching->work->sprites[3] != -1) {
        freeMainSprite(matching->work->sprites[3]);
        matching->work->sprites[3] = -1;
    }
    if (matching->work->sprites[0] != -1) {
        freeMainSprite(matching->work->sprites[0]);
        matching->work->sprites[0] = -1;
    }
    if (matching->work->sprites[1] != -1) {
        freeMainSprite(matching->work->sprites[1]);
        matching->work->sprites[1] = -1;
    }
}

/* Frees the Wi-Fi matching screen's buttons and the sprite that goes with
 * them. */
void freeWifiMatchingButtons(struct WifiMatching *matching) {
    s32 buttons;

    buttons = matching->buttons;
    if (buttons != -1) {
        if (buttons != -1) {
            closeButtonGroup(buttons);
            matching->buttons = -1;
        }
    }
    if (matching->work->unk48 == -1) {
        return;
    }
    freeMainSprite(matching->work->unk48);
    matching->work->unk48 = -1;
}
