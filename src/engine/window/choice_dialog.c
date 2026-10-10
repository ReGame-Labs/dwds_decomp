#include "engine/window/choice_dialog.h"
#include "engine/data.h"
#include "engine/system/system.h"
#include "engine/text/expand_text.h"
#include "engine/text/text_args.h"
#include "engine/text/window_text.h"
#include "engine/window/dialogue_window.h"
#include "engine/window/window.h"

/* Prints two texts side by side, at x 0 and 0x58, into the text box of
 * data_021e33dc, each moved up by its number of lines (func_0209d02c). */
void func_020a7f04(s32 index, void *text0, void *text1) {
    void *text;
    s32 lines;

    getWindow(index);
    text  = func_0209e344(text0);
    lines = func_0209d02c();
    func_020a68cc((u8) data_021e33dc, 3, (s16) (3 - lines), 0x16, (s16) (4 - (2 - lines)), text, 0, 0xE, 3, 2, 4);
    text  = func_0209e344(text1);
    lines = func_0209d02c();
    func_020a68cc((u8) data_021e33dc, 3, (s16) (8 - lines), 0x16, (s16) (4 - (2 - lines)), text, 0x58, 0xE, 3, 2, 4);
}

/* Opens the text box of func_020a78a4; script commands open it. */
void func_020a7bac(u16 unk28, u16 unk2C, u16 unk2A, u16 unk2E, u16 unk26) {
    struct TextBox *box;

    box           = createTask(&func_020a78a4, 0x11D);
    box->state    = 0;
    box->unk20    = 0;
    box->unk28    = unk28;
    box->unk2C    = unk2C;
    box->unk2A    = unk2A;
    box->unk26    = unk26;
    box->unk2E    = unk2E;
    data_021e33e0 = getTaskId(box);
}
