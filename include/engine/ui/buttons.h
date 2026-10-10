#ifndef ENGINE_UI_BUTTONS_H
#define ENGINE_UI_BUTTONS_H

/* The touch buttons and their groups, the overlay loader and the start of a
 * new game. */

#include "types.h"

/* The modes of loadOverlay, indexes of OVERLAY_IDS, which holds the
 * overlay each one loads. Three places hold one mode each: the field's (2 or
 * 3), the battle's (0, 1 or 6) and the farm's (4 or 5). */
enum OverlayMode {
    OVERLAY_MODE_BATTLE       = 0, /* ov002 */
    OVERLAY_MODE_SCRIPTS      = 1, /* ov003, the event scripts */
    OVERLAY_MODE_FIELD        = 2, /* ov000, the field map */
    OVERLAY_MODE_BATTLE_CHARS = 3, /* ov001, the battle characters */
    OVERLAY_MODE_FARM         = 4, /* ov005 */
    OVERLAY_MODE_DIGIMON_MENU = 5, /* ov006, the Digimon menus */
    OVERLAY_MODE_WIFI         = 6, /* ov004, the Wi-Fi library */
    OVERLAY_MODE_NONE         = 0xFFFF,
};

#define BUTTON_COUNT 32  /* of BUTTONS */
#define BUTTON_NONE 0xFF /* in a group's buttons */

/* A Button's flags; 0 is a free button. */
enum ButtonFlag {
    BUTTON_RECT      = 0x1,  /* the rectangle given */
    BUTTON_SPRITE    = 0x2,  /* the bounds of the sprite's cell */
    BUTTON_NO_CURSOR = 0x8,  /* touching it doesn't make it the cursor */
    BUTTON_OBJECT    = 0x10, /* the object getSubActor or getMainActor returns */
    BUTTON_DISABLED  = 0x20,
};

/* A ButtonGroup's flags. */
enum ButtonGroupFlag {
    BUTTON_GROUP_SILENT = 0x8, /* no sound when a new button is touched */
    BUTTON_GROUP_PAUSED = 0x80,
};

struct Button;
struct ButtonGroup;
struct Rect;

s16 getGroupTappedButton(struct ButtonGroup *group);
void getSpriteCellRect();
void getSubSpriteRect(struct Rect *rect, u16 sprite);
void getMainSpriteRect(struct Rect *rect, u16 sprite);
s32 loadOverlay();
BOOL isFieldOverlayLoaded(void);
void loadFieldOverlays(void);
void initGameData(void);
s32 closeButtonGroup();
s32 addRectButton();
s32 createButtonGroup();
BOOL isButtonGroupTapped(s32 id);
BOOL takeButtonGroupTap(s32 id);
s16 getButtonGroupCursor(s32 id);
void resumeButtonGroup(s32 id);
void pauseButtonGroup(s32 id);
struct Button *getButton(s32 index, s32 id);
s16 getGroupChosenButton(struct ButtonGroup *group);
s16 getChosenButton(s32 id);
void enableButton(s32 index, s32 id);
void disableButton(s32 index, s32 id);
void setButtonGroupCursor(s32 button, s32 id);
void func_020b2228();
void func_020b2328();
void tickButtonGroup(void);
u64 getFriendCode(void);
void clearButtons(void);
s32 addObjectButton(s16 sprite, u16 flags, s32 id);
void func_020b1168();

#endif /* ENGINE_UI_BUTTONS_H */
