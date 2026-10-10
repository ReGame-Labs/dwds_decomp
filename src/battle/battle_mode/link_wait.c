#include "battle/battle_mode/link_wait.h"
#include "battle/battle_mode/data.h"
#include "battle/battle_mode/link_setup.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "link/link_session.h"
#include "link/link_start.h"
#include "title/title_menu.h"

/* Starts the wait for the link to the other DS. */
void startLinkWaitTask(void) {
    struct LinkWaitTask *task;

    task             = createTask(&tickLinkWaitTask, 0x117);
    task->state      = 0;
    task->result     = LINK_PENDING;
    LINK_WAIT_RESULT = task->result;
}

/* The link's result: LINK_PENDING until known, then LINK_OK or LINK_FAILED. */
u8 getLinkWaitResult(void) {
    return LINK_WAIT_RESULT;
}

/* Starts the preparation of a link battle, with the buffers it trades with
 * the other DS. */
void startLinkSetupTask(void) {
    struct LinkSetupTask *task;

    task                 = createTask(&tickLinkSetupTask, 0x117);
    task->state          = LINK_SETUP_INIT_PARTY;
    task->step           = 0;
    task->send           = 0;
    task->received       = 0;
    task->unk23          = 0;
    task->linkLost       = 0;
    task->status         = heapAlloc(2, 4);
    task->otherStatus    = heapAlloc(2, 4);
    task->partyData      = heapAlloc(sizeof(struct LinkParty), 4);
    task->otherPartyData = heapAlloc(sizeof(struct LinkParty), 4);
    task->option         = heapAlloc(1, 4);
    task->otherOption    = heapAlloc(1, 4);
    func_020aa340(0, 1);
    LINK_SETUP_RESULT = LINK_PENDING;
}

/* The preparation's result: LINK_PENDING until it ends, then LINK_OK to
 * battle or LINK_FAILED if the link was lost. */
u8 getLinkSetupResult(void) {
    return LINK_SETUP_RESULT;
}

/* Starts the link and waits for it: the result is LINK_FAILED if it fails,
 * and LINK_OK once it holds after five frames more. */
void tickLinkWaitTask(void) {
    struct LinkWaitTask *task = (struct LinkWaitTask *) getCurrentTask();
    s32 link                  = func_02071b5c();

    switch (task->state) {
        case 0:
            playBgm(16);
            task->state = 1;
            break;
        case 1:
            func_020722f0(3);
            task->state = 2;
            break;
        case 2:
            if (link == 3) {
                func_02071b4c();
                task->result = LINK_FAILED;
                task->state  = 4;
            } else if (link == 2) {
                func_02071b4c();
                task->result = LINK_FAILED;
                task->state  = 4;
            } else if (func_02071c20() != 0) {
                task->wait = 5;
                task->state++;
            }
            break;
        case 3:
            if (task->wait > 0) {
                task->wait--;
                break;
            }
            /* A link lost now still ends as linked: the result is set over. */
            if (link == 3) {
                func_02071b4c();
                task->result = LINK_FAILED;
                task->state  = 4;
            }
            task->result = LINK_OK;
            task->state++;
            break;
        case 4:
            task->state++;
            break;
        case 5:
            LINK_WAIT_RESULT = task->result;
            endTask(task);
            task->state++;
            break;
    }
}
