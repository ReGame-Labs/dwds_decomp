#ifndef LINK_LINK_SESSION_H
#define LINK_LINK_SESSION_H

/* The link session: the task that connects two DS for a trade, training, a
 * matching, a battle or a Wi-Fi trade, and what other code asks of it. */

#include "engine/data.h"
#include "types.h"

/* What a link session connects for (func_020722f0's mode). */
enum LinkMode {
    LINK_TRADE,
    LINK_TRAINING,
    LINK_MATCHING,
    LINK_BATTLE,
    LINK_WIFI
};

/* The session's kind as it keeps it: 0x08080801 plus its LinkMode. */
#define LINK_KIND(mode) (0x08080801 + (mode))

/* The state that ends a link session. */
#define LINK_STATE_END 9999

/* One of the link session's 0x34-byte blocks. */
struct LinkBlock {
    /* 0x00 */ u8 unk0[0x1C];
    /* 0x1C */ s32 unk1C; /* the session's at 0x24 is put in a lent Digimon's unk10C */
    /* 0x20 */ u8 unk20[0x14];
};

/* The link session's work block, 0x188 bytes. */
struct LinkSessionWork {
    /* 0x000 */ u8 unk0[0x148];
    /* 0x148 */ s32 cursorSprite; /* the two-button prompt's, or -1 */
    /* 0x14C */ u8 unk14C[8];
    /* 0x154 */ s32 sprites[2]; /* or -1 */
    /* 0x15C */ u8 unk15C[8];
    /* 0x164 */ s32 unk164; /* a sprite (0x3F8) beside the list, or -1 */
    /* 0x168 */ u8 unk168[0x10];
    /* 0x178 */ u16 unk178; /* shown with system text 0x3D */
    /* 0x17A */ u8 unk17A[0xE];
};

/* The link session, a task made by func_02071f18. */
struct LinkSession {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct LinkSessionWork *work;
    /* 0x20 */ struct LinkBlock *unk20;
    /* 0x24 */ struct LinkBlock *unk24;
    /* 0x28 */ s16 *choice; /* a two-button prompt's: the button picked, then the one before */
    /* 0x2C */ s32 buttons; /* a button group's task id, or -1 */
    /* 0x30 */ u16 state;
    /* 0x32 */ u16 step; /* within some states */
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s32 unk38; /* set by func_02071b28 */
    /* 0x3C */ s32 unk3C; /* when set, ending the session calls func_0207270c(2, 0) */
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 kind; /* LINK_KIND of its mode */
    /* 0x48 */ s16 unk48;
    /* 0x4A */ u16 unk4A;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D[0x13];
    /* 0x60 */ s32 unk60[3]; /* set together by func_02071acc */
};

/* The two-button prompt's buttons: x, y, width and height each, read as a
 * flat array. */
extern s16 LINK_PROMPT_RECTS[];

/* The list's five buttons on the link screen: x, y, width and height each,
 * read as a flat array. */
extern s16 data_021357ac[];
/* The link level icons on the main screen and the sub screen, or -1. */
extern s32 MAIN_LINK_ICON;
extern s32 SUB_LINK_ICON;

extern struct LinkSession *LINK_SESSION;
extern s32 LINK_SESSION_TASK_ID; /* the link session's task id */

void func_02071acc(s32 a, s32 b, s32 c);
void func_02071b28(s32 value);
void func_02071b4c(void);
s32 func_02071b5c(void);
u8 isLinkSessionEnded(void);
BOOL func_02071ba8(void);
struct LinkBlock *func_0207198c(void);
s32 func_020719e0(void);
void onLinkSessionEnd(void);
s32 getTradeBlockReason(s32 digimon);
void endLinkSession(void);
s32 func_02071c20(void);

#endif /* LINK_LINK_SESSION_H */
