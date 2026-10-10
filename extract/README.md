This repository does not include any of the game's code or assets: you need
your own copy of the game.

Put the base ROM in this directory and check that it matches:

| Version | File name | SHA-1 |
| ------- | --------- | ----- |
| USA (`ADNE`) | `baserom_dwds_usa.nds` | `225ffc25aaf1ab4006fcdce5896d411a8fee870f` |

To rebuild the whole ROM byte for byte, the ARM7 BIOS of a DS goes in the
repository's root as `arm7_bios.bin`. It should match one of these:

| File name | SHA-1 |
| --------- | ----- |
| `arm7_bios.bin` | `6ee830c7f552c5bf194c20a2c13d5bb44bdb5c03` |
| `arm7_bios.bin` | `24f67bdea115a2c847c8813a262502ee1607b7df` |

The modules (the ARM9 program, its overlays and the ITCM and DTCM) are
checked one by one and match without it.
