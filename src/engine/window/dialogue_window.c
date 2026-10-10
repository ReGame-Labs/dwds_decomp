#include "engine/window/dialogue_window.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "engine/text/window_text.h"

/* Returns whether the text box of func_020a7bac is open. */
BOOL func_020a7538(void) {
    if (data_021e33e0 != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Opens the text box of func_020a725c. */
void func_020a74ec(s16 unk2E, s16 unk26) {
    struct TextBox *box;

    box           = createTask(&func_020a725c, 0x104);
    box->state    = 0;
    box->unk20    = 0;
    box->unk26    = unk26;
    box->unk2E    = unk2E;
    data_021e33d8 = getTaskId(box);
}

/* Opens the text box of func_020a6f10. */
void func_020a74a0(s16 unk2E, s16 unk26) {
    struct TextBox *box;

    box           = createTask(&func_020a6f10, 0x104);
    box->state    = 0;
    box->unk20    = 0;
    box->unk26    = unk26;
    box->unk2E    = unk2E;
    data_021e33dc = getTaskId(box);
}
