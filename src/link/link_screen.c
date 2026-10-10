#include "link/link_screen.h"
#include "engine/bg/bg_load.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite.h"
#include "engine/sprite/sprite_create.h"
#include "engine/sprite/sprite_draw.h"
#include "engine/system/system.h"
#include "engine/text/font.h"
#include "engine/text/text_args.h"
#include "engine/ui/buttons.h"
#include "link/link_session.h"
#include "link/wifi.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Prints system text 0x3D with the session's unk178, when show is set. */
void func_0206f55c(struct LinkSession *session, s32 show) {
    if (show == 0) {
        return;
    }
    func_02042ee0(0, 0x10, 0x20, 2);
    func_02042d58(8, 0x10, func_0209cd08(0x3D), 0, (s32) session->work->unk178);
}

/* Clears both screens' backgrounds, sprites and blending. */
void clearLinkScreens(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    G2_BlendNone();
    G2S_BlendNone();
}

/* Loads the link screen's fonts. */
void loadLinkScreenFonts(void) {
    func_020a9ae0(2, 0, 0xF);
    func_020a9ae0(1, 1, 0xF);
    func_020a9ae0(4, 2, 0xF);
    func_020a9ae0(5, 3, 0xF);
    func_020a9ae0(3, 4, 0xF);
    func_020a9c40(2, 5, 0xE);
    func_020a9c40(0, 7, 0xF);
}

/* Frees the link screen's fonts. */
void freeLinkScreenFonts(void) {
    func_020a9844(2);
    func_020a9844(1);
    func_020a9844(4);
    func_020a9844(5);
    func_020a9844(3);
    func_020a98a8(2);
    func_020a98a8(1);
    func_020a98a8(0);
}

/* Shows the link level icon on the sub screen, at the top right corner. */
void showSubLinkIcon(s32 palette, s32 unk12) {
    if (SUB_LINK_ICON == -1) {
        SUB_LINK_ICON = createMainSprite(0x3F2, 0xF0, 0, palette, unk12);
        setMainSpriteBgPriority(SUB_LINK_ICON, 0);
        func_0203e878(SUB_LINK_ICON, 0);
    } else {
        freeMainSprite(SUB_LINK_ICON);
        SUB_LINK_ICON = createMainSprite(0x3F2, 0xF0, 0, palette, unk12);
        setMainSpriteBgPriority(SUB_LINK_ICON, 0);
        func_0203e878(SUB_LINK_ICON, 0);
    }
}

/* Shows the link level icon on the main screen, at the top right corner,
 * freeing the other one first. */
void showMainLinkIcon(s32 palette, s32 unk12) {
    s32 sprite;

    if (MAIN_LINK_ICON == -1) {
        sprite         = createSubSprite(0x3F2, 0xF0, 0, palette, unk12);
        MAIN_LINK_ICON = sprite;
        setSubSpriteBgPriority(sprite, 0);
        func_0203e848(MAIN_LINK_ICON, 0);
        return;
    }
    freeSubSprite(SUB_LINK_ICON);
    sprite         = createSubSprite(0x3F2, 0xF0, 0, palette, unk12);
    MAIN_LINK_ICON = sprite;
    setSubSpriteBgPriority(sprite, 0);
    func_0203e848(MAIN_LINK_ICON, 0);
}

/* Frees the sub screen's link level icon. */
s32 freeSubLinkIcon(void) {
    if (SUB_LINK_ICON == -1) {
        return SUB_LINK_ICON;
    }
    freeMainSprite();
    SUB_LINK_ICON = -1;
    return (s32) &SUB_LINK_ICON;
}

/* Frees the main screen's link level icon. */
s32 freeMainLinkIcon(void) {
    if (MAIN_LINK_ICON == -1) {
        return MAIN_LINK_ICON;
    }
    freeSubSprite();
    MAIN_LINK_ICON = -1;
    return (s32) &MAIN_LINK_ICON;
}

/* Shows the link level (0 to 3) of func_020b5288 on the icons. */
void updateLocalLinkIcons(void) {
    s32 level;

    switch (func_020b5288()) {
        default:
        case 0:
            level = 0;
            break;
        case 1:
            level = 1;
            break;
        case 2:
            level = 2;
            break;
        case 3:
            level = 3;
            break;
    }
    if (SUB_LINK_ICON != -1) {
        setMainSpriteAnim(SUB_LINK_ICON, level, -1);
    }
    if (MAIN_LINK_ICON != -1) {
        setSubSpriteAnim(MAIN_LINK_ICON, level, -1);
    }
}

/* Opens the link screen's list: its cursor, its sprite and its five
 * buttons. */
void openLinkList(struct LinkSession *session) {
    s32 i;

    if (session->buttons != -1) {
        return;
    }
    if (session->work->cursorSprite == -1) {
        session->work->cursorSprite = createMainSprite(0x40E, data_021357ac[0], data_021357ac[1], 2, 0);
    }
    if (session->work->unk164 == -1) {
        session->work->unk164 = createMainSprite(0x3F8, 0x20, 0xAC, 1, 0);
    }
    session->buttons = createButtonGroup(0, session->choice[0], onLinkListButton);
    for (i = 0; i < 5; i++) {
        addRectButton(data_021357ac[i * 4], data_021357ac[i * 4 + 1], data_021357ac[i * 4 + 2], data_021357ac[i * 4 + 3], 0,
                      session->buttons);
    }
    findTask(session->buttons);
    setMainSpritePos(session->work->cursorSprite, data_021357ac[session->choice[0] * 4],
                     data_021357ac[session->choice[0] * 4 + 1]);
}

/* Closes the link screen's list: its buttons, its cursor and its sprite. */
void closeLinkList(struct LinkSession *session) {
    s32 buttons = session->buttons;

    if (buttons != -1 && buttons != -1) {
        closeButtonGroup(buttons);
        session->buttons = -1;
    }
    if (session->work->cursorSprite != -1) {
        freeMainSprite(session->work->cursorSprite);
        session->work->cursorSprite = -1;
    }
    if (session->work->unk164 != -1) {
        freeMainSprite(session->work->unk164);
        session->work->unk164 = -1;
    }
}
