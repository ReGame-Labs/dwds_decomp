#include "battle/battle_mode/battle_end.h"
#include "battle/battle_mode/data.h"
#include "battle/battle_mode/turn_order.h"
#include "battle/battle_state.h"
#include "battle/characters/chr.h"
#include "battle/characters/chr_draw.h"
#include "battle/characters/data.h"
#include "battle/sprite_slots.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/palette/palette_fade.h"
#include "engine/palette/palette_upload.h"
#include "engine/save/progress.h"
#include "field/map/map_character.h"

/* Closes the message window once its timer runs out. */
void func_ov002_02234114(void) {
    if (BATTLE->messageTimer == 0) {
        return;
    }
    BATTLE->messageTimer--;
    if (BATTLE->messageTimer != 0) {
        return;
    }
    func_ov002_02247bf4();
}

/* Moves the popups up while their timers run, then removes their sprites. The
 * positions are read as u16 and passed as s16 (ldrh, then a sign extension). */
void func_ov002_02234008(void) {
    s32 i;
    struct SpriteSlot *sprite;
    s32 j;
    u16 handle;
    struct Popup *popup;

    for (i = 0, popup = BATTLE->popups; i < POPUP_COUNT; i++, popup++) {
        if (popup->active == -1) {
            continue;
        }
        handle = popup->sprite;
        if (popup->timer != 0) {
            popup->timer--;
            if (popup->slow == 0) {
                popup->y.value -= 0x8000;
            } else {
                popup->y.value -= 0x4000;
            }
            for (j = 0; j < POPUP_SPRITE_COUNT; handle++, j++) {
                sprite = findSpriteSlot(handle);
                if (sprite == NULL) {
                    break;
                }
                setSlotSpritePosition(handle, (s16) (u16) sprite->x.part.whole, (s16) (u16) popup->y.part.whole);
            }
        } else {
            for (j = 0; j < POPUP_SPRITE_COUNT; handle++, j++) {
                if (findSpriteSlot(handle) == NULL) {
                    break;
                }
                releaseSlotSprite(handle);
            }
            popup->active = -1;
        }
    }
}

/* Flashes the palettes of the enemies' sprite and character toward a color
 * every few frames while their timers run. */
void func_ov002_02233bb8(void) {
    s32 i;
    struct Flash *flash;
    s16 palette;
    u16 *dst;

    for (i = 0, flash = BATTLE->flashes; i < FLASH_COUNT; i++, flash++) {
        if (flash->unit != -1) {
            flash->timer--;
            if (flash->unit > LAST_ALLY_UNIT) {
                palette = (u16) ((findSpriteSlot(flash->unit + 0x8A)->palette << 8) + 0xA00);
                dst     = getSubPaletteBase(palette);
                func_020e2454(dst, getSubPaletteColor(palette), 0x200);
                func_0208448c(flash->color, 0x100, (s16) ((flash->timer & 3) * 3), getSubPaletteColor(palette));
                palette =
                    (u16) ((((struct BattleChr *) getMainBattleChr(flash->unit - FIRST_ENEMY_UNIT))->palette << 8) + 0xA00);
                dst = getMainPaletteBase(palette);
                func_020e2454(dst, getMainPaletteColor(palette), 0x200);
                func_0208448c(flash->color, 0x100, (s16) ((flash->timer & 3) * 3), getMainPaletteColor(palette));
                markMainPalettesDirty();
                markSubPalettesDirty();
            }
            if (flash->timer == 0) {
                flash->unit = -1;
            }
        }
    }
}

/* Sets the characters in animResets back to sequence 0 once their sequence is
 * done. */
void func_ov002_02233b48(void) {
    s32 i;
    s8 *slot;

    slot = BATTLE->animResets;
    for (i = 0; i < 6; i++) {
        if (*slot != -1 && isMainBattleChrSeqDone(*slot) == 1) {
            playMainBattleChrSeq(*slot, 0, -1);
            *slot = -1;
        }
        slot++;
    }
}

/* Once a removal's palette effect has ended and its timer runs out, stops the
 * effect, removes the unit's character and hides its sprite. */
void func_ov002_022339e0(void) {
    s32 i;
    struct UnitWait *wait;

    wait = BATTLE->removals;
    for (i = 0; i < 6; i++) {
        if (wait->unit != -1 && isMainPaletteEffectRunning(wait->effect) == 0) {
            if (--wait->timer == 0) {
                stopMainPaletteEffects(wait->effect);
                removeMainBattleChr(wait->unit);
                hideSlotSprite(wait->unit + 0x90);
                wait->unit = -1;
            }
        }
        wait++;
    }
}

/* Once a reveal's palette effect has ended, stops the palette effects of
 * unk545E and shows the unit's sprite again. */
void func_ov002_02233964(void) {
    s32 i;
    struct UnitWait *wait;

    wait = BATTLE->reveals;
    for (i = 0; i < 6; i++) {
        if (wait->unit != -1 && isMainPaletteEffectRunning(wait->effect) == 0) {
            stopMainPaletteEffects(BATTLE->unk545E);
            showSlotSprite(wait->unit + 0x90);
            wait->unit = -1;
        }
        wait++;
    }
}

/* Whether the battle is over: the party fled, or one side has no unit left
 * standing. Unless dryRun, records the result and, in a link battle, what
 * addLinkWins and addLinkLosses return for each side. */
BOOL checkBattleEnd(BOOL dryRun) {
    s8 actor;
    u8 count;
    s32 i;
    struct BattleUnit *remaining;
    struct BattleUnit *enemy;
    struct BattleUnit *ally;

    actor = BATTLE->actor;
    if (actor <= LAST_ALLY_UNIT && BATTLE->unk3DFE == 0xFFFF && BATTLE->unk3E43 == 7) {
        if (!dryRun) {
            BATTLE->result = BATTLE_FLED;
        }
        return TRUE;
    }
    if (actor >= FIRST_ENEMY_UNIT && BATTLE->unk3DFE == 0xFFFF) {
        BATTLE->units[actor].unk00 = -1;
        for (i = FIRST_ENEMY_UNIT, remaining = &BATTLE->units[FIRST_ENEMY_UNIT]; i <= LAST_ENEMY_UNIT; i++, remaining++) {
            if (remaining->unk00 != -1) {
                break;
            }
        }
        if (i == BATTLE_UNIT_COUNT) {
            if (!dryRun) {
                BATTLE->result = BATTLE_WON;
            }
            return TRUE;
        }
    }
    count = 0;
    for (i = 0, ally = &BATTLE->units[0]; i <= LAST_ALLY_UNIT; i++, ally++) {
        if (ally->unk00 != -1 && ally->stats.hp > 0) {
            count++;
        }
    }
    if (count == 0) {
        if (!dryRun) {
            BATTLE->result = BATTLE_LOST;
            if (isLinkBattle()) {
                BATTLE->wins           = addLinkWins(0);
                BATTLE->losses         = addLinkLosses(1);
                BATTLE->linkBattleLost = 1;
            }
        }
        return TRUE;
    }
    count = 0;
    for (i = FIRST_ENEMY_UNIT, enemy = &BATTLE->units[FIRST_ENEMY_UNIT]; i <= LAST_ENEMY_UNIT; i++, enemy++) {
        if (enemy->unk00 != -1 && enemy->stats.hp > 0) {
            count++;
        }
    }
    if (count == 0) {
        if (!dryRun) {
            BATTLE->result = BATTLE_WON;
            if (isLinkBattle()) {
                BATTLE->wins           = addLinkWins(1);
                BATTLE->losses         = addLinkLosses(0);
                BATTLE->linkBattleLost = 0;
            }
        }
        return TRUE;
    }
    return FALSE;
}
