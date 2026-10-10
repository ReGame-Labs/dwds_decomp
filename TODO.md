# TODO

Every module of the ROM rebuilds byte for byte (`ninja check`), and every
function written in C matches (`tools/check_matched.py`). The game's code is
cut into files and grouped by the part of the game it runs
([src/README.md](src/README.md)). Only the game is decompiled: the libraries
stay delinked from the original, and the work on them is only to find their
objects and name their functions.

The counts below are from 2026-10-09.

## Code

- [ ] Decompile the game's 1279 functions still delinked from the original:
  873 in the ARM9 program, 42 in overlay 0, 28 in overlay 1, 100 in
  overlay 2, 112 in overlay 5 and 124 in overlay 6. Mark each file
  `complete` in `delinks.txt` once all of it is C.
- [ ] Replace m2c's 67 `M2C_FIELD` offsets (in 10 files) with struct
  members, give the parameters and the globals their real types, and drop
  `include/m2c_macros.h`. The 14 in `field/actors/actor_commands.c` and
  `engine/script/actor/props.c` reach `MAIN_MAP_STATE` and `SUB_MAP_STATE`,
  whose `struct MapState` now has the fields.
- [ ] Replace the 4 `M2C_FIELD` left in the overlays: the halfword at 0xD0
  of `data_021e0bf8` (`field/map/ov000_021fbb2c.c`) and the save's word at
  0x4438, `SaveData.unk4438` (`farm/farms.c`).
- [ ] Make `func_020a14e8` return `struct EnemyData *` and `func_020a1268`
  `struct SkillData *`, and drop their callers' casts.
- [ ] Name the `struct Digimon` fields whose meaning the comments already
  give: `unk4` the species, `unk1E` the stage, which is also the food it
  eats a day (its row of `FOOD_PER_STAGE`), `unk22` the abilities,
  `unk48`-`unk4E` attack, defense, spirit and speed, `unk54` the skills.
  Make the rename with `tools/rename.py`'s table form, apart from any match.
- [ ] Give every function a short comment saying what it does in the game;
  about 60 have none yet.
- [ ] Give the 28 headers that have none a comment at the top saying what
  the module is.
- [ ] Split the globals of the `data.h` headers (`include/engine/data.h` and
  one per overlay folder) into the headers of the files that own them, with
  the data split.

## Splitting

- [ ] Name the 8 files still named after their address once their code
  says what they are: 3 in `menus/digimon/` (overlay 6), 3 in `field/map/`
  (overlay 0) and 2 in `battle/battle_mode/` (overlay 2). Move them with
  `tools/move_sources.py`.
- [ ] Check the cuts of the game's code into files: they follow the local
  calls and the `.data` references (the `.rodata` of the game isn't in the
  order of its functions, so it says little). Merge, move or rename the
  files as the code shows what each object is, and give them their
  `.rodata`, `.data` and `.bss`.
- [ ] Split overlay 3, the event scripts' data
  (`include/field/event_scripts/data.h` holds it as one array).

## Libraries

- [ ] Find the libraries' objects: their blocks of code are known only
  roughly, from how their functions return (see the README).
- [ ] Find which libraries are linked in: NitroSDK 3.0 (the file system is
  at `0x020D96EC`), NitroSystem, the Wi-Fi libraries (WiFi SDK 1.0, DWC
  1.0, the GameSpy sources; overlay 4 is DWC), the runtime and its
  soft-float routines at `0x0202BAB0`. Name their functions from the SDK's.

## Toolchain

- [ ] The libraries' functions end with `ldm sp!, {..., lr}; bx lr`, as
  1.2/sp2p3 and earlier releases build them, where 1.2/sp3 and later pop
  into `pc`. It tells their code from the game's when finding their
  objects.
- [ ] Check 1.2/sp3 against 1.2/sp4: both give the game's code tried so
  far; keep sp4 unless a function says otherwise.
- [ ] dsd's analysis doesn't see the soft-float routines' extra entry
  points (calls into the middle of `func_0202bab0`, `func_0202cfd8`,
  `func_0202dbd8`, `func_0202e00c`, and the fall-through into
  `0x0202E208`); `dsd init` needed `--allow-unknown-function-calls`. Give
  them their own symbols.

## Names

- [ ] Name the game's functions from the strings, calls and data they use.
- [ ] Give the save's farm fields and functions the farms' names:
  `SaveData.groupTimer`, `groupOrder`, `groups` and `items` hold the farm
  day's timer, `FARM_ORDER`, `FARMS` and `PLAYER_GOODS`; `getGroup` and
  `getGroupById` find a farm (the second should return `struct Farm *`).
