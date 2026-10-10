# src

The game's C, grouped by the part of the game it runs. The module is where
the code is in the ROM: `main` is the ARM9 program, `ovNNN` its overlays.
Each file's header has the same path under `include/`.

| Folder | Module | What |
|---|---|---|
| `engine/bg/` | main | the backgrounds: loading, screens, layers, affine BGs |
| `engine/debug/` | main | the debug console printed on a BG |
| `engine/digimon/` | main | the Digimon's records, digivolution, species flags and game data |
| `engine/gfx/` | main | the graphics files' helpers |
| `engine/input/` | main | the touch screen |
| `engine/movie/` | main | the movie player |
| `engine/palette/` | main | the palette buffers, fades and uploads |
| `engine/save/` | main | the save data, the card backup, the game state and progress |
| `engine/script/` | main | the event script engine: its interpreter and commands |
| `engine/script/actor/` | main | the script engine's commands on the actors |
| `engine/sprite/` | main | the sprites: their creation, resources and drawing |
| `engine/system/` | main | the tasks, the display and the game's setup |
| `engine/text/` | main | the font, the text banks and the printing of text |
| `engine/ui/` | main | buttons, captions, dials, gauges and the Digimon list |
| `engine/window/` | main | the windows, the dialogue window, message boxes and choices |
| `field/map/` | ov000 | the field's map, its characters and sprites |
| `field/actors/` | main | the field's characters (actors): their files, walking, routes and commands |
| `battle/` | main | the ARM9 program's battle code: stat bonuses, experience, the battle state, the unit panels |
| `battle/battle_mode/` | ov002 | the battle itself: its state, start and end, map, background, turn order, the enemies' actions, panels, movie and link setup |
| `battle/characters/` | ov001 | the battle characters, their effects and their move scripts |
| `farm/` | ov005, main | the farms: their screen, goods, events, the day's results and food, and the exit question |
| `menus/digimon/` | ov006, main | the Digimon menu, the item menu, the status screen, the trait learning menu, the digivolution screen, the Digimon guide and the Tamer screen (`menu_digivolve.c` is main's) |
| `menus/widgets/` | main | the parts the menus share: lists, scroll bars, status windows, item and skill displays |
| `menus/digiconvert/` | main | the DigiConvert and its conversion scene |
| `menus/field_menu/` | main | the field menu and its panels |
| `menus/shop/` | main | the item, equipment and farm shops |
| `menus/farm_stats/` | main | the View Stats screen |
| `menus/save/` | main | the save menu |
| `menus/quests/` | main | the quest list |
| `menus/name_entry/` | main | the name entry screen |
| `menus/experience/` | main | the experience gained screen |
| `eggs/` | main | the DigiEggs: breeding, hatching, the egg list and the family tree |
| `items/` | main | the item stocks and the equipment |
| `link/` | main | the wireless exchange, farm visits, the training menu and Wi-Fi |
| `title/` | main | the title menu |
| `ending/` | main | the staff roll |

Overlay 3 is the event scripts' data, with no code; its header is
`include/field/event_scripts/data.h`. Overlay 4 is the Wi-Fi library (DWC)
and stays delinked from the original, like the other libraries.
