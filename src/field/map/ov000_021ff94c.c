#include "field/map/ov000_021ff94c.h"
#include "engine/libs.h"
#include "nitro/g2.h"
#include "nitro/mi.h"
#include "nitro/mmap.h"

/* Clears the main screen: its BG and OBJ VRAM and its OAM, then calls the
 * library's func_020da508-func_020da564 and turns its blending off. */
void clearMainScreenAndBlending(void) {
    MI_CpuClearFast((void *) HW_BG_VRAM, HW_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_OAM, HW_OAM_SIZE);
    func_020da564();
    func_020da550();
    func_020da52c();
    func_020da508();
    REG_BLDCNT = 0;
}

/* The same for the sub screen. */
void clearSubScreenAndBlending(void) {
    MI_CpuClearFast((void *) HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
    MI_CpuClearFast((void *) HW_DB_OAM, HW_OAM_SIZE);
    func_020da4b8();
    func_020da4a4();
    func_020da47c();
    func_020da454();
    REG_DB_BLDCNT = 0;
}
