#include "link/sjis.h"
#include "engine/data.h"

/* The Shift JIS code of a Unicode one, looked up in count + 1 pairs of {Shift
 * JIS, Unicode} (data_02127e00 and others, for convertUnicodeToSjis), or 0x8140, the
 * Shift JIS space. */
u16 findSjisCode(u16 code, u16 *table, s32 count) {
    count++;
    while (count-- != 0) {
        if (table[1] == code) {
            return table[0];
        }
        table += 2;
    }
    return 0x8140;
}

/* The work of a local link. */
struct LinkWork *getLinkWork(void) {
    return LINK_WORK;
}

/* The work of a link over Wi-Fi. */
struct WifiWork *getWifiWork(void) {
    return LINK_WORK;
}
