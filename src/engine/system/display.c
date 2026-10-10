#include "engine/system/display.h"
#include "engine/bg/bg_affine.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/input/touch.h"
#include "engine/libs.h"
#include "engine/palette/palette_upload.h"
#include "engine/system/system.h"
#include "nitro/gx.h"

/* Sets the display up: the VBlank task, the VRAM transfer queue, the BG
 * layers, the palettes and the layers' priorities. */
void initDisplay(void) {
    DISPLAY_FLAGS = 0;
    func_020878d4();
    func_02087884();
    resetBgPriorities();
    clearTouch();
    createTask(&tickTouch, 2);
    ((struct StateTask *) createTask(&func_020879c4, 0xF00D))->state = 0;
    clearVramTransfers();
    func_02085c84();
    initPalettes();
    setMainBgPriorities(0, 1, 2, 3);
    setSubBgPriorities(0, 1, 2, 3);
    VBLANK_CALLBACK_COUNT = 0;
    setDisplayReady();
}

/* Gives both screens' BG layers the priority of their number. */
void resetBgPriorities(void) {
    REG_BG0CNT &= ~REG_BGCNT_PRIORITY_MASK;
    REG_BG1CNT = (REG_BG1CNT & ~REG_BGCNT_PRIORITY_MASK) | 1;
    REG_BG2CNT = (REG_BG2CNT & ~REG_BGCNT_PRIORITY_MASK) | 2;
    REG_BG3CNT = (REG_BG3CNT & ~REG_BGCNT_PRIORITY_MASK) | 3;
    REG_DB_BG0CNT &= ~REG_BGCNT_PRIORITY_MASK;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & ~REG_BGCNT_PRIORITY_MASK) | 1;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & ~REG_BGCNT_PRIORITY_MASK) | 2;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & ~REG_BGCNT_PRIORITY_MASK) | 3;
}

/* Sets display flag 2. */
void func_020878ec(void) {
    DISPLAY_FLAGS |= DISPLAY_FLAG_2;
}

/* Clears display flag 2. */
void func_020878d4(void) {
    DISPLAY_FLAGS &= ~DISPLAY_FLAG_2;
}

/* Resets the game, leaving SOFT_RESET_MAGIC for isSoftReset. */
void softReset(void) {
    func_020e5e9c(SOFT_RESET_MAGIC);
}

/* Whether the game started from a reset by softReset. */
s32 isSoftReset(void) {
    if (RESET_PARAMETER == SOFT_RESET_MAGIC) {
        return 1;
    }
    return 0;
}

/* Sets display flag 4. */
void func_02087884(void) {
    DISPLAY_FLAGS |= DISPLAY_FLAG_4;
}

/* Clears display flag 4. */
void func_0208786c(void) {
    DISPLAY_FLAGS &= ~DISPLAY_FLAG_4;
}

/* Marks the display as set up. */
void setDisplayReady(void) {
    DISPLAY_READY = 1;
}

/* Whether the display is set up. */
u8 isDisplayReady(void) {
    return DISPLAY_READY;
}

/* Sets which of the main screen's layers show, from the next VBlank. */
void setMainLayersShown(s8 layers) {
    MAIN_LAYERS_SHOWN = layers;
    addVBlankCallback(&applySetMainLayers);
}

/* Shows the main screen's layers MAIN_LAYERS_SHOWN says, at VBlank. */
void applySetMainLayers(void) {
    REG_DISPCNT = (REG_DISPCNT & ~REG_DISPCNT_DISPLAY_MASK) | (MAIN_LAYERS_SHOWN << REG_DISPCNT_DISPLAY_SHIFT);
}

/* Sets which of the sub screen's layers show, from the next VBlank. */
void setSubLayersShown(s8 layers) {
    SUB_LAYERS_SHOWN = layers;
    addVBlankCallback(&applySetSubLayers);
}

/* Shows the sub screen's layers SUB_LAYERS_SHOWN says, at VBlank. */
void applySetSubLayers(void) {
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~REG_DISPCNT_DISPLAY_MASK) | (SUB_LAYERS_SHOWN << REG_DISPCNT_DISPLAY_SHIFT);
}

/* Shows some of the main screen's layers from the next VBlank. */
void showMainLayers(s32 layers) {
    MAIN_LAYERS_SHOWN |= layers;
    addVBlankCallback(&applyShowMainLayers);
}

/* Shows the main screen's layers MAIN_LAYERS_SHOWN says, at VBlank. */
void applyShowMainLayers(void) {
    REG_DISPCNT = (REG_DISPCNT & ~REG_DISPCNT_DISPLAY_MASK) | (MAIN_LAYERS_SHOWN << REG_DISPCNT_DISPLAY_SHIFT);
}

/* Shows some of the sub screen's layers from the next VBlank. */
void showSubLayers(s32 layers) {
    SUB_LAYERS_SHOWN |= layers;
    addVBlankCallback(&applyShowSubLayers);
}

/* Shows the sub screen's layers SUB_LAYERS_SHOWN says, at VBlank. */
void applyShowSubLayers(void) {
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~REG_DISPCNT_DISPLAY_MASK) | (SUB_LAYERS_SHOWN << REG_DISPCNT_DISPLAY_SHIFT);
}

/* Hides some of the main screen's layers from the next VBlank. */
void hideMainLayers(s32 layers) {
    MAIN_LAYERS_SHOWN &= ~layers;
    addVBlankCallback(&applyHideMainLayers);
}

/* Shows the main screen's layers MAIN_LAYERS_SHOWN says, at VBlank. */
void applyHideMainLayers(void) {
    REG_DISPCNT = (REG_DISPCNT & ~REG_DISPCNT_DISPLAY_MASK) | (MAIN_LAYERS_SHOWN << REG_DISPCNT_DISPLAY_SHIFT);
}

/* Hides some of the sub screen's layers from the next VBlank. */
void hideSubLayers(s32 layers) {
    SUB_LAYERS_SHOWN &= ~layers;
    addVBlankCallback(&applyHideSubLayers);
}

/* Shows the sub screen's layers SUB_LAYERS_SHOWN says, at VBlank. */
void applyHideSubLayers(void) {
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~REG_DISPCNT_DISPLAY_MASK) | (SUB_LAYERS_SHOWN << REG_DISPCNT_DISPLAY_SHIFT);
}

/* Sets the main screen's BG layers' priorities, from the next VBlank. */
void setMainBgPriorities(s32 bg0, s32 bg1, s32 bg2, s32 bg3) {
    MAIN_BG_PRIORITIES[0] = bg0;
    MAIN_BG_PRIORITIES[1] = bg1;
    MAIN_BG_PRIORITIES[2] = bg2;
    MAIN_BG_PRIORITIES[3] = bg3;
    addVBlankCallback(&applyMainBgPriorities);
}

/* Gives the main screen's BG layers their priorities, at VBlank. */
void applyMainBgPriorities(void) {
    REG_BG0CNT = (REG_BG0CNT & ~REG_BGCNT_PRIORITY_MASK) | MAIN_BG_PRIORITIES[0];
    REG_BG1CNT = (REG_BG1CNT & ~REG_BGCNT_PRIORITY_MASK) | MAIN_BG_PRIORITIES[1];
    REG_BG2CNT = (REG_BG2CNT & ~REG_BGCNT_PRIORITY_MASK) | MAIN_BG_PRIORITIES[2];
    REG_BG3CNT = (REG_BG3CNT & ~REG_BGCNT_PRIORITY_MASK) | MAIN_BG_PRIORITIES[3];
}

/* Sets the sub screen's BG layers' priorities, from the next VBlank. */
void setSubBgPriorities(s32 bg0, s32 bg1, s32 bg2, s32 bg3) {
    SUB_BG_PRIORITIES[0] = bg0;
    SUB_BG_PRIORITIES[1] = bg1;
    SUB_BG_PRIORITIES[2] = bg2;
    SUB_BG_PRIORITIES[3] = bg3;
    addVBlankCallback(&applySubBgPriorities);
}

/* Gives the sub screen's BG layers their priorities, at VBlank. */
void applySubBgPriorities(void) {
    REG_DB_BG0CNT = (REG_DB_BG0CNT & ~REG_BGCNT_PRIORITY_MASK) | SUB_BG_PRIORITIES[0];
    REG_DB_BG1CNT = (REG_DB_BG1CNT & ~REG_BGCNT_PRIORITY_MASK) | SUB_BG_PRIORITIES[1];
    REG_DB_BG2CNT = (REG_DB_BG2CNT & ~REG_BGCNT_PRIORITY_MASK) | SUB_BG_PRIORITIES[2];
    REG_DB_BG3CNT = (REG_DB_BG3CNT & ~REG_BGCNT_PRIORITY_MASK) | SUB_BG_PRIORITIES[3];
}

/* Gets the main screen's BG layers' priorities; any pointer may be NULL. */
void getMainBgPriorities(s32 *bg0, s32 *bg1, s32 *bg2, s32 *bg3) {
    if (bg0 != NULL) {
        *bg0 = MAIN_BG_PRIORITIES[0];
    }
    if (bg1 != NULL) {
        *bg1 = MAIN_BG_PRIORITIES[1];
    }
    if (bg2 != NULL) {
        *bg2 = MAIN_BG_PRIORITIES[2];
    }
    if (bg3 != NULL) {
        *bg3 = MAIN_BG_PRIORITIES[3];
    }
}

/* Gets the sub screen's BG layers' priorities; any pointer may be NULL. */
void getSubBgPriorities(s32 *bg0, s32 *bg1, s32 *bg2, s32 *bg3) {
    if (bg0 != NULL) {
        *bg0 = SUB_BG_PRIORITIES[0];
    }
    if (bg1 != NULL) {
        *bg1 = SUB_BG_PRIORITIES[1];
    }
    if (bg2 != NULL) {
        *bg2 = SUB_BG_PRIORITIES[2];
    }
    if (bg3 != NULL) {
        *bg3 = SUB_BG_PRIORITIES[3];
    }
}

/* Empties the VRAM transfer queue. */
void clearVramTransfers(void) {
    VRAM_TRANSFER_END  = VRAM_TRANSFERS;
    VRAM_TRANSFER_DATA = &data_021d8c90;
}

/* Runs the queued VRAM transfers and empties the queue, at VBlank. */
void runVramTransfers(void) {
    struct VramTransfer *transfer;

    transfer = VRAM_TRANSFERS;
    if (VRAM_TRANSFER_END == VRAM_TRANSFERS) {
        return;
    }
    for (; transfer < VRAM_TRANSFER_END; transfer++) {
        if (transfer->unitBits == 32) {
            func_020e2324(transfer->src, transfer->dst, transfer->size);
        } else if (transfer->unitBits == 16) {
            func_020e22f4(transfer->src, transfer->dst, transfer->size);
        }
    }
    VRAM_TRANSFER_END  = VRAM_TRANSFERS;
    VRAM_TRANSFER_DATA = &data_021d8c90;
}

/* Takes size bytes for data to transfer from the top of the queue's buffer. */
s32 *allocVramTransferData(s32 size) {
    VRAM_TRANSFER_DATA -= size / 4 + 1;
    return VRAM_TRANSFER_DATA;
}

/* Loads characters into the main screen's BG layer bg at slot (-1 for the
 * first free one) and returns where they went. */
s16 loadMainBgChars(u8 bg, s16 slot, struct CharacterData *chars) {
    u32 count;

    switch (chars->format) {
        case GX_TEXFMT_PLTT16:
            count = chars->size >> 5;
            break;
        case GX_TEXFMT_PLTT256:
            count = chars->size >> 6;
            break;
    }
    return putMainBgChars(bg, slot, (s16) count, (s32) chars->data);
}

/* Loads characters into the sub screen's BG layer bg at slot (-1 for the
 * first free one) and returns where they went. */
s16 loadSubBgChars(u8 bg, s16 slot, struct CharacterData *chars) {
    u32 count;

    switch (chars->format) {
        case GX_TEXFMT_PLTT16:
            count = chars->size >> 5;
            break;
        case GX_TEXFMT_PLTT256:
            count = chars->size >> 6;
            break;
    }
    return putSubBgChars(bg, slot, (s16) count, (s32) chars->data);
}

/* Copies tiles onto the main screen's BG layer (params is a struct ScreenCopy)
 * and flushes what it wrote. */
struct BgData *copyMainBgScreenAndFlush(u8 *params) {
    struct BgData *data;

    data = copyMainBgScreen(params);
    if (data != NULL) {
        func_020e4f58(data->data, data->unk0 * data->unk2);
    }
    return data;
}

/* Copies tiles onto the sub screen's BG layer (params is a struct ScreenCopy)
 * and flushes what it wrote. */
struct BgData *copySubBgScreenAndFlush(u8 *params) {
    struct BgData *data;

    data = copySubBgScreen(params);
    if (data != NULL) {
        func_020e4f58(data->data, data->unk0 * data->unk2);
    }
    return data;
}

/* Loads the palette, character and screen files of entry index of
 * func_0204871c's table into gfx, a struct BgGraphics, and unpacks them. */
void func_02086df4(s32 index, s32 *gfx) {
    s32 *files;

    files  = func_0204871c(index);
    gfx[0] = loadTempPaletteFile(gfx + 3, files[0]);
    gfx[1] = loadTempCharFile(gfx + 4, files[1]);
    gfx[2] = loadTempScreenFile(gfx + 5, files[2]);
}
