#include "battle/battle_mode/enemy_marks.h"
#include "battle/battle_mode/data.h"
#include "battle/characters/chr.h"
#include "battle/characters/data.h"
#include "battle/sprite_slots.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/text/text_object.h"
#include "engine/ui/gauge.h"

/* Colors the five marks of a skill's range: a zone it reaches orange, or blue
 * for a fixed range, and the others grey. */
void setSkillRangeColors(u32 id) {
    struct SkillData *skill;
    s32 i;
    struct BattleBg *copy;
    struct BattleBg *bg;
    u8 lit;

    skill = func_020a1268(id);
    copy  = &BATTLE->unk1750;
    bg    = &BATTLE->unk196C;
    lit   = skill->range.bytes[3] & 0x1F;
    for (i = 0; i < 5; i++) {
        if (lit & (0x10 >> i)) {
            if (skill->range.flags >> 31 == 0) {
                copy->colors[i][0] = bg->colors[i][0] = 0x31F;
                copy->colors[i][1] = bg->colors[i][1] = 0x115F;
            } else {
                copy->colors[i][0] = bg->colors[i][0] = 0x7F46;
                copy->colors[i][1] = bg->colors[i][1] = 0x7D00;
            }
        } else {
            copy->colors[i][0] = bg->colors[i][0] = 0x1CE7;
            copy->colors[i][1] = bg->colors[i][1] = 0x4E73;
        }
    }
}

/* The same for an item of func_020a1410's table, the 50 of item_dik_hlp.sdb,
 * whose range is laid out as a skill's but four bytes further. The table's
 * records are not typed yet. */
void setItemRangeColors(u32 id) {
    struct BattleBg *copy;
    struct BattleBg *bg;
    u8 *record;
    s32 i;
    u8 lit;

    copy   = &BATTLE->unk1750;
    bg     = &BATTLE->unk196C;
    record = (u8 *) func_020a1410(id);
    lit    = record[0x17] & 0x1F;
    for (i = 0; i < 5; i++) {
        if (lit & (0x10 >> i)) {
            if (*(u32 *) &record[0x14] >> 31 == 0) {
                copy->colors[i][0] = bg->colors[i][0] = 0x31F;
                copy->colors[i][1] = bg->colors[i][1] = 0x115F;
            } else {
                copy->colors[i][0] = bg->colors[i][0] = 0x7F46;
                copy->colors[i][1] = bg->colors[i][1] = 0x7D00;
            }
        } else {
            copy->colors[i][0] = bg->colors[i][0] = 0x1CE7;
            copy->colors[i][1] = bg->colors[i][1] = 0x4E73;
        }
    }
}

/* Clears four by two tiles of the main screen's background 1 and releases the
 * sprites 0x2B and 0x2C. */
void func_ov002_0223af00(void) {
    func_020867fc(1, 0x1B, 0x15, 4, 2, 0);
    releaseSlotSprite(0x2B);
    releaseSlotSprite(0x2C);
}

/* Clears a part of the sub screen's background 3, hides the sprites 0x9B to
 * 0xA7, closes the text windows after the first and frees background 3's
 * characters. */
void func_ov002_0223a840(void) {
    s32 i;

    func_02086758(3, 0xF, 2, 0x11, 0xC, 0);
    for (i = 0x9B; i <= 0xA7; i++) {
        hideSlotSprite(i);
    }
    for (i = 1; i <= 21; i++) {
        freeWindowImage(&BATTLE->windows[i]);
    }
    func_02085710(3, BATTLE->unk196C.unk218);
}

/* Releases the sprites 0x2B to 0x2E that are in use. */
void func_ov002_0223a6f0(void) {
    s32 sprite;

    for (sprite = 0x2E; sprite >= 0x2B; sprite--) {
        if (findSpriteSlot(sprite) != NULL) {
            releaseSlotSprite(sprite);
        }
    }
}

/* Clears the main screen's background 0 and frees its characters. */
void func_ov002_0223a454(void) {
    struct BattleBg *bg = &BATTLE->unk0AA8;

    func_020867fc(0, 0, 0, 0x20, 0x18, 0);
    func_0208577c(0, bg->unk218);
}

/* Moves the shown enemy numbers with their enemies; one shown from the next
 * frame is shown from now on. */
void func_ov002_02239d04(void) {
    s32 i;
    struct UnitNumber *number;

    number = BATTLE->unitNumbers;
    for (i = 6; i <= 11; i++) {
        if (number->state == 1) {
            func_ov002_02239a9c(number);
            func_020a4ad4(&number->number, number->number.x, number->number.y);
            setSlotSpritePosition(number->unit + 0x2B, number->number.x, number->number.y);
        } else if (number->state == 2) {
            number->state = 1;
        }
        number++;
    }
}

/* Hides the enemy numbers. */
void func_ov002_02239b28(void) {
    s32 i;
    struct UnitNumber *number;

    number = BATTLE->unitNumbers;
    for (i = 11; i >= 6; i--) {
        if (number->state != 0) {
            releaseSlotSprite(number->unit + 0x2B);
            func_020a4c9c(&number->number);
            number->state = 0;
        }
        number++;
    }
}

/* Places an enemy's number over it on the screen. */
void func_ov002_02239a9c(struct UnitNumber *number) {
    struct NumberSprite *sprite;
    struct BattleChr *chr;
    u32 kind;

    sprite = &number->number;
    chr    = getMainBattleChr(number->unit);
    kind   = number->unk2;
    if (kind == 4 || kind == 16 || kind == 28) {
        sprite->x = chr->x - (kind >> 1) * 8 - BATTLE_MAP_SCROLL.x[0].part.whole;
    } else {
        sprite->x = chr->x - BATTLE_MAP_SCROLL.x[0].part.whole;
    }
    sprite->y = chr->y + 0x60 - BATTLE_MAP_SCROLL.y[0].part.whole;
}
