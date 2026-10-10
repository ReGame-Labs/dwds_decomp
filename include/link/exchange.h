#ifndef LINK_EXCHANGE_H
#define LINK_EXCHANGE_H

/* The exchange: the link session's task that trades Digimon or lends them for
 * training (runExchange), its fonts, and the Digimon it moves. */

#include "engine/data.h"
#include "types.h"

/* The exchange's work block, 0x13C bytes. */
struct ExchangeWork {
    /* 0x000 */ struct BgGraphics bgs[3];
    /* 0x048 */ u8 unk48[0xC8];
    /* 0x110 */ s32 sprites[3]; /* the Digimon panels' sprite slots, freed by freeSubSprite */
    /* 0x11C */ u8 unk11C[0x20];
};

/* The exchange, a task. */
struct Exchange {
    /* 0x00 */ struct Task task;
    /* 0x1C */ struct ExchangeWork *work;
    /* 0x20 */ u8 *unk20; /* filled by the partner's packets of type 2 */
    /* 0x24 */ void *unk24;
    /* 0x28 */ u8 *unk28; /* filled by the partner's packets of type 3 */
    /* 0x2C */ void *unk2C;
    /* 0x30 */ u8 unk30[4];
    /* 0x34 */ void *unk34;
    /* 0x38 */ void *unk38;
    /* 0x3C */ u8 unk3C[4];
    /* 0x40 */ void *unk40;
    /* 0x44 */ u8 unk44[8];
    /* 0x4C */ void *unk4C;
    /* 0x50 */ void *unk50;
    /* 0x54 */ void *unk54;
    /* 0x58 */ u8 unk58[0xC];
    /* 0x64 */ s8 fonts[4];   /* font slots, freed by func_020a9610 */
    /* 0x68 */ u8 windows[4]; /* window slots, or NO_WINDOW */
    /* 0x6C */ u8 unk6C[4];
    /* 0x70 */ s32 buttons; /* the Digimon panels' button group's task id, or -1 */
    /* 0x74 */ s32 unk74[2]; /* freed by stopSubPaletteEffectsButFades */
    /* 0x7C */ s32 unk7C[2]; /* freed by stopMainPaletteEffectsButFades */
};

/* A window slot that is not open (closeWindow closes the others). */
#define NO_WINDOW 0xFF

/* A packet from the partner, as getReceivedPacket returns it: size bytes of data
 * for offset in the block its type names. */
struct LinkPacket {
    /* 0x0 */ u8 unk0[4];
    /* 0x4 */ u8 type;
    /* 0x5 */ u8 size;
    /* 0x6 */ u16 offset;
    /* 0x8 */ u8 data[1];
};

extern s32 EXCHANGE_TASK_ID; /* the exchange's task id */
extern s32 EXCHANGE_ACTIVE; /* the exchange's task, 0 for none */

void freeExchangeFonts(void);
void loadExchangeFonts(void);
void receiveTrainingGuest(struct Digimon *lent, struct Digimon *guest);
void receiveTrainedDigimon(struct Digimon *guest, struct Digimon *home);
u8 readPartnerPacket(struct Exchange *exchange);

#endif /* LINK_EXCHANGE_H */
