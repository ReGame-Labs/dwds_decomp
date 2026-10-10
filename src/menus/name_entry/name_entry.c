#include "menus/name_entry/name_entry.h"
#include "engine/bg/bg_layers.h"
#include "engine/text/window_text.h"
#include "engine/window/message_box.h"
#include "menus/experience/experience_screen.h"

/* Writes text 0x34 + unk21 of func_0209ec68's table with func_020a6808. */
void func_02083318(struct NameEntry *entry) {
    void *text = func_0209ec68(entry->unk21 + 0x34);

    func_020a6808(entry->unk25, 1, 0, 0xE, 2, text, 0, entry->unk22, 4, 0, 0);
}

/* Waits for the answer to the confirmation: yes closes the name entry, no or
 * a cancel goes back to typing. */
void func_02081bf4(struct NameEntry *entry) {
    switch (func_020ac6b8()) {
        case 0:
            playSound(1);
            func_020ac6f8();
            entry->state = NAME_ENTRY_CLOSE;
            return;
        case 1:
        case 9999: /* cancelled */
            func_020ac6f8();
            entry->state = NAME_ENTRY_INPUT;
            return;
    }
}

/* Waits for the message to be closed, then closes the name entry. */
void func_02081bd0(struct NameEntry *entry) {
    if (func_020ac6b8() != 0) {
        return;
    }
    func_020ac6f8();
    entry->state = NAME_ENTRY_CLOSE;
}
