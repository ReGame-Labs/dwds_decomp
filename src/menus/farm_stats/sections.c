#include "menus/farm_stats/sections.h"
#include "engine/digimon/game_data.h"
#include "engine/libs.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "menus/farm_stats/stats_screen.h"
#include "menus/widgets/digimon_detail.h"
#include "menus/widgets/skill_displays.h"
#include "menus/widgets/status_window.h"

/* Shows the Digimon's drawDigimonDetail display in window 1. */
void func_020cb4b4(struct StatsScreen *screen) {
    struct Params02059d8c params;

    params.digimon  = screen->digimon;
    params.window   = screen->windows[1];
    params.x        = 1;
    params.y        = 1;
    params.unkC     = 0;
    params.unkE     = 1;
    params.unk10    = 2;
    params.unk12    = 0xE;
    params.unk14[0] = 0;
    params.unk14[1] = 0;
    params.unk14[2] = 0;
    params.unk14[3] = 0;
    params.unk14[4] = 0;
    params.unk1E    = 2;
    params.unk20    = 2;
    params.unk22    = screen->unk5C;
    params.unk24    = 2;
    params.unk26    = 9;
    drawDigimonDetail(0, &params);
}

/* Takes down func_020cb4b4's display. */
void func_020cb494(void) {
    freeDigimonDetailSprites(0);
    func_02059c50(0);
}

/* Shows the Digimon's status in window 2: rows 7, 8 and 9. */
void func_020cb3fc(struct StatsScreen *screen) {
    struct StatusParams params;

    func_020e23c0(&params, 0, sizeof(params));
    params.digimon = screen->digimon;
    params.window  = screen->windows[2];
    params.x       = 1;
    params.y       = 5;
    params.unk6    = 1;
    params.unk8    = 1;
    params.unk10   = 7;
    params.unk12   = 8;
    params.unk14   = 9;
    params.unk16   = 0xE;
    params.unk24   = 2;
    params.unk26   = screen->unk60;
    params.unk28   = 2;
    params.unk2A   = 0;
    params.unk22   = 1;
    params.unk2C   = 0;
    drawStatusWindow(0, &params);
}

/* Takes down func_020cb3fc's status. */
void func_020cb3dc(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
}

/* Shows the Digimon's status in window 4: rows 0, 1 and 2. */
void func_020cb350(struct StatsScreen *screen) {
    struct StatusParams params;

    func_020e23c0(&params, 0, sizeof(params));
    params.digimon = screen->digimon;
    params.window  = screen->windows[4];
    params.x       = 1;
    params.y       = 5;
    params.unk6    = 1;
    params.unk8    = 1;
    params.unk10   = 0;
    params.unk12   = 1;
    params.unk14   = 2;
    params.unk16   = 0xE;
    params.unk24   = 2;
    params.unk26   = screen->unk5E;
    params.unk28   = 2;
    params.unk2A   = 1;
    params.unk22   = 2;
    params.unk2C   = 1;
    drawStatusWindow(0, &params);
}

/* Takes down func_020cb350's status. */
void func_020cb330(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
}

/* Shows three displays of the Digimon: func_02054e00's in window 8, its first
 * skill in window 7 once it has the level its species wants for it (none
 * before), and its status in window 2. */
void func_020cb19c(struct StatsScreen *screen) {
    struct StatusParams status;
    struct Params02056940 skill;
    struct Params02054e00 params;
    struct SpeciesData *species;

    params.digimon  = screen->digimon;
    species         = loadSpeciesData(params.digimon->unk4);
    params.window   = screen->windows[8];
    params.x        = 1;
    params.y        = 0;
    params.unkC     = 7;
    params.unk10    = 8;
    params.unkE     = 9;
    params.unk12    = 0;
    params.unk14[0] = 1;
    params.unk14[1] = 2;
    params.unk14[2] = 3;
    params.unk14[3] = 4;
    params.unk14[4] = 5;
    params.unk14[5] = 6;
    params.unk20    = 2;
    params.unk22    = screen->unk60;
    params.unk24    = 2;
    params.unk26    = 0;
    func_02054e00(0, &params);
    if (params.digimon->level >= species->unk34) {
        skill.item = params.digimon->unk54[0];
    } else {
        skill.item = 0xFFFF;
    }
    skill.window = screen->windows[7];
    skill.x      = 0;
    skill.y      = 4;
    skill.unk6   = 1;
    skill.unk8   = 1;
    skill.unkC   = 3;
    skill.unkE   = 5;
    skill.unk10  = 4;
    skill.unk12  = 2;
    skill.unk14  = screen->unk5E;
    skill.unk16  = 2;
    skill.unk18  = 1;
    func_02056940(0, &skill);
    func_020e23c0(&status, 0, sizeof(status));
    status.digimon = screen->digimon;
    status.window  = screen->windows[2];
    status.x       = 1;
    status.y       = 5;
    status.unk6    = 1;
    status.unk8    = 1;
    status.unk10   = 0;
    status.unk12   = 1;
    status.unk14   = 2;
    status.unk16   = 0xE;
    status.unk24   = 2;
    status.unk26   = screen->unk5C;
    status.unk28   = 2;
    status.unk2A   = 1;
    status.unk22   = 2;
    status.unk2C   = 0;
    drawStatusWindow(0, &status);
}

/* Takes down func_020cb19c's three displays. */
void func_020cb15c(void) {
    freeStatusWindowSprites(0);
    func_020587fc(0);
    freeAbilityDisplaySprites(0);
    closeAbilityDisplay(0);
    func_02054cb8(0);
    closeAbilityListDisplay(0);
}

/* Shows func_02053200's display of the Digimon in window 6 and its first ability
 * in window 5. */
void func_020cb0a4(struct StatsScreen *screen) {
    struct Params020539ac ability;
    struct Params02053200 params;

    params.window  = screen->windows[6];
    params.x       = 0;
    params.y       = 0;
    params.digimon = screen->digimon;
    params.unkC    = 1;
    params.unkE    = 2;
    params.unk10   = screen->unk60;
    params.unk12   = 2;
    params.unk14   = 0;
    func_02053200(0, &params);
    ability.unkA   = params.digimon->unk22[0];
    ability.unkC   = params.digimon->unk2C[0];
    ability.window = screen->windows[5];
    ability.x      = 1;
    ability.y      = 4;
    ability.unk6   = 1;
    ability.unk8   = 1;
    ability.unk10  = 0;
    ability.unk12  = 1;
    ability.unk14  = 2;
    ability.unk16  = screen->unk62;
    ability.unk18  = 2;
    ability.unk1A  = 0;
    func_020539ac(0, &ability);
}

/* Takes down func_020cb0a4's two displays. */
void func_020cb074(void) {
    freeMoveListDisplaySprite(0);
    closeMoveListDisplay(0);
    freeMoveDisplaySprite(0);
    closeMoveDisplay(0);
}

/* Moves the section menu's button group (func_020ca1a8) to its state 20, kept
 * in its work[6]. */
void func_020cad9c(struct StatsScreen *screen) {
    struct ButtonGroup *group;

    group          = findTask(screen->buttons);
    group->work[6] = 20;
}

/* Closes the section menu of func_020cadbc: frees its five sprites and ends its
 * button group. */
void func_020cad4c(struct StatsScreen *screen) {
    freeMainSprite(1);
    freeMainSprite(2);
    freeMainSprite(3);
    freeMainSprite(4);
    freeMainSprite(5);
    if (screen->buttons != -1) {
        closeButtonGroup(screen->buttons);
        screen->buttons = -1;
    }
}

/* Whether the screen's button group is closed. */
u8 func_020cad30(struct StatsScreen *screen) {
    u8 closed;

    if (screen->buttons == -1) {
        closed = 1;
    } else {
        closed = 0;
    }
    return closed;
}
