#ifndef LINK_WIFI_H
#define LINK_WIFI_H

/* The link to other DS: a local one through the SDK's wireless library, or one over Nintendo Wi-Fi Connection through the
 * Wi-Fi library. */

#include "types.h"

#define GAME_CODE 0x41444E45 /* 'ADNE', the ROM's game code */

/* What the game puts in its beacon for the others to see: probably the
 * userGameInfo of the SDK's WMGameInfo. */
struct LinkGameInfo {
    /* 0x00 */ u8 unk0[0x14]; /* func_020b59a8 converts a text into it */
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15; /* the DS linked, less one */
    /* 0x16 */ u8 unk16[2];
    /* 0x18 */ u8 unk18[0x40];
};

/* A parent found by the scan: strongly inferred to be the SDK's WMBssDesc,
 * which is 0xC0 bytes, starts with its length and has the user's game info
 * at 0x50, 0x70 bytes. */
struct BssDesc {
    /* 0x00 */ u16 length; /* 0 for an empty entry */
    /* 0x02 */ u8 unk2[0x4E];
    /* 0x50 */ u16 userGameInfo[0x38]; /* a LinkGameInfo */
};

/* The work of a local link, LINK_WORK as getLinkWork returns it. */
struct LinkWork {
    /* 0x000 */ u8 sendPacket[0x48]; /* the packet to send this frame */
    /* 0x048 */ u8 unk48[0x1B8];
    /* 0x200 */ u8 packets[7][0x48]; /* the last one from each DS, by aid */
    /* 0x3F8 */ u8 unk3F8[8];
    /* 0x400 */ struct BssDesc parents[4];
    /* 0x700 */ s16 unk700[4];
    /* 0x708 */ s32 unk708;
    /* 0x70C */ struct LinkGameInfo gameInfo; /* the game's own */
    /* 0x764 */ u16 tgid; /* strongly inferred */
    /* 0x766 */ u8 unk766[2];
    /* 0x768 */ s32 unk768;
    /* 0x76C */ u8 unk76C[4];
    /* 0x770 */ s32 unk770;
    /* 0x774 */ s32 unk774;
};

/* The work of a link over Wi-Fi, LINK_WORK as getWifiWork returns
 * it. */
struct WifiWork {
    /* 0x0000 */ u8 unk0[0x700];
    /* 0x0700 */ u8 userData[0x40]; /* strongly inferred to be DWCUserData */
    /* 0x0740 */ u8 unk740[0xC0];
    /* 0x0800 */ u8 unk800[0xC];
    /* 0x080C */ u8 unk80C[0xDB8];
    /* 0x15C4 */ u8 unk15C4[1][0x7800];
    /* 0x8DC4 */ s32 unk8DC4;
    /* 0x8DC8 */ s32 unk8DC8;
    /* 0x8DCC */ s32 unk8DCC;
    /* 0x8DD0 */ s32 unk8DD0;
    /* 0x8DD4 */ s32 unk8DD4;
    /* 0x8DD8 */ s32 errorCode; /* negative */
    /* 0x8DDC */ u8 unk8DDC[4];
};

s32 func_020b50ac(s32 unk0, s32 unk1, s32 unk2);
void func_020b50f0(void *userData);
s32 func_020b5128();
s32 *func_020b51c4(void *userData);
void func_020b5208(s32 unk1, s32 unk2);
void *func_020b5230(void);
s32 countLinkedConsoles(void);
void func_020b527c(void);
s32 func_020b5288(void);
s32 getWifiErrorKind(void);
s32 getWifiErrorCode(void);
void func_020b5954(void);
void func_020b5970(void);
void func_020b5980(void);
s32 func_020b599c(void);
void func_020b5e2c(void);
void func_020b5ebc(s32 error, s32 value);
void func_020b5ee8(void);
void func_020b5ef4();
void func_020b5f0c(void);
void func_020b60c0(void);
void func_020b60cc();
void func_020b60d0();
void freeLinkWork(void);
void freeWifiBlock(s32 kind, void *block, u32 size);
s32 func_020b61cc(void);
void func_020b61f8(s32 value);
void func_020b6210(s32 value);
s32 func_020b6228(void);
void func_020b6244(s32 value);
s32 func_020b625c(void);
void func_020b6278(s32 value);
s32 func_020b6290(void);
void *func_020b62ac(void);
void *func_020b62cc(void);
s32 func_020b6308(void);
void createUserData(void);
void *func_020b637c(void);
void *getUserData(void);
s32 func_020b63ac(void);
void func_020b63c4(void);
s32 func_020b63d0(void);
void func_020b63f8(s32 value);
void *getReceivedPacket(s32 aid);
void *getSendPacket(void);
struct LinkGameInfo *getLinkGameInfo(void);
void func_020b64d8(s32 index);
void func_020b64f8(s32 index);
void func_020b6518(s32 value);
s32 func_020b652c(void);
struct BssDesc *getScannedParent(s32 index);
void func_020b658c(s32 value);
s32 func_020b65a0(void);
void func_020b65b8(s32 value);
s32 func_020b65cc(void);
s32 getGgid(void);
u16 getTgid(void);
void useLocalLink(void);
void useWifiLink(void);
s32 isLocalLink(void);
s32 isWifiLink(void);
void setLinkState(s32 state);
s32 getLinkState(void);
void setLinkWork(void *work);
void func_020b5e44(s32 error, s32 value);
s32 func_020b5ef8();
void allocLinkWork(void);
void *allocWifiBlock(s32 kind, u32 size, s32 align);
void func_020b59a8(s32 mode, s32 arg1);
void func_020b6344(void);
void clearScannedParents(void);
s32 func_020b640c(void);
BOOL hasScannedParent(s32 index);
void updateTgid(void);
void *func_020b5248(s32 index);
void *func_020b62e4(s32 index);

#endif /* LINK_WIFI_H */
