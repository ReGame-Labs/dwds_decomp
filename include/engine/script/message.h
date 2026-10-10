#ifndef ENGINE_SCRIPT_MESSAGE_H
#define ENGINE_SCRIPT_MESSAGE_H

/* The script engine's messages: the text of a message id, the message tasks
 * and the commands that show a message with a Digimon speaking. */

#include "engine/data.h"
#include "types.h"

/* Message ids, as getMessageText resolves them. Below 1000 they are texts of
 * data_0211a688 and below 1500 of data_02117c40; from 1610 on, an id is the
 * text's address. */
#define MESSAGE_ID_SECOND_TABLE 1000
#define MESSAGE_ID_PLAYER_NAME 1500 /* 1500-1509 */
#define MESSAGE_ID_DIGIMON_NAME 1510 /* plus the index of a Digimon record */
#define MESSAGE_ID_ADDRESS 1610

/* An operand of commands 0xED-0xEE that names a Digimon: 10000 plus the index
 * of its record. */
#define SCRIPT_DIGIMON_FIRST 10000

/* func_0208ebb4's and func_0208ed28's task: prints a text in the window of a
 * message window task, waits for the text to end and wakes its thread. */
struct MessageTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s32 wait;
    /* 0x24 */ u16 flags; /* bit 0: style 6 for func_0209e9cc, else 2 */
    /* 0x26 */ s16 text;  /* func_0209d6f8's id */
    /* 0x28 */ s16 nameText; /* the speaker's name, a message id */
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u8 window;
    /* 0x34 */ s32 printer; /* func_0209e9cc's */
    /* 0x38 */ u16 thread;
    /* 0x3A */ u8 unk3A[0x2A];
    /* 0x64 */ u16 unk64;
};

s32 func_0208ebb4();
s32 func_0208ed28();
void *getMessageText(s32 id);
s32 func_0208e1e8(struct ScriptThread *thread);
s32 func_0208e260(struct ScriptThread *thread);

#endif /* ENGINE_SCRIPT_MESSAGE_H */
