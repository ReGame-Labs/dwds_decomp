#include "menus/digimon/guide_open.h"
#include "battle/characters/chr.h"
#include "engine/data.h"
#include "engine/libs.h"
#include "engine/palette/palette_buffers.h"
#include "engine/sprite/sprite_create.h"
#include "engine/system/system.h"
#include "engine/ui/buttons.h"
#include "engine/window/window.h"
#include "field/actors/actor_create.h"
#include "field/actors/actor_tasks.h"
#include "menus/digimon/data.h"
#include "menus/digimon/guide_data.h"
#include "menus/digimon/guide_graphics.h"
#include "menus/digimon/guide_window_texts.h"
#include "menus/digimon/guide_windows.h"

/* Frees what the guide shows, but not its task or its work, and clears both
 * screens, before openStatusScreen takes them over with the Digimon of the
 * cursor's row; restoreDigimonGuide makes it all again. */
void func_ov006_0229e2d0(struct DigimonGuide *guide) {
    void *block;

    block = guide->unk70;
    if (block != NULL) {
        heapFree(block);
        guide->unk70 = NULL;
    }
    block = guide->unk74;
    if (block != NULL) {
        heapFree(block);
        guide->unk74 = NULL;
    }
    stopSubPaletteEffectsButFades(GUIDE_SUB_PALETTE_EFFECT);
    stopMainPaletteEffectsButFades(GUIDE_MAIN_PALETTE_EFFECT);
    freeMainSprites();
    freeSubSprites();
    removeAllMainBattleChrs();
    removeAllSubBattleChrs();
    endBattleChrs();
    deleteSubActors();
    endSubActorTask();
    func_ov006_0229c4d4();
    func_ov006_0229c04c();
    func_ov006_0229be68();
    func_ov006_0229b814(guide);
    if (guide->listWindow != 0xFF) {
        closeWindow(guide->listWindow);
        guide->listWindow = 0xFF;
    }
    if (guide->unk5F != 0xFF) {
        closeWindow(guide->unk5F);
        guide->unk5F = 0xFF;
    }
    if (guide->unk61 != 0xFF) {
        closeWindow(guide->unk61);
        guide->unk61 = 0xFF;
    }
    if (guide->nameWindow != 0xFF) {
        closeWindow(guide->nameWindow);
        guide->nameWindow = 0xFF;
    }
    if (guide->tabWindow != 0xFF) {
        closeWindow(guide->tabWindow);
        guide->tabWindow = 0xFF;
    }
    if (guide->pageButtons != -1) {
        closeButtonGroup(guide->pageButtons);
        guide->pageButtons = -1;
    }
    if (guide->arrowButtons != -1) {
        closeButtonGroup(guide->arrowButtons);
        guide->arrowButtons = -1;
    }
    if (guide->rowButtons != -1) {
        closeButtonGroup(guide->rowButtons);
        guide->rowButtons = -1;
    }
    if (guide->tabButtons != -1) {
        closeButtonGroup(guide->tabButtons);
        guide->tabButtons = -1;
    }
    if (guide->unk40 != -1) {
        closeButtonGroup(guide->unk40);
        guide->unk40 = -1;
    }
    if (guide->chrButton != -1) {
        closeButtonGroup(guide->chrButton);
        guide->chrButton = -1;
    }
    func_ov006_0229972c();
    func_ov006_02299548();
    func_ov006_02299364();
    freeGuideTexts();
    func_ov006_0229914c();
    func_ov006_02298640();
    func_ov006_02298fb8();
    func_ov006_02298cc4();
    func_020a95c0();
    func_ov006_0229c164();
}
