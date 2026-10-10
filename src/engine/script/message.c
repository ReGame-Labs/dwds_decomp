#include "engine/script/message.h"
#include "engine/data.h"
#include "engine/digimon/game_data.h"
#include "engine/script/cmd_fade.h"
#include "engine/script/operand.h"
#include "engine/text/text_banks.h"
#include "engine/ui/gauge.h"

/* The text of a message id (see MESSAGE_ID_*). */
void *getMessageText(s32 id) {
    if (id < MESSAGE_ID_SECOND_TABLE) {
        return getSpeciesShortName(id);
    }
    if (id < MESSAGE_ID_PLAYER_NAME) {
        return getCharacterName(id - MESSAGE_ID_SECOND_TABLE);
    }
    if (id < MESSAGE_ID_DIGIMON_NAME) {
        return &PLAYER_NAME;
    }
    if (id >= MESSAGE_ID_ADDRESS) {
        return (void *) id;
    }
    return func_0209d41c(id - MESSAGE_ID_DIGIMON_NAME);
}

/* Command 0xED: shows a message spoken by a Digimon in the first message
 * window, unless one is showing there, and sets event flag 0x3F2. */
s32 func_0208e260(struct ScriptThread *thread) {
    s16 digimon;
    s16 text;
    struct Digimon *speaker;

    digimon = readOperand(thread);
    text    = readOperand(thread);
    if (!(data_021d8cb8 & 1)) {
        data_021d8cb8 |= 1;
        speaker = getDigimonAt(digimon - SCRIPT_DIGIMON_FIRST);
        func_0208f068(thread, (s16) (speaker->unk1D + 8), text);
        setGameFlag(0x3F2);
    }
    return 0;
}

/* Command 0xEE: the same in the second message window. */
s32 func_0208e1e8(struct ScriptThread *thread) {
    s16 digimon;
    s16 text;
    struct Digimon *speaker;

    digimon = readOperand(thread);
    text    = readOperand(thread);
    if (!(data_021d8cb8 & 2)) {
        data_021d8cb8 |= 2;
        speaker = getDigimonAt(digimon - SCRIPT_DIGIMON_FIRST);
        func_0208f068(thread, (s16) (speaker->unk1D + 8), text);
        setGameFlag(0x3F2);
    }
    return 0;
}
