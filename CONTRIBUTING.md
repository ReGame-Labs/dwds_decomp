# Contributing

The conventions follow the other ReGame Labs decomps, such as
[Digimon World 3's](https://github.com/ReGame-Labs/dw3_decomp), so that the
Digimon decomps read the same way, and the build follows the Nintendo DS
decomps built on [dsd](https://github.com/AetiasHax/ds-decomp), such as
[zeldaret/ph](https://github.com/zeldaret/ph). The README explains how to set
up and build the project; this file is about the work itself.

## How the build works

Nothing of the original is in the repository. `ninja` extracts the ROM into
`extract/usa/` and dsd cuts each module into pieces, as the delinks files of
`config/usa/arm9/` say:

```
src/engine/sprite/sprite_draw.c:
    .text       start:0x0203e77c end:0x0203f084
```

Every gap between the listed files is delinked from the original into an
object of its own, and so is every listed file not marked `complete`: its C
is compiled for objdiff only, which compares it with the original function
by function, while the link still takes the original's bytes. A file marked
`complete` has all of its range in C, and the link takes the compiled C
instead. The linker puts everything back together and `ninja check`
compares the result with the ROM, module by module (`check modules`), and
every symbol's address with `symbols.txt` (`check symbols`).
`tools/check_matched.py` checks the rest: every function written in C, in
the files not yet `complete` too, must be a 100% match in objdiff's report
(`ninja report` first). `ninja dis` writes the disassembly of what is still
delinked into `build/usa/asm/`.

The game's code is cut into files, one per object of the original as far as
the evidence goes: the cuts are where no local call and no `.data`
reference crosses. A file goes in the folder of the part of the game it runs
(see [Layout](#layout)), whatever module it comes from. It is named after
what it does once the evidence says so (`src/engine/sprite/sprite_draw.c`),
and until then after its module and its first address
(`src/menus/digimon/ov006_02281f70.c`). Its header has the same path under
`include/` (`include/engine/sprite/sprite_draw.h`) and declares its
functions. dsd needs the basename of every delinked file to be unique across
all the modules, so no two files share a name, even in different folders. A
file gets its entry in `delinks.txt` with its first function in C. Files are
moved or renamed with `tools/move_sources.py`, which moves the `.c` file and
its header and rewrites the delinks entries, the includes and the header's
guard; symbols are renamed with `tools/rename.py`.

The globals are declared in the `data.h` of their module's folder
(`include/engine/data.h` for the ARM9 program, `include/field/map/data.h`
for overlay 0, and so on) until the data is split into the files too, and
the library functions of the ARM9 program in `include/engine/libs.h`.
NitroSDK's inline functions, whose code the compiler wrote into the game's
functions, are in `include/nitro/` with their SDK names; only the ones the
code shows go there.

| File | What |
|---|---|
| `config/usa/arm9/delinks.txt` | the ARM9 program's sections and the source files cut from it |
| `config/usa/arm9/symbols.txt` | its functions and data, with their addresses |
| `config/usa/arm9/relocs.txt` | the relocations dsd found, the targets of its pointers |
| `config/usa/arm9/overlays/ovNNN/` | the same for each overlay |
| `config/usa/arm9/itcm/`, `dtcm/` | the same for the ITCM and the DTCM |

## Layout

`src/` is grouped by the part of the game each file runs, not by module: a
folder can hold files of the ARM9 program (`main`) and of an overlay.
`include/` has the same folders. [src/README.md](src/README.md) says what
each one holds.

| Folder | Module | What |
|---|---|---|
| `engine/` | main | what every part of the game uses: backgrounds, sprites, palettes, text, windows, the UI, the script engine, the save, the tasks and the system |
| `field/map/` | ov000 | the field's map |
| `field/actors/` | main | the field's characters |
| `battle/` | main | the battle code of the ARM9 program |
| `battle/battle_mode/` | ov002 | the battle itself: its map, turn order, the enemies' actions and the panels |
| `battle/characters/` | ov001 | the battle characters and their effects |
| `farm/` | ov005, main | the farms |
| `menus/digimon/` | ov006, main | the Digimon menu, the item menu, the status screen, the digivolution screen, the Digimon guide and the Tamer screen |
| `menus/` (the other folders) | main | the menu widgets, the DigiConvert, the field menu, the shop, the farm stats, the save, the quests, the name entry, the experience screen |
| `eggs/`, `items/`, `link/`, `title/`, `ending/` | main | the DigiEggs, the items and equipment, the wireless exchange and Wi-Fi, the title menu, the staff roll |

Overlay 3 is the event scripts' data, with no code; its header is
`include/field/event_scripts/data.h`. Overlay 4 is the Wi-Fi library (DWC):
it isn't the game's, and it stays delinked from the original.

## Decompiling a function

1. **Find it.** `ninja dis` writes the disassembly; objdiff's GUI (open the
   project's `objdiff.json` after `ninja objdiff`) shows each function, and
   its scratch button makes a [decomp.me](https://decomp.me) scratch with
   the project's compiler (`mwcc_20_87`) and flags.
2. **Get a first draft.** [m2c](https://github.com/matt-kempster/m2c)
   decompiles ARM: take the function's lines from `build/usa/asm/` (without
   the `arm_func_start`/`arm_func_end` lines and the `;` comments) into a
   `.s` file and run
   ```
   python m2c.py -t arm --valid-syntax --globals used func.s
   ```
   Give the draft the real types, the struct fields and the calls of the
   code around it.
3. **Make it match on its own.** Write a draft in a file of its own that
   includes the headers it needs, and compare it with the original:
   ```
   python tools/try_match.py draft.c func_0203e848
   ```
   It compiles the draft with the project's compiler and prints `MATCH`, or
   both versions side by side with the differing instructions marked `**`.
   Relocated fields are masked, so a different symbol name doesn't count as
   a difference. Overlay functions are named `func_ovNNN_XXXXXXXX`; give
   other names their address (`setMainSpritesBgPriority=0x0203e8d8`,
   `name=ov002:0x02249e6c`).
4. **Put it in place.** Write the function in its file, in address order
   (see below), its prototype in the file's header, and name what you
   understood in `symbols.txt`. When every function of a file is C, mark it
   `complete` in `delinks.txt`. Then rebuild and check:
   ```
   ninja && ninja report && python tools/check_matched.py
   ```
5. **Check the progress.** `ninja report` writes the progress that
   decomp.dev shows.

### The compiler writes functions backwards

`mwccarm` 1.2 emits a file's functions in the reverse of their order in the
source, and the linker keeps that order. So the original source had them in
the reverse of their order in the ROM, and a file in `src/` lists its
functions from the highest address down:

```c
void setMainSpritesBgPriority(u8 priority) { ... }  /* at 0x0203e8d8 */
void setSubSpritesBgPriority(u8 priority) { ... }   /* at 0x0203e8a8 */
```

`check symbols` says when two functions are swapped.

## Matching

- A change only counts if `ninja` still passes `check` and
  `tools/check_matched.py` passes: every module has to stay byte for byte
  identical, and every function in C has to match.
- Only byte-identical matches go in. No `NON_MATCHING` code, no `#if 0`
  blocks and no assembly in place of C (`asm` functions or blocks). A
  function that doesn't match yet stays delinked from the original.
  `tools/hacks.py` fails the CI on these.
- No fake matches: no `volatile`, junk temporaries, dead stores, empty or
  breakless `do`/`while (0)` barriers or identical arms to force the
  compiler. A function that only matches that way stays delinked, with what
  was found in `TODO.md`. `tools/hacks.py` counts the comments that start
  with `/* fake match:`, and the count stays at zero.
- A match that depends on a form the reader wouldn't expect (a local of
  another type, an order of statements) says so in a short comment with
  "match depends on" and why; `tools/hacks.py` counts these too.
- Only the game is decompiled. The libraries stay delinked from the
  original: NitroSDK, the Wi-Fi libraries and the runtime (the start and
  the end of main, 0x02000000-0x02030108 and 0x020d6124 on, and the block
  0x020b8c40-0x020c2070, NitroSystem's lists and heaps first, built with an
  older compiler), overlay 4, the ITCM, MSL, the Metrowerks C library
  (0x02030108-0x0203b960, built like the game), and the SDK's wireless
  library (0x020b6bd8-0x020b8a80, built like the game). Their functions are declared in `include/engine/libs.h`.
- The game's code is built with `mwccarm` 1.2/sp4.

## Code

Look at the C around you and write the same way.

- Four spaces, no tabs; the opening brace on the same line; braces around
  every `if`, `for` and `while` body; one statement per line.
  `clang-format` (`.clang-format`) formats it, and the pre-commit hooks run
  it: `pre-commit install` once.
- Comments are `/* */`. A function gets a short comment above it that says
  what it does in the game (`/* Opens the Digimon's status screen on the
  given tab */`); a block of code gets one for what the code can't say: a
  magic number, a file, a mode, why a form matches.
- The types are `include/types.h`'s (`s8`, `u8`, `s16`, `u16`, `s32`,
  `u32`, `BOOL`) and the SDK's where the code talks to it.
- Struct fields keep their offset in a comment, and the ones not understood
  yet are named by it:
  ```c
  struct SpeciesData {
      /* 0x00 */ u16 id;
      /* 0x02 */ u8 level;
      /* 0x03 */ u8 unk3;
  };
  ```
- `NULL` for pointers, `0` for integers, `TRUE`/`FALSE` for `BOOL`.
- A header declares what its `.c` file defines; every header has an
  `#ifndef <PATH>_H` guard and a comment at the top that says what the
  module is. A `.c` file includes the headers of what it uses and declares
  nothing of another file's.
- NitroSDK's inline functions, whose code the compiler wrote into the
  game's functions, are in `include/nitro/` with their SDK names; only the
  ones the code shows go there. The library functions the game calls are
  declared in `include/engine/libs.h`, with their SDK names once known.
- `CLEAR(ptr, size)` (`include/types.h`) is the compiler's zero-fill
  intrinsic, for the stores of zeroed registers that no plain C statement
  gives.

## Names

A name has to come from evidence: the strings and files a function uses,
the SDK calls it makes, its callers, the data it reads, the game's texts.
What isn't understood yet keeps dsd's name (`func_0203e848`,
`func_ov006_02287ca4`, `data_021e0012`) or its offset (`unk14`). A wrong
name costs more than an address.

| What | Style | Examples |
|---|---|---|
| Functions | camelCase, a verb that says what it does | `loadSpeciesData`, `openStatsScreen`, `heapAlloc` |
| Globals and tables | UPPER_SNAKE, as in the other ReGame decomps | `EGG_GALLERY`, `TASK_SLOTS` |
| Types | PascalCase | `SpeciesData`, `DigimonGuide`, `TextWindow` |
| Struct fields | camelCase, with the offset comment kept | `/* 0x58 */ s32 cursor;` |
| Parameters and locals | camelCase, the same word for the same thing everywhere | `task`, `digimon`, `window`, `id` |
| Constants and enum values | UPPER_SNAKE, the enum's name first | `OVERLAY_MODE_FIELD`, `ITEM_ID_ARMOR` (the SDK's keep theirs, `PAD_BUTTON_A`) |
| Macros | UPPER_SNAKE | `CLEAR` |
| Library functions | the SDK's name | `FS_LoadOverlay`, `NNS_FndFreeToExpHeap` |

Verbs: a task's per-frame update is `tick*`, the function that creates it
`start*Task`; `draw*` draws, `create*` sets up and returns an object,
`init*`, `load*`, `open*`/`close*`, `get*`/`set*`, `is*`/`has*`.

Every name goes in the symbol file of its module (`symbols.txt`), so that
dsd and objdiff use it too.

## Clean code

Every change follows these rules, after the match: nothing goes in that
breaks a module or a function.

- **Names tell the truth.** Name only what the evidence supports, and keep
  `unkXX`, `func_` and `data_` rather than guess. One word for one concept
  everywhere.
- **No magic numbers.** A number whose meaning is known gets a constant or
  an enum in its owner's header (`PAD_*`, an element, a tab, a file), and
  sizes are `sizeof`; one that isn't known stays as it is.
- **Types instead of casts.** Real struct members, unions for two views of
  the same memory, the right parameter and return types. No `M2C_FIELD`
  offsets and no m2c names (`temp_r0`, `var_r4`, `arg0`) in finished code. A
  cast that stays says why.
- **One declaration per symbol**, in the header of the file that defines
  it, which its users include. No copies of externs or prototypes.
- **Shared code once.** Code the game repeats (an inline it wrote into many
  functions, like `heapAlloc`) is one `static inline` function in a header,
  not copies. A helper exists only where the game has one: no
  abstractions for looks.
- **Comments say why.** Stale comments, commented-out code and TODOs in the
  code go; open questions go in `TODO.md`.
- **No dead code or fake matches**: no junk temporaries, unread locals,
  `volatile`, an empty `do`/`while (0)` or one without a `break` used as a
  barrier, or branches with identical arms.
- **Renames by script.** A rename is made with a script that can be run
  again, so that other branches can apply it after a rebase.

## Evidence

- Work out what the original code did, then write it the way its
  programmers would have; the match is the floor, not the goal.
- Every change made to match has a reason: what it changes in the
  generated code and why. No blind trial of variants, no permuter output
  taken as it is.
- A name, a type or a comment says what the evidence shows. When it is a
  guess, say so ("probably the egg's kind") or leave it unnamed.
- Search the code before inventing: a type, a constant or a helper may
  already exist.
- Keep the original's strange behaviour, its bugs included.
- Matching, renaming and moving code are separate changes.

## Commits

- Commit messages are one short sentence in the imperative, without a
  trailing period, about the game: "Decompile the Digimon guide's list",
  "Name the species data's fields". Add a body when the change needs
  explaining: what was found, why a form matches. No trailers.
- One theme per commit. Matches, renames and moves go in separate commits:
  decomp.dev shows a renamed or moved function as broken under its old name
  and new under the new one.
- A commit that renames lists the renames (address, old name, new name).
- Before committing, run the checks the CI runs:
  ```
  ninja && ninja report && python tools/check_matched.py && python tools/hacks.py
  ```
