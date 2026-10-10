#include "link/training_menu.h"
#include "engine/bg/bg_load.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "engine/ui/digimon_list.h"
#include "engine/window/message_box.h"
#include "link/link_session.h"

/* Opens the two-button prompt: its cursor sprite and its buttons, the cursor
 * on the first. */
void openLinkPrompt(struct LinkSession *session) {
    s32 i;

    if (session->buttons != -1) {
        return;
    }
    if (session->work->cursorSprite == -1) {
        session->work->cursorSprite = createMainSprite(0x40E, (s16) (LINK_PROMPT_RECTS[0] - 3), LINK_PROMPT_RECTS[1], 2, 0);
    }
    session->choice[1] = 0;
    session->choice[0] = session->choice[1];
    session->buttons   = createButtonGroup(0, session->choice[0], onLinkPromptButton);
    for (i = 0; i < 2; i++) {
        addRectButton(LINK_PROMPT_RECTS[i * 4], LINK_PROMPT_RECTS[i * 4 + 1], LINK_PROMPT_RECTS[i * 4 + 2],
                      LINK_PROMPT_RECTS[i * 4 + 3], 0, session->buttons);
    }
    findTask(session->buttons);
}

/* Closes the two-button prompt: its buttons, its cursor and its window. */
void closeLinkPrompt(struct LinkSession *session) {
    if (session->buttons != -1 && session->buttons != -1) {
        closeButtonGroup(session->buttons);
        session->buttons = -1;
    }
    if (session->work->cursorSprite != -1) {
        freeMainSprite(session->work->cursorSprite);
        session->work->cursorSprite = -1;
    }
    func_02042ee0(3, 7, 0x1C, 0xB);
}

/* The two-button prompt's buttons' callback: moves the cursor, and on a pick
 * goes on to session state 0x136 (the first button) or 0x140. */
void onLinkPromptButton(s32 touched, s32 cursor, struct ButtonGroup *group) {
    s32 id;
    struct LinkSession *session;
    s32 changed;

    session = findTask(LINK_SESSION_TASK_ID);
    id      = getTaskId(group);
    changed = 0;
    getTouchX();
    getTouchY();
    if (touched != -1 && session->choice[0] != touched) {
        if (touched < 2) {
            session->choice[1] = session->choice[0];
            session->choice[0] = touched;
        } else {
            if (touched >= 2) {
                session->choice[1] = session->choice[0];
                session->choice[0] = 0;
            }
            setButtonGroupCursor(session->choice[0], id);
        }
        changed = 1;
    }
    if (changed != 0) {
        setMainSpritePos(session->work->cursorSprite, LINK_PROMPT_RECTS[session->choice[0] * 4] - 3,
                         LINK_PROMPT_RECTS[session->choice[0] * 4 + 1]);
    }
    if (!(getPadPressed() & 1) && takeButtonGroupTap(id) == 0) {
        return;
    }
    switch (session->choice[0]) {
        case 0:
            if (session->unk4A < 2) {
                return;
            }
            closeLinkPrompt(session);
            session->state = 0x136;
            break;
        case 1:
            closeLinkPrompt(session);
            session->state = 0x140;
            break;
    }
}

/* Frees the link session's buttons and its two sprites. */
void freeLinkSessionButtons(struct LinkSession *session) {
    s32 i;

    if (session->buttons != -1) {
        if (session->buttons != -1) {
            closeButtonGroup(session->buttons);
            session->buttons = -1;
        }
    }
    for (i = 0; i < 2; i++) {
        if (session->work->sprites[i] != -1) {
            freeMainSprite(session->work->sprites[i]);
            session->work->sprites[i] = -1;
        }
    }
}

/* Shows message 0x98 with a choice and goes on by the answer. */
void func_0206e38c(struct LinkSession *session) {
    switch (session->step) {
        case 0:
            openFarmMessage(0x98, 1, 8, 5, 5, 4);
            session->step += 1;
            break;
        case 1:
            switch (func_020ac6b8()) {
                case 0:
                    func_020ac6f8();
                    session->state += 1;
                    break;
                case 1:
                    func_020ac6f8();
                    session->state += 9;
                    break;
            }
            break;
    }
}
