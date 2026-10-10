#include "engine/text/text_banks.h"
#include "engine/bg/bg_layers.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/system/system.h"
#include "engine/text/expand_text.h"
#include "engine/text/text_args.h"
#include "farm/farm_groups.h"

#define TEXT_BANK_FARM_GOODS_HELP 0x10 /* fghelp.sdb */
#define TEXT_BANK_FARM_GOODS_INFO 0x11 /* fginfo.sdb */
#define TEXT_BANK_FP_INFO 0x12 /* fpinfo.sdb */
#define TEXT_BANK_SKILL_HELP 0x13 /* skill_help.sdb */
#define TEXT_BANK_ABILITY_HELP 0x14 /* abi_help.sdb */
#define TEXT_BANK_ITEM_DIK_HELP 0x15 /* item_dik_hlp.sdb */
#define TEXT_BANK_ITEM_WEAPON_HELP 0x16 /* item_wep_hlp.sdb */
#define TEXT_BANK_ITEM_ARMOR_HELP 0x17 /* item_arm_hlp.sdb */
#define TEXT_BANK_ITEM_ACC_HELP 0x18 /* item_acc_hlp.sdb */
#define TEXT_BANK_ITEM_DIJ_HELP 0x19 /* item_dij_hlp.sdb */
#define TEXT_BANK_SNK_HELP 0x22 /* snk_hlp.sdb */

#define ITEMS_WEAPONS 50  /* the first weapon */
#define ITEMS_ARMOR 187
#define ITEMS_ACCESSORIES 355
#define ITEMS_DIJ 429
#define ITEMS_END 499

/* Ends a sprite text, giving its tiles back with func_0208558c. */
void func_0209d954(s32 id) {
    struct SpriteText *text;
    void *sprites;

    text = findTask(id);
    func_0208558c(4, text->tiles);
    sprites = text->sprites;
    heapFree(sprites);
    endTaskById(id);
}

/* The same as func_0209d954, with func_02085520. */
void func_0209d900(s32 id) {
    struct SpriteText *text;
    void *sprites;

    text = findTask(id);
    func_02085520(4, text->tiles);
    sprites = text->sprites;
    heapFree(sprites);
    endTaskById(id);
}

/* Returns a sprite text's unk3C. */
s16 func_0209d8e8(s32 id) {
    struct SpriteText *text = findTask(id);

    return text->unk3C;
}

/* Returns whether a task runs. */
BOOL func_0209d8c8(s32 id) {
    if (findTask(id) != NULL) {
        return TRUE;
    }
    return FALSE;
}

/* Frees the loaded text bank (loadTextBank). */
void freeTextBank(void) {
    void *buffer;

    buffer = data_021da41c;
    if (buffer == 0) {
        return;
    }
    heapFree(buffer);
    data_021da41c = 0;
    data_021da418 = 0xFFFF;
}

/* Returns the help text of an item, from the bank of its kind, or NULL. */
void *getItemHelp(s32 item) {
    if (item >= 0 && item < ITEMS_WEAPONS) {
        loadTextBank(TEXT_BANK_ITEM_DIK_HELP);
        return func_0209d6f8(item);
    }
    if (item >= ITEMS_WEAPONS && item < ITEMS_ARMOR) {
        loadTextBank(TEXT_BANK_ITEM_WEAPON_HELP);
        return func_0209d6f8(item - ITEMS_WEAPONS);
    }
    if (item >= ITEMS_ARMOR && item < ITEMS_ACCESSORIES) {
        loadTextBank(TEXT_BANK_ITEM_ARMOR_HELP);
        return func_0209d6f8(item - ITEMS_ARMOR);
    }
    if (item >= ITEMS_ACCESSORIES && item < ITEMS_DIJ) {
        loadTextBank(TEXT_BANK_ITEM_ACC_HELP);
        return func_0209d6f8(item - ITEMS_ACCESSORIES);
    }
    if (item >= ITEMS_DIJ && item < ITEMS_END) {
        loadTextBank(TEXT_BANK_ITEM_DIJ_HELP);
        return func_0209d6f8(item - ITEMS_DIJ);
    }
    return NULL;
}

/* Returns the name of a group (getGroupById). */
void *getGroupName(s32 id) {
    struct Farm *group = getGroupById(id);

    return group->name;
}

/* Returns one of the 24 texts of snk_hlp.sdb, filled with up to three text
 * arguments, or NULL. */
void *func_0209d47c(s32 index, void *text0, void *text1, void *text2) {
    if (index < 0 || index >= 24) {
        return NULL;
    }
    if (text0 != NULL) {
        setTextArg(0, text0);
    }
    if (text1 != NULL) {
        setTextArg(1, text1);
    }
    if (text2 != NULL) {
        setTextArg(2, text2);
    }
    loadTextBank(TEXT_BANK_SNK_HELP);
    return func_0209e344(func_0209d6f8(index));
}

/* Returns the short name of a species (data_0211a688: "Armadillomn"). */
void *getSpeciesShortName(s16 index) {
    return (u8 *) data_0211a688 + data_0211a688[index];
}

/* Returns the full name of a species (data_0211f4e0: "Armadillomon"). */
void *getSpeciesName(s32 index) {
    return (u8 *) data_0211f4e0 + data_0211f4e0[index];
}

/* Returns the name of a character (data_02117c40: "PC-MALE", "Yuji"). */
void *getCharacterName(s16 index) {
    return (u8 *) data_02117c40 + data_02117c40[index];
}

/* Returns the name of a Digimon kept. */
void *getDigimonName(s32 id) {
    struct Digimon *digimon = getDigimon(id);

    return digimon->name;
}

/* Returns the name of a skill (data_0211cbd0). */
void *getSkillName(s32 index) {
    return func_0209d470(data_0211cbd0, index);
}

/* Returns the help text of a skill. */
void *getSkillHelp(s32 index) {
    loadTextBank(TEXT_BANK_SKILL_HELP);
    return func_0209d6f8(index);
}

/* Returns the name of an ability (data_02110974). */
void *getAbilityName(s32 index) {
    return func_0209d470(data_02110974, index);
}

/* Returns the help text of an ability. */
void *getAbilityHelp(s32 index) {
    loadTextBank(TEXT_BANK_ABILITY_HELP);
    return func_0209d6f8(index);
}

/* Returns the name of farm goods, three levels to a name (data_02118a78). */
u8 *func_0209d378(s32 value) {
    return (u8 *) data_02118a78 + data_02118a78[value / 3];
}

/* Returns the description of farm goods, three levels to one. */
void *func_0209d350(s32 value) {
    loadTextBank(TEXT_BANK_FARM_GOODS_INFO);
    return func_0209d6f8(value / 3);
}

/* Returns the help text of farm goods at one level. */
void *func_0209d334(s32 index) {
    loadTextBank(TEXT_BANK_FARM_GOODS_HELP);
    return func_0209d6f8(index);
}

/* Returns one of the names of data_0211809c ("Water Gun", "Volcano"). */
void *func_0209d320(s32 index) {
    return (u8 *) data_0211809c + data_0211809c[index];
}

/* Returns the text of fpinfo.sdb that goes with them. */
void *func_0209d304(s32 index) {
    loadTextBank(TEXT_BANK_FP_INFO);
    return func_0209d6f8(index);
}

/* Writes a number as text (func_0209d168). */
u16 *formatNumber(s32 value, s32 digits, u16 *buffer, s32 flags) {
    return func_0209d168(value, 0, digits, buffer, flags);
}
