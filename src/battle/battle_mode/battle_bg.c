#include "battle/battle_mode/battle_bg.h"
#include "battle/battle_mode/battle.h"
#include "battle/battle_mode/battle_map.h"
#include "battle/battle_mode/data.h"
#include "battle/battle_mode/panels.h"
#include "battle/battle_mode/turn_order.h"
#include "battle/battle_state.h"
#include "battle/characters/chr_system.h"
#include "battle/characters/fade_sprite_slot.h"
#include "battle/characters/move_script.h"
#include "battle/sprite_slots.h"
#include "battle/unit_panel_draw.h"
#include "battle/unit_panels.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/debug/debug_print.h"
#include "engine/gfx/gfx_files.h"
#include "engine/libs.h"
#include "engine/palette/palette_fade.h"
#include "engine/system/display.h"
#include "engine/text/font.h"
#include "menus/widgets/text_list.h"
#include "nitro/g2.h"
#include "nitro/g2d.h"
#include "nitro/gx.h"
#include "title/title_menu.h"

/* Sets the main screen's blending from mainBlend, at the vblank. */
void applyBattleMainBlend(void) {
    G2_SetBlendAlpha(BATTLE->mainBlend.plane1, BATTLE->mainBlend.plane2, BATTLE->mainBlend.ev1, BATTLE->mainBlend.ev2);
}

/* Sets the sub screen's blending from subBlend, at the vblank. */
void applyBattleSubBlend(void) {
    G2S_SetBlendAlpha(BATTLE->subBlend.plane1, BATTLE->subBlend.plane2, BATTLE->subBlend.ev1, BATTLE->subBlend.ev2);
}

/* Changes the sub screen's blend weights to subBlend's, at the vblank. */
void applyBattleSubBlendWeights(void) {
    G2S_ChangeBlendAlpha(BATTLE->subBlend.ev1, BATTLE->subBlend.ev2);
}

/* Turns the main screen's blending off, at the vblank. */
void applyBattleMainBlendOff(void) {
    G2_BlendNone();
}

/* Turns the sub screen's blending off, at the vblank. */
void applyBattleSubBlendOff(void) {
    G2S_BlendNone();
}

/* Updates the sprite slots. */
void func_ov002_0224b830(void) {
    updateSpriteSlots();
}

/* Sets up the sprite slots. */
void func_ov002_0224b824(void) {
    initSpriteSlots();
}

/* Updates the unit panels. */
void func_ov002_0224b818(void) {
    updateUnitPanels();
}

/* Sets up the unit panels. */
void func_ov002_0224b80c(void) {
    initUnitPanels();
}

/* Frees the unit panels' texts. */
void func_ov002_0224b800(void) {
    freeUnitPanelTexts();
}

/* Hands a unit's panel to func_0207debc. */
void func_ov002_0224b7f4(s8 unit) {
    func_0207debc(unit);
}

/* Shows a unit's panel at (x, y). */
void func_ov002_0224b7e8(s8 unit, s16 x, s16 y) {
    func_0207d990(unit, x, y);
}

/* Takes a unit's panel off the screen. */
void func_ov002_0224b7dc(s8 unit) {
    func_0207d920(unit);
}

/* Moves a unit's panel to (x, y). */
void func_ov002_0224b7d0(s8 unit, s16 x, s16 y) {
    func_0207d638(unit, x, y);
}

/* Sets the priority of a unit's panel's sprites. */
void func_ov002_0224b7c4(s8 unit, s32 priority) {
    func_0207d524(unit, priority);
}

/* Sets up a unit's panel for the Digimon id, with its maximum HP and MP. */
void func_ov002_0224b7b8(s8 unit, s32 id, s16 maxHp, s16 maxMp) {
    func_0207d404(unit, id, maxHp, maxMp);
}

/* Sets up the battle's screens: the map and its scroll, the battle characters,
 * BG effects, list sprites and move scripts, the backgrounds and the map's
 * scroll limits. */
void initBattleScreens(void) {
    func_ov002_0222c318();
    clearBattleChrState();
    initMainBattleChrs(0);
    initSubBattleChrs(0x280);
    loadBattleMap(func_02080eb4(), 0x87, 0x3C);
    initBgEffects();
    clearListSprites();
    initMoveScripts();
    initTextLists();
    stopDebugPrint();
    G2S_SetBG0Control(1, 0, 6, 6, 0);
    func_020a9c40(2, 1, 0xA);
    func_020a9c40(1, 2, 0x10);
    func_020a9c40(4, 3, 0x10);
    func_020a9c40(5, 4, 0x10);
    func_020a9ae0(2, 5, 0xC);
    func_020a9ae0(1, 6, 0xE);
    func_020a9ae0(4, 7, 0xE);
    func_020a9ae0(5, 8, 0xE);
    func_020a9ae0(1, 9, 0x10);
    func_020a9ae0(4, 0xA, 0x10);
    func_020a9ae0(5, 0xB, 0x10);
    /* The map's size in pixels less the screen's. */
    BATTLE->maxScrollX = BATTLE_MAP_SCROLL.width[0] * 8 - 256;
    BATTLE->maxScrollY = BATTLE_MAP_SCROLL.height[0] * 8 - 192;
    BATTLE->unk4562    = 3;
    BATTLE->unk4563    = 1;
}

/* Loads the battle's backgrounds. */
void loadBattleBgs(void) {
    struct BattleBg *bg;
    s32 size;

    func_020aa340(1, 1);
    loadBattleBgGraphics(1, &BATTLE->unk088C.gfx);
    loadBattleBgGraphics(0x63, &BATTLE->unk0AA8.gfx);
    loadBattleBgGraphics(0, &BATTLE->unk0CC4.gfx);
    loadBattleBgGraphics(0xA, &BATTLE->unk0EE0.gfx);
    loadBattleBgGraphics(0x38, &BATTLE->unk1750.gfx);
    bg         = &BATTLE->unk1750;
    bg->unk218 = loadMainBgChars(1, -1, bg->gfx.chars);
    loadBattleBgGraphics(0x37, &BATTLE->unk10FC.gfx);
    bg         = &BATTLE->unk10FC;
    bg->unk218 = loadMainBgChars(1, -1, bg->gfx.chars);
    size       = getPaletteSize((s32) bg->gfx.paletteFile, bg->gfx.palette);
    loadMainPalette(0xF0, (u16) (size >> 1), (s32) bg->gfx.palette->pRawData);
    setMainBgOffset(1, 0, 0);
    setMainBgPriorities(2, 0, 1, 3);
    func_ov002_02249a2c();
    func_ov002_022474e0();
    func_ov002_02245f60();
}
