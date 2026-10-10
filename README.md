# Digimon World DS decomp

| Version | Code | Data | Functions |
|---|---|---|---|
| 🇺🇸 USA (`ADNE`) | [![Code](https://decomp.dev/ReGame-Labs/dwds_decomp.svg?mode=shield&measure=code&label=Code)](https://decomp.dev/ReGame-Labs/dwds_decomp) | [![Data](https://decomp.dev/ReGame-Labs/dwds_decomp.svg?mode=shield&measure=data&label=Data)](https://decomp.dev/ReGame-Labs/dwds_decomp) | [![Functions](https://decomp.dev/ReGame-Labs/dwds_decomp.svg?mode=shield&measure=functions&label=Functions)](https://decomp.dev/ReGame-Labs/dwds_decomp) |

[![Build](https://github.com/ReGame-Labs/dwds_decomp/actions/workflows/build.yaml/badge.svg)](https://github.com/ReGame-Labs/dwds_decomp/actions/workflows/build.yaml)
[![Platform](https://img.shields.io/badge/platform-Nintendo%20DS-a6a6a6)](#the-rom)
[![Compiler](https://img.shields.io/badge/compiler-mwccarm%201.2%2Fsp4-orange)](#toolchain)
[![License](https://img.shields.io/github/license/ReGame-Labs/dwds_decomp)](LICENSE)

A work-in-progress matching decompilation of **Digimon World DS** for the
Nintendo DS, from its North American release (`ADNE`): C source that
compiles back into byte-identical copies of the game's ARM9 program and
overlays.

This repository does not contain any game data. You need your own copy of the
game to build it.

## Status

The build already gives back every module of the ROM byte for byte: the code
that isn't C yet is delinked from the original ROM by
[dsd](https://github.com/AetiasHax/ds-decomp) and linked back in, so each
function decompiled to C replaces its piece of the original while
`ninja check` keeps the match. Progress is measured by
[objdiff](https://github.com/encounter/objdiff) and tracked on
[decomp.dev](https://decomp.dev/ReGame-Labs/dwds_decomp).

On 2026-10-09, 2386 of the game's 3665 functions are C (65.1%): 244,568 of
its 1,065,540 bytes of code (23.0%). These figures count the game alone,
the ARM9 program's game code and overlays 0, 1, 2, 5 and 6, from objdiff's
report and the functions' sizes in `symbols.txt`. The badges count the
libraries too, so they show less.

## The ROM

The game is written in C and built on NitroSDK 3.0 with the Nintendo Wi-Fi
Connection libraries (WiFi SDK 1.0, DWC 1.0). Its code is the ARM9 program,
its two tightly coupled memories and seven overlays; nothing is compressed.

| Module | Address | Size | What |
|---|---|---|---|
| ARM9 | `0x02000000` | `0x13A540` | the program, entry at `0x02000800`, `.bss` up to `0x021F9BE0` |
| ITCM | `0x01FF8000` | `0x600` | autoloaded code |
| DTCM | `0x027C0000` | `0x60` | autoloaded data |
| `ov000` | `0x021F9BE0` | `0x10FE0` | the field's map; shares its address with `ov001` |
| `ov001` | `0x021F9BE0` | `0xF100` | the battle characters |
| `ov002` | `0x0222B240` | `0x2F520` | the battle; shares its address with `ov003` and `ov004` |
| `ov003` | `0x0222B240` | `0x50240` | the event scripts, data only |
| `ov004` | `0x0222B240` | `0x2B1A0` | the Wi-Fi library (DWC), built with an older compiler |
| `ov005` | `0x0227B480` | `0x26880` | the farms; shares its address with `ov006` |
| `ov006` | `0x0227B480` | `0x23FA0` | the Digimon menus |

Inside the ARM9 program, the code is in these blocks (the boundaries are
approximate until the objects are split):

| Address | What |
|---|---|
| `0x02000800` | crt0, the entry point |
| `0x02000D2C` | libraries built with an older compiler, the hand-written soft-float routines among them (`0x0202BAB0`) |
| `0x02030108` | MSL, the Metrowerks C library, built like the game |
| `0x0203B960` | the game's code |
| `0x020B6BD8` | the SDK's wireless library, built like the game |
| `0x020B8A80` | the game's code |
| `0x020B8C40` | a library built with an older compiler, NitroSystem's lists (`NNS_FndGetPrevListObject` on) and heaps first |
| `0x020C2070` | the game's code |
| `0x020D6124` | NitroSDK (the file system at `0x020D96EC`) and the Wi-Fi libraries |
| `0x0210396C` | `.rodata`, then `.data` at `0x021285E0` and `.bss` at `0x0213A540` |

## Building

On Linux (Ubuntu 24.04 or similar):

```sh
git clone https://github.com/ReGame-Labs/dwds_decomp.git
cd dwds_decomp
python3 -m venv .venv && . .venv/bin/activate
pip install -r tools/requirements.txt
```

Put your ROM in `extract/` as `baserom_dwds_usa.nds`
([extract/README.md](extract/README.md) has its SHA-1), then configure the
build and download the tools (dsd, objdiff, wibo and the compilers):

```sh
python tools/configure.py usa
ninja download_tools
python tools/configure.py usa
```

Then build and check:

```sh
ninja
```

`ninja` extracts the ROM, delinks it, compiles `src/`, links the modules and
checks every one of them against the original (`ninja check`). `ninja rom`
also builds the whole ROM as `dwds_usa.nds`. Its SHA-1 only matches with the
ARM7 BIOS in the repository's root as `arm7_bios.bin`, because the header's
secure area checksum needs it; with the BIOS there, `ninja` checks the ROM's
SHA-1 too. `ninja report` writes objdiff's progress report
(`build/usa/report.json`), and `ninja objdiff` the `objdiff.json` that
objdiff's GUI opens.

On Windows `configure.py` runs the compilers directly, without wibo.

## Toolchain

- **Compiler:** Metrowerks CodeWarrior for NINTENDO DS, `mwccarm` 1.2/sp4
  (build 2.0.0.87, April 2006) at `-O4,p`, for the game's code. 1.2/sp3
  gives the same code on everything tried so far; the 2.0 releases don't
  match. The libraries at the start and end of the ARM9 program and
  overlay 4 come from an older 1.2 release (sp2p3 or earlier): they end
  their functions with `ldm sp!, {..., lr}; bx lr` where 1.2/sp3 and later
  pop into `pc`.
- **Delinking, linking and checking:**
  [dsd](https://github.com/AetiasHax/ds-decomp) (`config/usa/arm9/`),
  with `mwldarm` as the linker.
- **Build:** `tools/configure.py` writes the `build.ninja` that
  [ninja](https://ninja-build.org) runs. On Linux the compilers run through
  [wibo](https://github.com/decompals/wibo), and
  [sjiswrap](https://github.com/encounter/sjiswrap) reads the sources as
  Shift-JIS.
- **Progress:** [objdiff](https://github.com/encounter/objdiff), and
  [decomp.me](https://decomp.me) scratches with the compiler `mwcc_20_87`.

## Contributing

Pick a function, write it as C, and check that `ninja` still passes. Only
byte-identical matches go in. [CONTRIBUTING](CONTRIBUTING.md) describes the
tools and the rules, and the [TODO](TODO.md) lists what comes next.
