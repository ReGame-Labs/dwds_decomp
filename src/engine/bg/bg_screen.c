#include "engine/bg/bg_screen.h"
#include "engine/bg/bg_screen_task.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/sprite/sprite_create.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Tears down tickBgScreen's screen: its backgrounds, their graphics and the
 * sprites of both screens. */
void closeBgScreen(struct BgScreenTask *task) {
    stopSubPaletteEffectsButFades(task->unk28);
    stopMainPaletteEffectsButFades(task->unk2C);
    freeBgGraphics(&task->graphics[0]);
    freeBgGraphics(&task->graphics[1]);
    freeMainSprites();
    freeSubSprites();
    clearScreens();
}

/* Whether startBgScreenTask's task has ended. */
u8 isBgScreenDone(void) {
    return BG_SCREEN_TASK == NULL;
}

/* Clears both screens' backgrounds and sprites and switches their blending
 * off. */
void clearScreens(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    G2_BlendNone();
    MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    G2S_BlendNone();
}

/* The offset of the sprites of an id; the table's last entry, all zero, for
 * the others. A void pointer for ov006's caller, which reads it as u16s. */
void *getSpriteOffset(u16 id) {
    u32 i;
    struct SpriteOffset *entry = SPRITE_OFFSETS;

    for (i = 0; i < 12; i++) {
        if (id == entry->id) {
            break;
        }
        entry++;
    }
    return entry;
}

/* The number of friends in the Wi-Fi roster: DWC_IsValidFriendData
 * (func_020ff144) for each. */
s16 countWifiFriends(void) {
    s32 i;
    s16 count             = 0;
    struct WifiData *wifi = (struct WifiData *) data_021db618;

    for (i = 0; i < 16; i++) {
        if (func_020ff144(wifi->friends[i]) != 0) {
            count++;
        }
    }
    return count;
}
