#include "link/link_session.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/save/progress.h"
#include "engine/system/display.h"
#include "engine/system/system.h"
#include "link/link_start.h"

/* The link session's onEnd: frees its four blocks. */
void onLinkSessionEnd(void) {
    struct LinkSession *session;
    void *block;

    session = (struct LinkSession *) getCurrentTask();
    block   = session->work;
    heapFree(block);
    session->work = NULL;
    block         = session->unk20;
    heapFree(block);
    session->unk20 = NULL;
    block          = session->unk24;
    heapFree(block);
    session->unk24 = NULL;
    block          = session->choice;
    heapFree(block);
    session->choice      = NULL;
    LINK_SESSION_TASK_ID = -1;
    LINK_SESSION         = NULL;
    func_020878ec();
}

/* Ends the link session, if there is one. */
void endLinkSession(void) {
    struct LinkSession *session;

    if (LINK_SESSION == NULL) {
        return;
    }
    session = findTask(LINK_SESSION_TASK_ID);
    if (session->unk3C != 0) {
        func_0207270c(2, 0);
    }
    session->state = LINK_STATE_END;
}

/* Whether a matching session is in its state 0x1FE or 0x212. */
BOOL func_02071ba8(void) {
    u16 state;
    struct LinkSession *session;

    session = findTask(LINK_SESSION_TASK_ID);
    if ((LINK_SESSION != NULL) && ((state = session->state, (state == 0x1FE)) || (state == 0x212)) &&
        (session->kind == LINK_KIND(LINK_MATCHING))) {
        return TRUE;
    }
    return FALSE;
}

/* Whether there is no link session. */
u8 isLinkSessionEnded(void) {
    u8 ended;

    if (LINK_SESSION == NULL) {
        ended = TRUE;
    } else {
        ended = FALSE;
    }
    return ended;
}

/* The link session's unk38, or 0 with no session. */
s32 func_02071b5c(void) {
    struct LinkSession *session;

    session = findTask(LINK_SESSION_TASK_ID);
    if (session != NULL) {
        return session->unk38;
    }
    return 0;
}

/* Clears the link session's unk38. */
void func_02071b4c(void) {
    func_02071b28(0);
}

/* Sets the link session's unk38. */
void func_02071b28(s32 value) {
    struct LinkSession *session;

    session = findTask(LINK_SESSION_TASK_ID);
    if (session != NULL) {
        session->unk38 = value;
    }
}

/* Gives the link session three values, if all are set. */
void func_02071acc(s32 a, s32 b, s32 c) {
    struct LinkSession *session;

    if (LINK_SESSION == NULL) {
        return;
    }
    if (a == 0) {
        return;
    }
    if (b == 0) {
        return;
    }
    if (c == 0) {
        return;
    }
    session           = findTask(LINK_SESSION_TASK_ID);
    session->unk60[0] = a;
    session->unk60[1] = b;
    session->unk60[2] = c;
}

/* Why a Digimon cannot be traded, from func_0209ff8c's flags: 0 it can,
 * 2 to 5 a reason, -1 no session. */
s32 getTradeBlockReason(s32 digimon) {
    s32 flags;
    struct LinkSession *session;

    if (LINK_SESSION == NULL) {
        return -1;
    }
    session = findTask(LINK_SESSION_TASK_ID);
    if (session->unk24 == NULL) {
        return -1;
    }
    flags = func_0209ff8c(digimon);
    if (flags != 0) {
        if (flags & 0x10) {
            return 2;
        }
        if (flags & 0x20) {
            return 3;
        }
        if (flags & 8) {
            return 4;
        }
        if (flags & 2) {
            return 5;
        }
        if (flags & 4) {
            return 5;
        }
    }
    return 0;
}

/* The unk1C of the link session's unk24 block, or 0. */
s32 func_020719e0(void) {
    struct LinkSession *session;

    if (LINK_SESSION == NULL) {
        return 0;
    }
    if (LINK_SESSION->unk24 == NULL) {
        return 0;
    }
    session = findTask(LINK_SESSION_TASK_ID);
    return session->unk24->unk1C;
}

/* The link session's unk24 block, or NULL. */
struct LinkBlock *func_0207198c(void) {
    if (LINK_SESSION == NULL) {
        return NULL;
    }
    if (LINK_SESSION->unk24 == NULL) {
        return NULL;
    }
    return ((struct LinkSession *) findTask(LINK_SESSION_TASK_ID))->unk24;
}
