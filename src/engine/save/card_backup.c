#include "engine/save/card_backup.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/ui/gauge.h"
#include "engine/window/message_box.h"
#include "menus/quests/quest_list.h"

/* Starts reading size bytes of the EEPROM at offset into buffer; 4 if the
 * backup is no EEPROM. */
s32 readEeprom(s32 offset, s32 buffer, s32 size) {
    if ((u8) func_020ec31c() != CARD_BACKUP_EEPROM) {
        return 4;
    }
    getCardLockId();
    func_020ebbe4();
    func_020ec330(offset, buffer, size, 0, 0, 1, CARD_REQ_READ_BACKUP, 1, CARD_REQUEST_MODE_RECV);
    return 0;
}

/* Starts writing size bytes of buffer to the EEPROM at offset; 4 if the
 * backup is no EEPROM. */
s32 writeEeprom(s32 offset, s32 buffer, s32 size) {
    if ((u8) func_020ec31c() != CARD_BACKUP_EEPROM) {
        return 4;
    }
    getCardLockId();
    func_020ebbe4();
    func_020ec330(buffer, offset, size, 0, 0, 1, CARD_REQ_PROGRAM_BACKUP, 10, CARD_REQUEST_MODE_SEND_VERIFY);
    return 0;
}

/* Starts reading size bytes of the flash memory at offset into buffer; 5 if
 * the backup is no flash memory. */
s32 readFlash(s32 offset, s32 buffer, s32 size) {
    if ((u8) func_020ec31c() != CARD_BACKUP_FLASH) {
        return 5;
    }
    getCardLockId();
    func_020ebbe4();
    func_020ec330(offset, buffer, size, 0, 0, 1, CARD_REQ_READ_BACKUP, 1, CARD_REQUEST_MODE_RECV);
    return 0;
}

/* Starts writing size bytes of buffer to the flash memory at offset; 5 if
 * the backup is no flash memory. */
s32 writeFlash(s32 offset, s32 buffer, s32 size) {
    if ((u8) func_020ec31c() != CARD_BACKUP_FLASH) {
        return 5;
    }
    getCardLockId();
    func_020ebbe4();
    func_020ec330(buffer, offset, size, 0, 0, 1, CARD_REQ_WRITE_BACKUP, 10, CARD_REQUEST_MODE_SEND_VERIFY);
    return 0;
}

/* Writes a signature, cut to 7 characters, into the 8 bytes at 0x10 of the
 * save. */
void writeSaveSignature(s32 save, u8 *signature) {
    s32 length;

    length = func_020348e4(signature);
    func_020e23c0(save + 0x10, 0, 8);
    if ((u32) length > 7U) {
        func_020347b8(save + 0x10, signature, 7);
        return;
    }
    func_0203481c(save + 0x10, signature);
}

/* The backup's page size (func_020ec2f4), once it is ready. */
s32 getBackupPageSize(void) {
    if (CARD_BACKUP.state != 1) {
        return 0;
    }
    return func_020ec2f4();
}

/* The last request's result. */
s32 getBackupResult(void) {
    return CARD_BACKUP.result;
}

/* Whether the backup's requests are done. */
s32 isBackupDone(void) {
    if (CARD_BACKUP.state == 2) {
        return 1;
    }
    return 0;
}

/* Whether the backup's requests are done or have failed. */
s32 isBackupFinished(void) {
    s32 state = CARD_BACKUP.state;

    if (state == 2) {
        return 1;
    }
    return state == -1;
}

/* Takes a new lock id for the card (func_020e2d7c); 0 if there is none to
 * take. */
s32 takeCardLock(void) {
    s32 lockId;

    releaseCardLock();
    lockId = func_020e2d7c();
    if (lockId == -3) {
        CARD_BACKUP.lockId = 0;
        return 0;
    }
    CARD_BACKUP.lockId = lockId;
    return 1;
}

/* Gives back the card's lock id, if it has one. */
void releaseCardLock(void) {
    if ((CARD_BACKUP.lockId != -3) && (CARD_BACKUP.lockId != 0)) {
        func_020e2dd4((u16) CARD_BACKUP.lockId);
    }
    CARD_BACKUP.lockId = 0;
}

/* The card's lock id. */
u16 getCardLockId(void) {
    return (u16) CARD_BACKUP.lockId;
}

/* Whether the card's request is done (func_020ec1a0); if so, keeps func_020ebc34's and unlocks the card. */
s32 func_0207bdf4(void) {
    s32 done;

    done = func_020ec1a0();
    if (done != 0) {
        CARD_BACKUP.unk8 = func_020ebc34();
        func_020ebbd4((u16) CARD_BACKUP.lockId);
    }
    return done;
}

/* Starts the backup's requests from the first chunk. */
void startBackupRequests(void) {
    CARD_BACKUP.chunk = 0;
    CARD_BACKUP.unk40 = -1;
    CARD_BACKUP.unk44 = -1;
    requestNextBackupChunk();
}

/* Requests the next chunk: 1 started, -1 failed, 0 none left. */
s32 requestNextBackupChunk(void) {
    s32 offset;
    s32 result;
    s32 started;

    if (CARD_BACKUP.chunk < CARD_BACKUP.chunkCount) {
        offset             = CARD_BACKUP.chunk * CARD_BACKUP.stride;
        CARD_BACKUP.offset = offset;
        CARD_BACKUP.chunk  = CARD_BACKUP.chunk + 1;
        result             = CARD_BACKUP.request(offset, CARD_BACKUP.buffer, 0x20);
        CARD_BACKUP.result = result;
        if (result != 0) {
            started           = -1;
            CARD_BACKUP.state = -1;
        } else {
            started           = 1;
            CARD_BACKUP.unk4C = 1;
            CARD_BACKUP.unk50 = 3;
        }
        return started;
    }
    return 0;
}

/* Whether the backup's unk38 is -1. */
s32 func_0207b82c(void) {
    if (CARD_BACKUP.unk38 == -1) {
        return 1;
    }
    return 0;
}

/* Opens the quest screen. */
void openQuestScreen(void) {
    struct QuestScreen *screen;

    screen               = createTask(&runQuestScreen, 0x114);
    QUEST_SCREEN_TASK_ID = getTaskId(screen);
    screen->state        = 0;
    screen->unk1E        = 0;
    setUiFlag(UI_FLAG_QUEST_SCREEN);
}

/* Whether the quest screen is open. */
s32 isQuestScreenOpen(void) {
    if (getUiFlag(UI_FLAG_QUEST_SCREEN) != 0) {
        return 1;
    }
    return 0;
}

/* Closes the quest screen: its palettes, fonts and characters. */
void closeQuestScreen(void) {
    struct QuestScreen *screen;

    screen = findTask(QUEST_SCREEN_TASK_ID);
    stopMainPaletteEffects(screen->unk26);
    stopSubPaletteEffects(screen->unk27);
    func_020a98a8(1);
    func_020a98a8(2);
    func_020a9844(1);
    func_020a9844(2);
    func_0208577c(3, screen->unk24);
    func_02085710(3, screen->unk25);
    endTask(screen);
    func_020ac1f8();
    func_020ac1cc();
    QUEST_SCREEN_TASK_ID = 0;
    clearUiFlag(UI_FLAG_QUEST_SCREEN);
}

/* Opens the quest list. */
void openQuestList(s8 unk21, s8 unk22) {
    struct QuestList *list;

    list               = createTask(&runQuestList, 0x115);
    QUEST_LIST_TASK_ID = getTaskId(list);
    list->state        = 0;
    list->unk1E        = 0;
    list->unk21        = unk21;
    list->unk22        = unk22;
    setUiFlag(UI_FLAG_QUEST_LIST);
}
