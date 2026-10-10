#include "battle/battle_mode/battle_map.h"
#include "battle/battle_mode/ov002_0222c3bc.h"
#include "engine/bg/bg_layers.h"
#include "engine/debug/debug_print.h"
#include "engine/system/display_modes.h"

/* Sets the map's scroll back to the start and starts its task, closes the
 * debug print and sets both screens' background offsets to 0. */
void func_ov002_0222c318(void) {
    resetMapScroll();
    startMapScrollTask();
    closeDebugPrint();
    func_020a3454(0);
    setSubBgOffset(0, 0, 0);
    setSubBgOffset(1, 0, 0);
    setSubBgOffset(2, 0, 0);
    setSubBgOffset(3, 0, 0);
    setMainBgOffset(0, 0, 0);
    setMainBgOffset(1, 0, 0);
    setMainBgOffset(2, 0, 0);
    setMainBgOffset(3, 0, 0);
}
