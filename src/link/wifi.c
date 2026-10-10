#include "link/wifi.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "farm/farm_task.h"
#include "link/link_start.h"
#include "link/sjis.h"
#include "link/wifi_matching.h"

/* The allocator allocLinkWork hands the Wi-Fi library (func_020f9b00): a
 * zeroed block, with the interrupts off. The kind of block is ignored. */
void *allocWifiBlock(s32 kind, u32 size, s32 align) {
    s32 saved;
    void *block;

    saved = func_020e5e04();
    block = heapAllocZeroed(size, align);
    func_020e5e18(saved);
    return block;
}

/* Empty. */
void func_020b60d0(void) {}

/* Empty: the callback func_020b551c hands the parent setup. */
void func_020b60cc(void) {}

/* Empty: a callback func_020b5e44 registers with func_020ee16c. */
void func_020b5ef4(void) {}

/* Sets the link's work, the block allocLinkWork allocates. */
void setLinkWork(void *work) {
    LINK_WORK = work;
}

/* The state of the link, which func_020b551c steps through. */
s32 getLinkState(void) {
    return LINK_STATE;
}

/* Sets the state of the link. */
void setLinkState(s32 state) {
    LINK_STATE = state;
}

/* Whether the link goes over Nintendo Wi-Fi Connection (1) or is local (0). */
s32 isWifiLink(void) {
    return LINK_OVER_WIFI;
}

/* Whether the link is local. */
s32 isLocalLink(void) {
    if (LINK_OVER_WIFI == 0) {
        return 1;
    }
    return 0;
}

/* Makes the link go over Nintendo Wi-Fi Connection. */
void useWifiLink(void) {
    LINK_OVER_WIFI = 1;
}

/* Makes the link local. */
void useLocalLink(void) {
    LINK_OVER_WIFI = 0;
}

/* The tgid of the local link (strongly inferred: it goes with the GGID to
 * func_020b551c's parent setup). */
u16 getTgid(void) {
    return getLinkWork()->tgid;
}

/* Takes a new tgid from func_020e9340. */
void updateTgid(void) {
    struct LinkWork *work = getLinkWork();

    work->tgid = func_020e9340();
}

/* The GGID of the local link (strongly inferred: func_020b551c hands it to the
 * parent setup with the beacon info). */
s32 getGgid(void) {
    return 0x400221;
}

/* The local link's unk774. */
s32 func_020b65cc(void) {
    return getLinkWork()->unk774;
}

/* Sets the local link's unk774. */
void func_020b65b8(s32 value) {
    getLinkWork()->unk774 = value;
}

/* The local link's unk770; link/exchange.c reads the packet of aid 1 when it is
 * 1, else that of aid 0. */
s32 func_020b65a0(void) {
    return getLinkWork()->unk770;
}

/* Sets the local link's unk770. */
void func_020b658c(s32 value) {
    getLinkWork()->unk770 = value;
}

/* The index-th parent found by the scan. */
struct BssDesc *getScannedParent(s32 index) {
    return &getLinkWork()->parents[index];
}

/* Whether the scan found an index-th parent. */
BOOL hasScannedParent(s32 index) {
    if (getScannedParent(index)->length != 0) {
        return TRUE;
    }
    return FALSE;
}

/* Takes unk768, clearing it. */
s32 func_020b652c(void) {
    s32 value = getLinkWork()->unk768;

    getLinkWork()->unk768 = 0;
    return value;
}

/* Sets the local link's unk768, which func_020b652c takes. */
void func_020b6518(s32 value) {
    getLinkWork()->unk768 = value;
}

/* Sets the index-th of the local link's unk700 to 0xF0. */
void func_020b64f8(s32 index) {
    getLinkWork()->unk700[index] = 0xF0;
}

/* Clears the index-th of the local link's unk700. */
void func_020b64d8(s32 index) {
    getLinkWork()->unk700[index] = 0;
}

/* The game's own beacon info. */
struct LinkGameInfo *getLinkGameInfo(void) {
    return &getLinkWork()->gameInfo;
}

/* The packet to send this frame (tickLinkTransfer fills it). */
void *getSendPacket(void) {
    return getLinkWork()->sendPacket;
}

/* The packet last received from the DS with the id. */
void *getReceivedPacket(s32 aid) {
    return getLinkWork()->packets[aid];
}

/* The local link's unk708, 0 when there's no work. */
s32 func_020b640c(void) {
    if (getLinkWork() == NULL) {
        return 0;
    }
    return getLinkWork()->unk708;
}

/* Sets the local link's unk708. */
void func_020b63f8(s32 value) {
    getLinkWork()->unk708 = value;
}

/* Whether the Wi-Fi link's unk8DC4 is 3. */
s32 func_020b63d0(void) {
    if (getWifiWork()->unk8DC4 == 3) {
        return 1;
    }
    return 0;
}

/* Calls getWifiWork; a tail call, so it may return the Wi-Fi work. */
void func_020b63c4(void) {
    getWifiWork();
}

/* The user data of the Wi-Fi library (strongly inferred to be
 * DWCUserData). It is an s32 because link/wifi_matching.c keeps it in one. */
s32 func_020b63ac(void) {
    return (s32) getWifiWork()->userData;
}

/* The user data of the Wi-Fi library. */
void *getUserData(void) {
    return getWifiWork()->userData;
}

/* The Wi-Fi link's unk740. */
void *func_020b637c(void) {
    return getWifiWork()->unk740;
}

/* Makes the user data anew for the game code (func_020ff12c, strongly
 * inferred to be DWC_CreateUserData). */
void createUserData(void) {
    func_020ff12c(getUserData(), GAME_CODE);
}

/* Hands the user data to func_020fefac. */
void func_020b6344(void) {
    func_020fefac(getUserData());
}

/* Checks the user data: 1 when func_020ff0e4 finds it isn't valid, 0 when
 * func_020ff038 returns 1, else 2. */
s32 func_020b6308(void) {
    if (func_020ff0e4(getUserData()) == 0) {
        return 1;
    }
    if (func_020ff038(getUserData()) == 1) {
        return 0;
    }
    return 2;
}

/* The Wi-Fi link's index-th buffer of 0x7800 bytes. */
void *func_020b62e4(s32 index) {
    return getWifiWork()->unk15C4[index];
}

/* The Wi-Fi link's unk800. */
void *func_020b62cc(void) {
    return getWifiWork()->unk800;
}

/* The Wi-Fi link's unk80C. */
void *func_020b62ac(void) {
    return getWifiWork()->unk80C;
}

/* The Wi-Fi link's unk8DC8, set by func_020b5ebc. */
s32 func_020b6290(void) {
    return getWifiWork()->unk8DC8;
}

/* Sets the Wi-Fi link's unk8DC8. */
void func_020b6278(s32 value) {
    getWifiWork()->unk8DC8 = value;
}

/* The Wi-Fi link's unk8DCC. */
s32 func_020b625c(void) {
    return getWifiWork()->unk8DCC;
}

/* Sets the Wi-Fi link's unk8DCC. */
void func_020b6244(s32 value) {
    getWifiWork()->unk8DCC = value;
}

/* The Wi-Fi link's unk8DD0, set by func_020b5ebc. */
s32 func_020b6228(void) {
    return getWifiWork()->unk8DD0;
}

/* Sets the Wi-Fi link's unk8DD0. */
void func_020b6210(s32 value) {
    getWifiWork()->unk8DD0 = value;
}

/* Sets the Wi-Fi link's unk8DD4. */
void func_020b61f8(s32 value) {
    getWifiWork()->unk8DD4 = value;
}

/* 1 when the Wi-Fi link's unk8DD0 is set, else what func_020fefd0 says of the
 * user data. */
s32 func_020b61cc(void) {
    if (func_020b6228() != 0) {
        return 1;
    }
    return func_020fefd0(getUserData());
}

/* Allocates the work of the link: the small one for a local link, or the
 * Wi-Fi one, which also hands the library its allocator. */
void allocLinkWork(void) {
    void *work;

    if (isLocalLink()) {
        work = allocWifiBlock(6, sizeof(struct LinkWork), 32);
    } else {
        work = allocWifiBlock(6, sizeof(struct WifiWork), 32);
        func_020f9b00(allocWifiBlock, &freeWifiBlock);
    }
    setLinkWork(work);
}

/* Frees the link's work. */
void freeLinkWork(void) {
    freeWifiBlock(6, getLinkWork(), 0);
    setLinkWork(0);
}

/* Calls func_020b6c30. */
void func_020b60c0(void) {
    func_020b6c30();
}

/* Forgets the parents the scan found. */
void clearScannedParents(void) {
    s32 i;

    i = 0;
    do {
        getScannedParent(i)->length = 0;
        func_020b64d8(i);
        i += 1;
    } while (i < 4);
    func_020b6518(1);
}

/* The Wi-Fi library's callback that raises func_020b2990's flag (registered by
 * func_020b5e44). */
void func_020b5f0c(void) {
    func_020b29f0();
}

/* A callback of func_020ee3f0, registered by func_020b5e44: calls
 * func_02072718. */
void func_020b5ee8(void) {
    func_02072718();
}

/* A callback of func_020ee3f0: on success, keeps the value in unk8DD0 and sets
 * unk8DC8. */
void func_020b5ebc(s32 error, s32 value) {
    if (error != 0) {
        return;
    }
    func_020b6210(value);
    func_020b6278(1);
}

/* On success, keeps the value in unk8DD4 and registers the Wi-Fi library's
 * callbacks. */
void func_020b5e44(s32 error, s32 value) {
    if (error != 0) {
        return;
    }
    func_020b61f8(value);
    func_020ee16c(&func_020b5ef4, 0);
    func_020ee3f0(0, &func_020b5ebc, 0, 0, 0, &func_020b5ee8, 0);
    func_020f93a4(&func_020b5f0c);
    func_020f9384(&func_020b5ef8);
}

/* Calls func_020ee0f4 and then func_02079390. */
void func_020b5e2c(void) {
    func_020ee0f4();
    func_02079390();
}

/* The state of the link. */
s32 func_020b599c(void) {
    return getLinkState();
}

/* Frees the link's work and puts the link in state 0. */
void func_020b5980(void) {
    freeLinkWork();
    setLinkState(0);
}

/* Puts the link in state 0. */
void func_020b5970(void) {
    setLinkState(0);
}

/* Calls func_020b6d70 and puts the link in state 0x10. */
void func_020b5954(void) {
    func_020b6d70();
    setLinkState(0x10);
}

/* The Wi-Fi error code (0 in a local link), positive. */
s32 getWifiErrorCode(void) {
    if (isLocalLink() != 0) {
        return 0;
    }
    return 0 - getWifiWork()->errorCode;
}

/* Sorts the Wi-Fi error code into the kinds of error the game tells apart,
 * 1 for any other. */
s32 getWifiErrorKind(void) {
    s32 code;

    code = 0 - getWifiWork()->errorCode;
    if (code == 0x4E8C) {
        return 2;
    }
    if (code == 0x4E8E) {
        return 3;
    }
    if ((code == 0xC79B) || ((code >= 0xC79C) && (code <= 0xC79E)) || ((code >= 0xC7A0) && (code <= 0xC7FE)) ||
        ((code >= 0xC864) && (code <= 0xC866)) || ((code >= 0xC867) && (code <= 0xC8C6))) {
        return 4;
    }
    if (((code >= 0xCB20) && (code <= 0xCB23)) || ((code >= 0xCB84) && (code <= 0xCB87)) ||
        ((code >= 0xCBE8) && (code <= 0xCBEB))) {
        return 5;
    }
    if (code == 0xC79F) {
        return 6;
    }
    if ((code >= 0xC350) && (code <= 0xC3B3)) {
        return 7;
    }
    if ((code == 0x4E85) || ((code >= 0x59D8) && (code <= 0x5DBF))) {
        return 8;
    }
    if ((code >= 0xC800) && (code <= 0xC863)) {
        return 9;
    }
    if ((code >= 0xEA60) && (code <= 0x1869F)) {
        return 0xA;
    }
    return 1;
}

/* 0 while the link is in state 0, else what func_020e966c (local) or
 * func_020f9b1c (Wi-Fi) returns. */
s32 func_020b5288(void) {
    if (getLinkState() == 0) {
        return 0;
    }
    if (isLocalLink() != 0) {
        return func_020e966c();
    }
    return func_020f9b1c();
}

/* func_020b7604's bitmap of the DS linked. */
void func_020b527c(void) {
    func_020b7604();
}

/* How many DS are linked: the bits of func_020b7604's bitmap
 * (func_020dc820 counts them). */
s32 countLinkedConsoles(void) {
    return func_020dc820(func_020b7604());
}

/* The unk18 of the beacon info of the index-th parent found. */
void *func_020b5248(s32 index) {
    return ((struct LinkGameInfo *) getScannedParent(index)->userGameInfo)->unk18;
}

/* The unk18 of the game's own beacon info. */
void *func_020b5230(void) {
    return getLinkGameInfo()->unk18;
}

/* Hands the two values to func_020f9424 with func_020edfb4's result. */
void func_020b5208(s32 unk1, s32 unk2) {
    func_020f9424(func_020edfb4(), unk1, unk2);
}

/* Fills data_021e5d00 from the user data (func_020fedb8), making the user data
 * first if it isn't valid. */
s32 *func_020b51c4(void *userData) {
    if (func_020ff0e4(userData) == 0) {
        func_020ff12c(userData, GAME_CODE);
        func_020fefac(userData);
    }
    func_020fedb8(userData, &data_021e5d00);
    return &data_021e5d00;
}

/* Hands the user data to func_020fee60, making it first if it isn't valid. */
void func_020b50f0(void *userData) {
    if (func_020ff0e4(userData) == 0) {
        func_020ff12c(userData, GAME_CODE);
        func_020fefac(userData);
    }
    func_020fee60(userData);
}

/* 3 when func_020ff4ec fails; else fills data_021e5d00 with func_020fee20 and
 * hands it to func_020b5128. */
s32 func_020b50ac(s32 unk0, s32 unk1, s32 unk2) {
    if (func_020ff4ec() == 0) {
        return 3;
    }
    func_020fee20(&data_021e5d00, unk1, unk2);
    return func_020b5128(unk0, &data_021e5d00);
}
