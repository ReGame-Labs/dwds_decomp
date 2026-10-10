#ifndef FARM_DATA_H
#define FARM_DATA_H

/* The farm overlay's (ov005) types and data: the farms' kinds, layouts and
 * levels, the goods and their effects (fghelp.sdb, fginfo.sdb), the farm
 * events, the day's food, and the farm screen's panels, windows and tasks. */

#include "engine/data.h"
#include "types.h"

#define FARM_COUNT 4        /* the farms the save holds */
#define FARM_SLOT_COUNT 8   /* the digimon, and the goods, a farm holds at most */
#define FARM_GOODS_COUNT 50 /* the goods the save holds */
#define FARM_LEVEL_COUNT 5  /* the values each level of a farm can take */

/* A farm's five levels (struct Farm), as raiseFarmLevel raises them:
 * the farm upgrade shop's "Increase Size" raises CAPACITY, GOODS and LAYOUT
 * together. */
enum FarmLevel {
    FARM_LEVEL_CAPACITY,
    FARM_LEVEL_GOODS,
    FARM_LEVEL_EXP,
    FARM_LEVEL_FOOD,
    FARM_LEVEL_LAYOUT
};

/* What a farm effect does (struct FarmEffect's kind), from fghelp.sdb's text
 * for the goods and the events of FARM_GOODS_DATA that have each kind.
 * The types go in FARM_TEXTS' order: dragon, beast, aquan, bird, insect/plant,
 * machine/mutant, dark, holy. */
enum FarmEffectKind {
    FARM_EFFECT_HP = 1,
    FARM_EFFECT_MP,
    FARM_EFFECT_EXP_DRAGON, /* the farm's EXP for a type, a day */
    FARM_EFFECT_EXP_BEAST,
    FARM_EFFECT_EXP_AQUAN,
    FARM_EFFECT_EXP_BIRD,
    FARM_EFFECT_EXP_INSECT,
    FARM_EFFECT_EXP_MACHINE,
    FARM_EFFECT_EXP_DARK,
    FARM_EFFECT_EXP_HOLY,
    FARM_EFFECT_EXP_ALL,
    FARM_EFFECT_ATTACK,
    FARM_EFFECT_DEFENSE,
    FARM_EFFECT_SPIRIT,
    FARM_EFFECT_SPEED = 16,
    FARM_EFFECT_STRESS,
    FARM_EFFECT_FRIENDSHIP,
    FARM_EFFECT_FOOD,          /* the food the farm gathers a day */
    FARM_EFFECT_GROWTH_DRAGON, /* the growth rate of a type */
    FARM_EFFECT_GROWTH_BEAST,
    FARM_EFFECT_GROWTH_AQUAN,
    FARM_EFFECT_GROWTH_BIRD,
    FARM_EFFECT_GROWTH_INSECT,
    FARM_EFFECT_GROWTH_MACHINE,
    FARM_EFFECT_GROWTH_DARK,
    FARM_EFFECT_GROWTH_HOLY,
    FARM_EFFECT_GROWTH_ALL,
    FARM_EFFECT_BITS = 36
};

/* The panels of the farm screens, each one open while its flag of
 * getUiFlag is set. */
#define FARM_PANEL_DIGIMON 0     /* struct DigimonPanel */
#define FARM_PANEL_PAGES 4       /* struct FarmPages */
#define FARM_PANEL_PICK_FARM 5   /* struct FarmChoice */
#define FARM_PANEL_STATS 7       /* struct StatsCompare */
#define FARM_PANEL_TABS 8        /* struct FarmTabs */
#define FARM_PANEL_DIGIMON_B 0xA /* the second struct DigimonPanel */

/* The list of the items given to the digimon of a farm, 6 rows at a time,
 * with a scroll bar and a color cycling on the cursor's row. */
struct ItemList {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x24 */ s32 owner;
    /* 0x28 */ s16 scroll; /* the entry on the first row */
    /* 0x2A */ s16 cursor; /* the row of the cursor */
    /* 0x2C */ s8 palette;
    /* 0x2D */ s8 unk2D;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ s8 gfxSlot;
    /* 0x31 */ u8 window;
    /* 0x32 */ s16 thumbY; /* where the scroll bar's thumb is */
    /* 0x34 */ s16 count;
    /* 0x38 */ s32 inputTask;
    /* 0x3C */ s8 cursorEffect;
    /* 0x3D */ s8 entries[8]; /* indexes for getDigimonItem */
    /* 0x45 */ s8 rowButtons[6];
};

/* The window that describes the item under the item list's cursor. */
struct ItemInfo {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x24 */ s32 item;
    /* 0x28 */ s8 palette;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s8 gfxSlot;
    /* 0x2D */ u8 window;
};

/* A digimon's stats as they were before the results and as they are now, side
 * by side, with an arrow on each stat that went up. */
struct StatsCompare {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x24 */ s32 digimon;
    /* 0x28 */ s32 shown; /* the digimon drawn last */
    /* 0x2C */ s8 palette;
    /* 0x2D */ s8 unk2D;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ u8 beforeWindow;
    /* 0x31 */ u8 afterWindow;
    /* 0x32 */ s8 gfxSlot;
};

/* The results of a farm day: the food before, what the farms gathered and what
 * their digimon ate (FARM_TEXTS 0xCD, "Current Food", "Kg Produced Today",
 * "Kg Consumed Today"). Then the digimon of the farms as they were before. */
struct Results {
    /* 0x00 */ s32 consumed;
    /* 0x04 */ s32 food;
    /* 0x08 */ s32 produced;
    /* 0x0C */ s32 count;
    /* 0x10 */ struct Digimon digimon[32];
};

/* The screen of the results, a page for each farm. */
struct ResultsScreen {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 farm;
    /* 0x26 */ s16 farmCount;
    /* 0x28 */ s8 unk28;
    /* 0x29 */ s8 gfxSlots[2];
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 windows[2];
    /* 0x34 */ s32 unk34;
    /* 0x38 */ struct Results *results;
};

/* The window of the food of the results. */
struct FoodWindow {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s8 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s8 gfxSlot;
    /* 0x29 */ u8 window;
    /* 0x2C */ struct Results *results;
};

/* The windows of a farm's "Food Information" (FARM_TEXTS 0xCC): the food it
 * gathers a day and what its digimon eat, by stage. */
struct FarmFoodInfo {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x24 */ s32 owner;
    /* 0x28 */ s8 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s8 gfxSlot;
    /* 0x2D */ u8 window;
    /* 0x2E */ u8 consumedWindow;
};

/* The list of the goods of a farm (see struct FarmGoods). */
struct FarmGoodsList {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ u8 unk20[8];
    /* 0x28 */ s32 owner;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ s16 scroll; /* the entry on the first row */
    /* 0x30 */ s16 cursor; /* the row of the cursor */
    /* 0x32 */ s8 palette;
    /* 0x33 */ s8 unk33;
    /* 0x34 */ s32 inputTask;
    /* 0x38 */ s8 unk38;
    /* 0x3A */ s16 count;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 window;
    /* 0x40 */ s16 gfxSlot;
    /* 0x42 */ u8 unk42[0x22];
    /* 0x64 */ u16 unk64[0x12];
    /* 0x88 */ u8 unk88[0xC];
    /* 0x94 */ s8 cursorEffect;
    /* 0x95 */ s8 entries[8]; /* indexes of the goods of getFarmGoodsIdAt */
    /* 0x9E */ s16 unk9E;
    /* 0xA0 */ s16 unkA0;
};

/* Panel 4: the pages of a farm. Opening a page sets the state to the page's
 * entry of FARM_PAGE_STATES. */
struct FarmPages {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 page;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s32 owner;
    /* 0x2C */ u8 windows[3];
    /* 0x2F */ s8 palette;
    /* 0x30 */ s8 gfxSlot;
    /* 0x34 */ struct WindowImage image;
    /* 0x5C */ s16 imageX;
    /* 0x5E */ s16 imageY;
    /* 0x60 */ s16 unk60;
    /* 0x62 */ u16 unk62[8];
    /* 0x72 */ u16 unk72[8];
};

/* A window of a digimon's status: panel 0 shows one, with its actor, and panel
 * 0xA another. */
struct DigimonPanel {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x24 */ struct Digimon *shown;
    /* 0x28 */ struct Digimon *digimon;
    /* 0x2C */ s8 gfxSlot;
    /* 0x2D */ s8 palette;
    /* 0x2E */ u8 window;
    /* 0x30 */ s16 mode;
    /* 0x34 */ s32 actorTask; /* a struct ActorView, for panel 0 */
    /* 0x38 */ s8 unk38;      /* whether freeDigimonDetailSprites's display is up */
    /* 0x39 */ s8 statusUp;   /* whether drawStatusWindow's display is up */
};

/* The actor of the digimon of panel 0, made again whenever the digimon changes
 * after a few frames without input. */
struct ActorView {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 mode;
    /* 0x26 */ s16 delay;
    /* 0x28 */ struct Digimon *shown;
    /* 0x2C */ struct Digimon *digimon;
    /* 0x30 */ u16 actorKind;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ u16 actor; /* 0xFFFF when there is none */
    /* 0x36 */ s16 x;
    /* 0x38 */ s16 y;
};

/* Panel 8: picks a farm with L and R and one of five tabs, each one a page of
 * panel 4. */
struct FarmTabs {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ u8 unk20[0x30];
    /* 0x50 */ s16 farm; /* index for getFarmIdAt */
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s32 farmId;
    /* 0x58 */ s16 page;
    /* 0x5A */ s8 gfxSlot;
    /* 0x5C */ s32 buttons; /* the touch buttons task of createButtonGroup */
    /* 0x60 */ u16 sprite;
    /* 0x62 */ s16 result; /* -1 while open, 0 once B is pressed */
    /* 0x64 */ s16 cursorEffect;
    /* 0x66 */ s16 tab;
};

/* Panel 5: picks a farm for a digimon; state 900 is done, with the farm in
 * farm. */
struct FarmChoice {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s8 gfxSlots[2];
    /* 0x26 */ u8 unk26[2];
    /* 0x28 */ s32 digimon;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 farm;
    /* 0x38 */ s16 cursor;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s8 unk3C;
    /* 0x3D */ u8 window;
    /* 0x3E */ u16 actor; /* made by func_020c7ed8 unless flags bit 0 */
    /* 0x40 */ u8 unk40;
    /* 0x42 */ u16 flags;
    /* 0x44 */ s16 unk44;
};

/* The task of func_ov005_0228478c, made by func_ov005_02284fd4: a window with
 * a digimon's name and icon. */
struct DigimonNameWindow {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s32 farm;
    /* 0x28 */ s32 digimon;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u16 actor; /* the digimon's, of getSubActor */
    /* 0x30 */ u8 window;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u16 icon;
    /* 0x38 */ s32 nameText; /* the text task of func_0209dbc8 */
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s8 gfxSlot;
    /* 0x4A */ u16 unk4A;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ u8 unk4E;
};

/* An entry of FARM_KINDS, a kind of farm (the shops call them NML,
 * DRG, AQU, BRD, BST, INS, MAC, HOL and DAR Farm): what each level of a farm
 * of the kind gives (struct Farm), -1 past its last level. */
struct FarmKind {
    /* 0x00 */ u16 unk0[8];
    /* 0x10 */ s8 capacity[5];      /* how many digimon it holds, by capacityLevel */
    /* 0x15 */ s8 goodsCapacity[5]; /* how many goods, by goodsLevel */
    /* 0x1A */ u16 expType; /* 1 to 9: the type its EXP goes to (func_ov005_02288750) */
    /* 0x1C */ s16 exp[5];  /* the species EXP it gives a day, by expLevel */
    /* 0x26 */ s16 food[5]; /* the food it gathers a day, by foodLevel */
    /* 0x30 */ s8 layouts[5]; /* its entry of FARM_LAYOUTS, by layoutLevel */
    /* 0x35 */ u8 unk35[5];
};

/* An entry of FARM_LAYOUTS: a farm's map, with where its digimon and
 * its goods stand, x and y, as many places as the level holds. */
struct FarmLayout {
    /* 0x00 */ u16 index; /* its own */
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s16 digimonPos[8][2];
    /* 0x24 */ s16 goodsPos[8][2];
    /* 0x44 */ s16 unk44[2];
};

/* What farm goods or an event do: kind (enum FarmEffectKind) picks what,
 * which grows by value, up to max ("Max growth" in fghelp.sdb), with chance
 * percent. For FARM_EFFECT_FOOD, rollFarmFoodProduced adds value when a random
 * number below 100 is below chance. */
struct FarmEffect {
    /* 0x0 */ s8 kind;
    /* 0x2 */ s16 value;
    /* 0x4 */ s8 chance;
    /* 0x6 */ s16 max;
};

/* An entry of FARM_GOODS_DATA, a stage of a kind of farm goods (struct
 * FarmGoods, getFarmGoodsData): each kind has three, in a row, and
 * fghelp.sdb has a text for each entry. Entries 0xF9 on are the farm's events
 * (ids -0xFF to -0xF5). */
struct FarmGoodsData {
    /* 0x00 */ s8 growTime; /* growFarmGoods calls to the next stage, 0 for the last */
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u16 icon; /* a sprite kind of createLoopingSubSprite */
    /* getFarmGoodsEffect takes an index, but only one fits before price. */
    /* 0x04 */ struct FarmEffect effects[1];
    /* 0x0C */ s16 price;
    /* 0x0E */ s16 sellPrice;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 actors[2]; /* the kinds of its actors on the farm's screen, 0xFFFF for none */
    /* 0x16 */ u16 unk16;
};

/* One of the events of FARM_EVENTS that a digimon of a farm can go
 * through (struct FarmEventTask), 0xC bytes. */
struct FarmEventData {
    /* 0x0 */ s8 unk0; /* added to the digimon's unk72, which must stay within 100 */
    /* 0x1 */ u8 unk1;
    /* What the event does to the digimon. applyEventEffect indexes this
     * with a field its task never sets; only the first fits. */
    /* 0x2 */ struct FarmEffect effects[1];
    /* 0xA */ s16 unkA;
};

/* The task startFarmEventTask starts and tickFarmEventTask runs: a digimon
 * of the farm going through an event of FARM_EVENTS. */
struct FarmEventTask {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ u8 unk20[0x30];
    /* 0x50 */ u16 unk50; /* never set here */
    /* 0x52 */ u8 unk52[0x14];
    /* 0x66 */ u16 event;
    /* 0x68 */ u16 slot; /* in data_ov005_022a1d9c */
    /* 0x6A */ u8 unk6A[8];
    /* 0x72 */ s16 unk72;
    /* 0x74 */ s32 digimon; /* its id */
    /* 0x78 */ u8 unk78[0x14];
    /* 0x8C */ s32 unk8C; /* a task's id, passed on from the task that started this */
};

/* The task tickFarmTask starts to close its screen, run by
 * func_ov005_02291a34. */
struct Task02291a34 {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
};

/* The task tickFarmTask starts to ask a yes or no question, run by
 * askExitFarm. */
struct Task02292b48 {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ u8 unk20[0x30];
    /* 0x50 */ s16 answer; /* func_020ac6b8's: -1 until there is one, 0 for yes */
};

/* The screen of a farm (tickFarmScreen, FARM_SCREEN_TASK_ID): the actors
 * of its digimon and its goods, the view going from one actor to another,
 * while the timer of the farms runs and their events happen. */
struct FarmScreen {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s32 slot;  /* findFarmSlot's slot of the farm */
    /* 0x28 */ s32 farm; /* 0 for none */
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ s8 unk32;
    /* 0x33 */ s8 gfxSlot;
    /* 0x34 */ s8 unk34;
    /* 0x35 */ u8 window;
    /* 0x36 */ s8 unk36; /* the low byte of the event task's id (func_ov005_022871bc) */
    /* 0x37 */ u8 unk37[0x1D];
    /* 0x54 */ s16 actorIndex; /* the next of actors to look at */
    /* 0x56 */ s16 actorCount;
    /* 0x58 */ u16 actors[16]; /* shuffled by func_ov005_022862d4 */
    /* 0x78 */ u16 actor;      /* the one looked at */
    /* 0x7A */ u8 unk7A[0x22];
    /* 0x9C */ s32 timerTask; /* a struct FarmDayTimer, 0 for none */
};

/* The timer of the farms, which the save counts in frames up to
 * FARM_DAY_LENGTH: shown in the farm screen's window as a gauge, colors 8
 * to 15 of its palette row, one more of them full for each eighth. */
struct FarmDayTimer {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ u8 window;
    /* 0x24 */ u16 empty[16]; /* the colors of the next palette row */
    /* 0x44 */ u16 full[16];  /* the colors of the window's palette row */
    /* 0x64 */ u16 shown[16];
    /* 0x84 */ u16 paletteRow;
};

/* The task func_ov005_0228e23c runs (tickFarmTask and func_ov005_02292f48
 * start it, data_021e5cb4): a list of items, 6 rows at a time, sorted one of
 * three ways by func_ov005_0228bb40. */
struct Task0228e23c {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s16 state;
    /* 0x1E */ s16 wait;
    /* 0x20 */ s16 slot;
    /* 0x22 */ u8 unk22[0x2E];
    /* 0x50 */ u16 unk50;
    /* 0x52 */ s16 sort;   /* 0 to 2 */
    /* 0x54 */ s16 scroll; /* the entry on the first row */
    /* 0x56 */ s16 cursor; /* the row of the cursor */
    /* 0x58 */ s16 count;
};

/* The panel of farm goods (func_ov005_0228d164, data_021e5cb8): its
 * actors and numbers in one window, its name and one of two texts in another,
 * its icon and its farm in the third. */
struct GoodsPanel {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s32 goodsId;   /* an id of findFarmGoods, 0 for none */
    /* 0x28 */ u16 actors[2]; /* 0xFFFF for none */
    /* 0x2C */ u8 actorWindow;
    /* 0x2D */ u8 infoWindow;
    /* 0x2E */ u8 nameWindow;
    /* 0x2F */ u8 view; /* which text infoWindow shows */
    /* 0x30 */ s8 gfxSlot;
    /* 0x31 */ s8 palette;
    /* 0x34 */ s32 next; /* the goods to show next, -1 for none */
};

/* Places farm goods on one of the spots of the farm's layout
 * (func_ov005_0228da2c, data_021e5cc4). */
struct GoodsPlacement {
    /* 0x00 */ struct Task task;
    /* 0x1C */ s32 state;
    /* 0x20 */ s16 wait;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ u16 slot;
    /* 0x28 */ s32 goodsId;
    /* 0x2C */ u16 actors[2]; /* 0xFFFF for none */
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u16 marks[8]; /* sprites on the free spots, 0xFFFF for none */
    /* 0x42 */ u16 unk42;
    /* 0x44 */ s16 layout; /* an index for getFarmLayout */
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8 unk4C[4];
    /* 0x50 */ s16 spot;        /* the one under the stylus, -1 for none */
    /* 0x52 */ s8 buttons[17];  /* in the touch buttons of data_021e5cac */
    /* 0x64 */ s16 result;      /* -1 until a spot is picked, 9999 if cancelled */
};

extern struct FarmKind FARM_KINDS[10];
extern struct FarmEventData FARM_EVENTS[];
extern struct FarmLayout FARM_LAYOUTS[35];
extern struct FarmGoodsData FARM_GOODS_DATA[];
extern s32 RESULTS_TASK_ID;
extern s32 data_ov005_022a1d0c;
extern s32 TEMP_FARM;
extern s32 data_ov005_022a1d18;
extern s32 data_ov005_022a1d1c;
extern s32 FARM_SCREEN_TASK_ID;
extern s32 data_ov005_022a1d30;
extern s32 FARM_DAY_LENGTH;
extern s32 data_ov005_022a1d14;
extern s16 FARM_PAGE_STATES[];
extern struct FarmGoods *TEMP_FARM_GOODS;
extern s32 data_ov005_022a1d9c[];
extern u16 FARM_DIGIMON_ACTORS[];
extern u16 data_ov005_022a1d4c[];
extern s16 FOOD_PER_STAGE[];

#endif /* FARM_DATA_H */
