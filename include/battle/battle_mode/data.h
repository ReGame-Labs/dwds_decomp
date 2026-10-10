#ifndef BATTLE_BATTLE_MODE_DATA_H
#define BATTLE_BATTLE_MODE_DATA_H

/* The battle overlay's (ov002) types and data: the battle's state and its
 * task, its units and turn order, the panels, numbers and popups of its
 * screens, and the link battle's preparation. */

#include "engine/data.h"
#include "nitro/fs.h"
#include "nitro/gx.h"
#include "types.h"

/* The battle's units: the party's are 0 to 5 and the enemy's 6 to 11. */
#define BATTLE_UNIT_COUNT 12
#define UNITS_PER_SIDE 6
#define LAST_ALLY_UNIT 5
#define FIRST_ENEMY_UNIT 6
#define LAST_ENEMY_UNIT 11

/* The turn order is a ring of 200 turns. */
#define TURN_COUNT 200

/* The numbers of the battle's table of random numbers. */
#define BATTLE_RANDOM_COUNT 30

#define DELAYED_VALUE_COUNT 10
#define POPUP_COUNT 12
#define POPUP_SPRITE_COUNT 5
#define FLASH_COUNT 12

/* Battle.result */
enum BattleResult {
    BATTLE_WON,
    BATTLE_LOST,
    BATTLE_FLED,
};

/* The kinds of packets the two DS of a link battle send each other: the
 * preparation's state, party and option, and, in the battle, the table of
 * random numbers. */
enum LinkPacketType {
    LINK_PACKET_SETUP_STATUS = 6,
    LINK_PACKET_SETUP_PARTY,
    LINK_PACKET_SETUP_OPTION,
    LINK_PACKET_RANDOM_TABLE = 10,
};

/* LinkSetupTask.state: the party screen, then the options screen. */
enum LinkSetupState {
    LINK_SETUP_INIT_PARTY,
    LINK_SETUP_SHOW_PARTY,
    LINK_SETUP_ARRANGE_PARTY,
    LINK_SETUP_WAIT_PARTY,
    LINK_SETUP_PARTY_LINK_LOST,
    LINK_SETUP_CLOSE_PARTY,
    LINK_SETUP_INIT_OPTIONS,
    LINK_SETUP_SHOW_OPTIONS,
    LINK_SETUP_CHOOSE_OPTION,
    LINK_SETUP_WAIT_OPTION,
    LINK_SETUP_OPTION_LINK_LOST,
    LINK_SETUP_CLOSE_OPTIONS,
    LINK_SETUP_END,
};

/* The second byte of the state a DS sends during the preparation. */
enum LinkSetupProgress {
    LINK_SETUP_ARRANGING,
    LINK_SETUP_HAS_PARTY, /* it has the other's party */
    LINK_SETUP_CHOOSING,
    LINK_SETUP_HAS_OPTION, /* it has the other's option */
};

/* LinkSetupTask.result and LinkWaitTask.result */
enum LinkResult {
    LINK_PENDING,
    LINK_OK,
    LINK_FAILED,
};

/* The party's slots: ten, of which the party screen shows eight, the five that
 * battle and three more; and the Digimon a DS sends of the five. */
#define LINK_PARTY_SLOT_COUNT 10
#define LINK_BATTLE_SLOT_COUNT 5
#define LINK_PARTY_DIGIMON_COUNT 3

/* LinkSetupTask.held when no Digimon is held */
#define LINK_NOT_HELD 0xFF

/* A background of the battle: its graphics, which loadBattleBgGraphics loads
 * from the files of an entry of data_0213537c and freeBattleBgGraphics frees,
 * and colors set in pairs (setSkillRangeColors indexes them by the pair). */
struct BattleBg {
    /* 0x000 */ struct BgGraphics gfx;
    /* 0x018 */ u16 colors[128][2];
    /* 0x218 */ u16 unk218; /* loadMainBgChars's result, handed to func_0208577c and func_02085710 */
};

/* What the battle knows of a Digimon taking part in it. The four stats are
 * each the sum of three parts. */
struct BattleStats {
    /* 0x00 */ s32 id; /* getSpeciesStage gives its stage, func_020a14e8 its enemy data */
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06[6];
    /* 0x0C */ s32 hp;
    /* 0x10 */ s32 maxHp;
    /* 0x14 */ s32 mp;
    /* 0x18 */ s32 maxMp;
    /* 0x1C */ u8 unk1C[0x2A];
    /* 0x46 */ s16 abilities[4]; /* ids of data_0210c11c, -1 for none */
    /* 0x4E */ u8 unk4E[2];
    /* 0x50 */ u32 turnInterval;
    /* 0x54 */ u32 nextTurn; /* the time of its next turn */
    /* 0x58 */ u8 unk58;     /* 0xFF for none */
    /* 0x59 */ u8 unk59;
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ u8 unk5C[4];
    /* 0x60 */ s16 statParts[4][3];
    /* 0x78 */ u8 unk78[0x42];
    /* 0xBA */ u16 unkBA;
    /* 0xBC */ s16 unkBC;
    /* 0xBE */ u8 unkBE[6];
};

/* The battle's task, which startBattleTask starts. */
struct BattleTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u8 phase;
    /* 0x1D */ u8 step;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ u8 turn; /* the entry of the turn order being played */
    /* 0x21 */ u8 unk21[0xA];
    /* 0x2B */ s8 received; /* 1 the table of random numbers, 2 unk3DF0 */
    /* 0x2C */ u8 packetType; /* of the last packet from the other DS */
    /* 0x2D */ u8 unk2D[0x17];
    /* 0x44 */ s8 unk44;
};

/* Where a text window goes and how it is set up, copied into the window by
 * copyWindowLayout before func_020a6b10 allocates it. */
struct WindowLayout {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ struct TextWindow window;
};

/* The task that scrolls the battle map, tickMapScrollTask. */
struct MapScrollTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u16 step;
};

/* A place on the battlefield: 0 to 5 the party's side, 6 to 11 the enemy's. */
struct BattleUnit {
    /* 0x00 */ s8 unk00; /* -1 for an empty place */
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ s32 unk04; /* an ally's Digimon id (getDigimon), an enemy's id for func_020a14e8 */
    /* 0x08 */ struct BattleStats stats;
};

/* An entry of the turn order: the unit that plays and when. */
struct Turn {
    /* 0x0 */ s8 unit;
    /* 0x4 */ u32 time;
};

/* The parameters of a G2_SetBlendAlpha call. */
struct BlendAlpha {
    /* 0x0 */ s32 plane1;
    /* 0x4 */ s32 plane2;
    /* 0x8 */ s32 ev1;
    /* 0xC */ s32 ev2;
};

/* A value for playSound, handed to it once its frames have run out. */
struct DelayedValue {
    /* 0x0 */ s16 value; /* -1 when free */
    /* 0x2 */ u16 frames;
};

/* A panel of the lower screen about a member of the party. */
struct BattlePanel {
    /* 0x000 */ u8 flags;
    /* 0x001 */ u8 unk01[0x5B];
    /* 0x05C */ struct TextWindow text[2];
    /* 0x0AC */ struct NumberSprite numbers[2];
    /* 0x1F4 */ u8 unk1F4[4];
};

/* A number shown over an enemy. */
struct UnitNumber {
    /* 0x0 */ u8 state; /* 0 unused, 1 shown, 2 shown from the next frame */
    /* 0x1 */ u8 unit;
    /* 0x2 */ u8 unk2;
    /* 0x4 */ struct NumberSprite number;
};

/* A row of five sprites rising over the battlefield until its timer ends. */
struct Popup {
    /* 0x0 */ s8 active; /* -1 when free */
    /* 0x1 */ u8 slow;   /* rises at half the speed */
    /* 0x2 */ u8 timer;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u16 sprite; /* the first of its five sprites */
    /* 0x6 */ u8 unk6[2];
    /* 0x8 */ union Fixed16 x;
    /* 0xC */ union Fixed16 y;
};

/* An enemy's palette flashing toward a color while its timer runs. */
struct Flash {
    /* 0x0 */ s8 unit; /* -1 when free */
    /* 0x1 */ u8 timer;
    /* 0x2 */ u16 color;
};

/* A unit waiting for the main screen's palette effect it started to end. */
struct UnitWait {
    /* 0x0 */ s8 unit; /* -1 when free */
    /* 0x1 */ u8 effect; /* the palette effect */
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 timer;
};

/* A packet received from the other DS in a link battle: size bytes to copy at
 * offset into the block that type names. */
struct LinkPacket {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ u8 type;
    /* 0x5 */ u8 size;
    /* 0x6 */ u16 offset;
    /* 0x8 */ u8 data[1];
};

/* The task that waits for the link to the other DS before a link battle,
 * tickLinkWaitTask. */
struct LinkWaitTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u8 state;
    /* 0x1D */ u8 result; /* enum LinkResult; copied to LINK_WAIT_RESULT at the end */
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ s32 wait;
};

/* A background picture of the link battle's preparation, of the main screen
 * in data_ov002_022626f4 and of the sub screen in data_ov002_02262f74. */
struct LinkBg {
    /* 0x0 */ u8 loaded;
    /* 0x1 */ u8 layer; /* the background it is drawn on */
    /* 0x2 */ u8 unk2[2];
    /* 0x4 */ struct BattleBg data;
};

/* Where a struct LinkBg comes from: the background it goes on, the entry of
 * data_0213537c with its files and where on the screen it is drawn, in
 * tiles. */
struct LinkBgSource {
    /* 0x0 */ u8 layer;
    /* 0x4 */ s32 file;
    /* 0x8 */ s16 x;
    /* 0xA */ s16 y;
};

/* What a DS sends the other of its party in a link battle's preparation. */
struct LinkParty {
    /* 0x000 */ s32 ids[LINK_BATTLE_SLOT_COUNT]; /* the party's first five slots, 0 for none */
    /* 0x014 */ struct Digimon digimon[LINK_PARTY_DIGIMON_COUNT]; /* those of the slots, in order */
    /* 0x494 */ u16 items[3][LINK_PARTY_DIGIMON_COUNT]; /* each Digimon's item in each equip slot, 0xFFFF for none */
};

/* The task that prepares a link battle, tickLinkSetupTask. Each player
 * arranges the party and then picks one of four options, and each DS sends
 * the other its state, its party and its option through the buffers. */
struct LinkSetupTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ u8 state; /* enum LinkSetupState */
    /* 0x1D */ u8 step;
    /* 0x1E */ u8 unk1E[2];
    /* 0x20 */ u8 result;   /* enum LinkResult; copied to LINK_SETUP_RESULT */
    /* 0x21 */ u8 send;     /* 1 the party, 2 the option; 0 the state, every frame */
    /* 0x22 */ u8 received; /* 1 the other's party, 2 its option */
    /* 0x23 */ u8 unk23;
    /* 0x24 */ s32 packetType; /* of the last packet from the other DS */
    /* 0x28 */ u8 linkLost;    /* 1 once the link is lost, 2 once the screen has gone */
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A[2];
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ u8 showStep;    /* of showing the Digimon under the cursor, 0 when done */
    /* 0x3D */ u8 statusShown; /* the status of the Digimon under the cursor is drawn */
    /* 0x3E */ s16 showWait;   /* frames before its picture */
    /* 0x40 */ s32 unk40;      /* the Digimon's unk4, for func_020a31d8 */
    /* 0x44 */ u8 cursor;
    /* 0x45 */ u8 held; /* the slot of the Digimon picked up to be moved, LINK_NOT_HELD for none */
    /* 0x46 */ u8 holding;
    /* 0x47 */ u8 flash; /* the held Digimon's flash, 0x80 set while it fades back */
    /* 0x48 */ s32 party[LINK_PARTY_SLOT_COUNT]; /* ids for getDigimon, 0 for none; the first 5 battle */
    /* 0x70 */ u8 *status; /* the state and enum LinkSetupProgress, sent each frame */
    /* 0x74 */ u8 *otherStatus;
    /* 0x78 */ struct LinkParty *partyData;
    /* 0x7C */ struct LinkParty *otherPartyData;
    /* 0x80 */ u8 *option;
    /* 0x84 */ u8 *otherOption;
    /* 0x88 */ s32 wait;
};

/* The battle's state, in data_ov002_0225b488 and reached through
 * BATTLE. */
struct Battle {
    /* 0x0000 */ u8 unk0000[0x18];
    /* 0x0018 */ struct BattleBg bg[4];
    /* 0x0888 */ u8 unk0888[4];
    /* 0x088C */ struct BattleBg unk088C;
    /* 0x0AA8 */ struct BattleBg unk0AA8;
    /* 0x0CC4 */ struct BattleBg unk0CC4;
    /* 0x0EE0 */ struct BattleBg unk0EE0;
    /* 0x10FC */ struct BattleBg unk10FC;
    /* 0x1318 */ struct BattleBg unk1318;
    /* 0x1534 */ struct BattleBg unk1534;
    /* 0x1750 */ struct BattleBg unk1750; /* colors[0..4]: the five marks of a skill's range */
    /* 0x196C */ struct BattleBg unk196C; /* the same marks */
    /* 0x1B88 */ u8 unk1B88[0x10E8];
    /* 0x2C70 */ struct BattleUnit units[BATTLE_UNIT_COUNT];
    /* 0x3600 */ u8 unk3600[0x1B0];
    /* 0x37B0 */ struct Turn turns[TURN_COUNT];
    /* 0x3DF0 */ u8 unk3DF0[0xC];
    /* 0x3DFC */ s8 actor;
    /* 0x3DFD */ u8 unk3DFD;
    /* 0x3DFE */ u16 unk3DFE;
    /* 0x3E00 */ u8 unk3E00[0x43];
    /* 0x3E43 */ u8 unk3E43;
    /* 0x3E44 */ u8 unk3E44[0x27E];
    /* 0x40C2 */ u8 randomIndex;
    /* 0x40C3 */ u8 unk40C3;
    /* 0x40C4 */ u16 randomTable[BATTLE_RANDOM_COUNT]; /* received from the other DS in a link battle */
    /* 0x4100 */ u8 unk4100[0x42C];
    /* 0x452C */ enum GXDispSelect dispSelect;
    /* 0x4530 */ u8 unk4530[2];
    /* 0x4532 */ s8 subBg3Setup; /* 0 to 2, set by func_ov002_0224bca8 at the vblank */
    /* 0x4533 */ s8 unk4533;
    /* 0x4534 */ struct BlendAlpha mainBlend;
    /* 0x4544 */ struct BlendAlpha subBlend;
    /* 0x4554 */ u8 unk4554[0xE];
    /* 0x4562 */ s8 unk4562;
    /* 0x4563 */ s8 unk4563;
    /* 0x4564 */ s16 maxScrollX;
    /* 0x4566 */ s16 maxScrollY;
    /* 0x4568 */ u8 unk4568[0x14];
    /* 0x457C */ struct DelayedValue delayedValues[DELAYED_VALUE_COUNT];
    /* 0x45A4 */ u8 unk45A4[4];
    /* 0x45A8 */ struct BattlePanel panels[3];
    /* 0x4B90 */ u8 unk4B90;
    /* 0x4B91 */ s8 unk4B91;
    /* 0x4B92 */ u8 unk4B92[6];
    /* 0x4B98 */ struct TextWindow windows[22];
    /* 0x4F08 */ u8 unk4F08[0x556];
    /* 0x545E */ u8 unk545E;
    /* 0x545F */ u8 unk545F[0xF0D];
    /* 0x636C */ struct UnitNumber unitNumbers[6];
    /* 0x675C */ u8 unk675C[0xE];
    /* 0x676A */ u8 messageTimer;
    /* 0x676B */ u8 unk676B[0x11];
    /* 0x677C */ struct Popup popups[POPUP_COUNT];
    /* 0x683C */ u8 unk683C[0x1B0];
    /* 0x69EC */ struct Flash flashes[FLASH_COUNT];
    /* 0x6A1C */ s8 animResets[6]; /* characters set back to sequence 0 once their animation ends */
    /* 0x6A22 */ struct UnitWait removals[6]; /* character and sprite taken off once effect and timer end */
    /* 0x6A3A */ struct UnitWait reveals[6];  /* sprite shown again once the effect ends */
    /* 0x6A52 */ u8 unk6A52[0xBF];
    /* 0x6B11 */ s8 result; /* enum BattleResult */
    /* 0x6B12 */ u8 unk6B12[0xFA];
    /* 0x6C0C */ s16 bits; /* the Bits the enemies beaten give */
    /* 0x6C0E */ u8 unk6C0E[0x32];
    /* 0x6C40 */ s32 exp; /* the EXP the enemies beaten give */
    /* 0x6C44 */ u8 unk6C44[0x388];
    /* 0x6FCC */ u8 unk6FCC[3];
    /* 0x6FCF */ u8 unk6FCF;
    /* 0x6FD0 */ s8 linkBattleLost; /* 1 lost, 0 won */
    /* 0x6FD1 */ u8 unk6FD1;
    /* 0x6FD2 */ s16 wins;   /* addLinkWins's count after a link battle, probably the wins */
    /* 0x6FD4 */ s16 losses; /* addLinkLosses's, probably the losses */
};

extern struct Battle *BATTLE;
extern struct UnitPanel data_ov002_0225a9e8[5]; /* the panels after the first */
extern struct Battle data_ov002_0225b488;
extern struct FSFile data_ov002_02262488;
extern struct BattleBg data_ov002_022624d8;
extern struct LinkBg data_ov002_022626f4[4];
extern struct LinkBg data_ov002_02262f74[4];
extern struct LinkBgSource data_ov002_0225a5ec[2]; /* the options screen's, main screen */
extern struct LinkBgSource data_ov002_0225a604[2]; /* the options screen's, sub screen */
extern u8 data_ov002_0225a5c0; /* frames before the X button works again */
extern struct TouchRect data_ov002_0225a5c4[1];  /* the party screen's OK button */
extern struct TouchRect data_ov002_0225a710[10]; /* the party slots, the last two unused */
extern u8 LINK_SETUP_RESULT;
extern u8 LINK_WAIT_RESULT;
extern struct UnitPanel data_ov002_0225a7c8; /* the first unit's panel */
extern struct TouchRect data_ov002_0225a5cc[1];
extern struct TouchRect data_ov002_0225a61c[4];
extern struct WindowLayout data_ov002_0225a660;
extern struct WindowLayout data_ov002_0225a68c;
extern struct WindowLayout data_ov002_0225a6e4;
extern void *BATTLE_MOVIE_GRAPHICS[];

#endif /* BATTLE_BATTLE_MODE_DATA_H */
