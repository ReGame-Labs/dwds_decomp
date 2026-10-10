#ifndef LINK_SJIS_H
#define LINK_SJIS_H

/* The link's work as its two halves see it, and the conversion of the
 * Unicode text the Wi-Fi library gives into the game's Shift JIS. */

#include "types.h"

struct LinkWork;
struct WifiWork;

struct WifiWork *getWifiWork(void);
struct LinkWork *getLinkWork(void);
u16 findSjisCode(u16 code, u16 *table, s32 count);
void convertUnicodeToSjis(char *dest, const u16 *src, u16 length);

#endif /* LINK_SJIS_H */
