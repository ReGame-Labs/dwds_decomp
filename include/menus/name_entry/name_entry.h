#ifndef MENUS_NAME_ENTRY_NAME_ENTRY_H
#define MENUS_NAME_ENTRY_NAME_ENTRY_H

#include "engine/data.h"
#include "types.h"

/* The name entry screen: a keyboard of three pages on the touch screen, which
 * the script commands open to name the player or a Digimon (engine/palette/palette_buffers.c). */

/* The states of func_0208337c, the name entry's task. */
enum NameEntryState {
    NAME_ENTRY_OPEN,    /* func_02082c24 */
    NAME_ENTRY_STATE_1, /* func_02082b3c */
    NAME_ENTRY_INPUT,   /* func_02081cd8 */
    NAME_ENTRY_CONFIRM, /* func_02081bf4 */
    NAME_ENTRY_MESSAGE, /* func_02081bd0 */
    NAME_ENTRY_CLOSE,   /* func_02081a5c */
    NAME_ENTRY_CLOSED
};

/* The name entry's task. The fields after unk25, up to 0x38 at least, are only
 * read by the functions still in assembly. */
struct NameEntry {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 state; /* enum NameEntryState */
    /* 0x1E */ u8 unk1E[3];
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 unk23[2];
    /* 0x25 */ u8 unk25;
};

void func_02081bd0(struct NameEntry *entry);
void func_02081bf4(struct NameEntry *entry);
void func_02083318(struct NameEntry *entry);

#endif /* MENUS_NAME_ENTRY_NAME_ENTRY_H */
