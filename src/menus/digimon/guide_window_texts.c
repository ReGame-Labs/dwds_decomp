#include "menus/digimon/guide_window_texts.h"
#include "engine/bg/bg_screen.h"
#include "engine/libs.h"
#include "engine/text/text_object.h"
#include "menus/digimon/data.h"

/* Frees the guide's four text windows of data_ov006_0229f770, after the one
 * func_ov006_02298fb8 frees. */
void func_ov006_02298cc4(void) {
    s32 i;
    struct TextWindow *window;

    func_ov006_02298fb8();
    for (i = 0, window = data_ov006_0229f770; i < 4; i++, window++) {
        if (window->width != 0 && window->height != 0) {
            freeWindowImage(window);
            func_02030f18(window, 0, sizeof(struct TextWindow));
        }
    }
}

/* Makes main screen sprites 6 to 9 (0x3AC to 0x3AF), one above the other
 * past the right edge, for func_ov006_02298054 to slide in. */
void func_ov006_02298598(void) {
    createMainSpriteAt(0x3AC, 0x118, 0x40, 6, 0, 6);
    createMainSpriteAt(0x3AD, 0x118, 0x50, 6, 0, 7);
    createMainSpriteAt(0x3AE, 0x118, 0x60, 6, 0, 8);
    createMainSpriteAt(0x3AF, 0x118, 0x70, 6, 0, 9);
}
