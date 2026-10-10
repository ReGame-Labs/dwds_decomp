#include "battle/unit_panel_draw.h"
#include "engine/data.h"
#include "engine/ui/gauge.h"

/* Frees the sprite VRAM of the panel's numbers. */
void freeUnitPanelNumbers(struct UnitPanel *panel) {
    if (!(panel->flags & UNIT_PANEL_ONE_NUMBER)) {
        func_020a4c9c(&panel->numbers[1]);
    }
    func_020a4c9c(&panel->numbers[0]);
}

/* Whether the unit's panel is not moving. */
s32 isUnitPanelStill(s8 unit) {
    if (!(UNIT_PANELS[findUnitPanel(unit)].flags & UNIT_PANEL_MOVING)) {
        return 1;
    }
    return 0;
}

/* The OBJ palette of the unit's panel: 5 on, one per panel. */
u8 func_0207d3e8(s8 unit) {
    return findUnitPanel(unit) + 5;
}
