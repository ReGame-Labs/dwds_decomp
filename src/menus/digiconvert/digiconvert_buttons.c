#include "menus/digiconvert/digiconvert_buttons.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "engine/text/expand_text.h"
#include "engine/text/print_text.h"
#include "engine/text/text_args.h"
#include "engine/text/text_banks.h"
#include "engine/text/text_object.h"
#include "engine/text/window_text.h"
#include "engine/ui/buttons.h"
#include "menus/digiconvert/digiconvert_data.h"
#include "menus/widgets/status_window.h"

/* Hides the status of the species picked. */
void func_0205ee24(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
}

/* Asks "Use scan data and Digiconvert ...?" (system text 0x17) with the
 * name of the species picked. */
void showDigiconvertPrompt(struct Digiconvert *digiconvert) {
    struct DigiconvertWork *work;
    void *text;
    struct TextWindow *window;

    work = digiconvert->work;
    if (work->message.width != 0 && work->message.height != 0) {
        freeWindowImage(&work->message);
        func_02030f18(&digiconvert->work->message, 0, sizeof(struct TextWindow));
    }
    setTextArg(0, getSpeciesShortName(digiconvert->species));
    text = func_0209cd08(0x17);
    text = func_0209e344(text);
    func_020a5848();
    window         = &digiconvert->work->message;
    window->unk4   = 2;
    window->unkA   = 1;
    window->font   = 2;
    window->width  = 23;
    window->height = 4;
    window->unk1C  = allocVramTransferData(0xB80);
    window->unk20  = allocVramTransferData(0xB8);
    window->flags  = 0;
    func_020a6b10(window);
    func_020a5338(window, text, 0, 9999);
    func_020a5bbc(window, 2, 1, digiconvert->windows[2]);
    func_020a5830();
}

/* Says "You cannot befriend any more Digimon" (system text 0x18). */
void showBefriendLimitMessage(struct Digiconvert *digiconvert) {
    struct DigiconvertWork *work;
    void *text;
    struct TextWindow *window;

    work = digiconvert->work;
    if (work->message.width != 0 && work->message.height != 0) {
        freeWindowImage(&work->message);
        func_02030f18(&digiconvert->work->message, 0, sizeof(struct TextWindow));
    }
    text = func_0209cd08(0x18);
    func_020a5848();
    window         = &digiconvert->work->message;
    window->unk4   = 2;
    window->unkA   = 1;
    window->font   = 2;
    window->width  = 23;
    window->height = 4;
    window->unk1C  = allocVramTransferData(0xB80);
    window->unk20  = allocVramTransferData(0xB8);
    window->flags  = 0;
    func_020a6b10(window);
    func_020a5338(window, text, 0, 9999);
    func_020a5bbc(window, 2, 1, digiconvert->windows[2]);
    func_020a5830();
}

/* Says "You must have at least 100% scan data to Digiconvert" (system text
 * 0x19). */
void showScanTooLowMessage(struct Digiconvert *digiconvert) {
    struct DigiconvertWork *work;
    void *text;
    struct TextWindow *window;

    work = digiconvert->work;
    if (work->message.width != 0 && work->message.height != 0) {
        freeWindowImage(&work->message);
        func_02030f18(&digiconvert->work->message, 0, sizeof(struct TextWindow));
    }
    text = func_0209cd08(0x19);
    func_020a5848();
    window         = &digiconvert->work->message;
    window->unk4   = 2;
    window->unkA   = 1;
    window->font   = 2;
    window->width  = 23;
    window->height = 4;
    window->unk1C  = allocVramTransferData(0xB80);
    window->unk20  = allocVramTransferData(0xB8);
    window->flags  = 0;
    func_020a6b10(window);
    func_020a5338(window, text, 0, 9999);
    func_020a5bbc(window, 2, 1, digiconvert->windows[2]);
    func_020a5830();
}

/* Closes the message, if one is shown. */
void closeDigiconvertPrompt(struct Digiconvert *digiconvert) {
    struct DigiconvertWork *work;

    work = digiconvert->work;
    if (work->message.width == 0) {
        return;
    }
    if (work->message.height == 0) {
        return;
    }
    freeWindowImage(&work->message);
    func_02030f18(&digiconvert->work->message, 0, sizeof(struct TextWindow));
}

/* Closes the message, if one is shown. */
void closeBefriendLimitMessage(struct Digiconvert *digiconvert) {
    struct DigiconvertWork *work;

    work = digiconvert->work;
    if (work->message.width == 0) {
        return;
    }
    if (work->message.height == 0) {
        return;
    }
    freeWindowImage(&work->message);
    func_02030f18(&digiconvert->work->message, 0, sizeof(struct TextWindow));
}

/* Closes the message, if one is shown. */
void closeScanTooLowMessage(struct Digiconvert *digiconvert) {
    struct DigiconvertWork *work;

    work = digiconvert->work;
    if (work->message.width == 0) {
        return;
    }
    if (work->message.height == 0) {
        return;
    }
    freeWindowImage(&work->message);
    func_02030f18(&digiconvert->work->message, 0, sizeof(struct TextWindow));
}

/* Makes the list's two arrow buttons and their sprites. */
void createDigiconvertArrows(struct Digiconvert *digiconvert) {
    s32 i;
    struct ButtonGroup *group;

    digiconvert->arrowButtons = createButtonGroup(0x32, 0, func_0205e758);
    for (i = 0; i < 2; i++) {
        addRectButton(data_02116890[i * 4], data_02116890[i * 4 + 1], data_02116890[i * 4 + 2], data_02116890[i * 4 + 3], 0,
                      digiconvert->arrowButtons);
    }
    group                        = findTask(digiconvert->arrowButtons);
    group->work[0]               = 0x20;
    group->work[1]               = 0x20;
    digiconvert->arrowSprites[0] = createMainSprite(0x3A7, 0xA8, 0, 4, 0);
    digiconvert->arrowSprites[1] = createMainSprite(0x3A8, 0xA8, 0x90, 4, 0);
}

/* Frees the arrow buttons and their sprites. */
void freeDigiconvertArrows(struct Digiconvert *digiconvert) {
    if (digiconvert->arrowButtons != -1) {
        closeButtonGroup(digiconvert->arrowButtons);
        digiconvert->arrowButtons = -1;
    }
    freeMainSprite(digiconvert->arrowSprites[0]);
    freeMainSprite(digiconvert->arrowSprites[1]);
}

/* Frees the Digiconvert screen's buttons, if it has them. */
void func_0205e638(struct Digiconvert *digiconvert) {
    if (digiconvert->buttons != -1) {
        closeButtonGroup(digiconvert->buttons);
        digiconvert->buttons = -1;
    }
}
