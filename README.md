# Cracked Dungeon

A terminal-based dungeon crawler written in C++. No graphics libraries, no dependencies — just raw ANSI escape codes, raw terminal input, and a grid of characters.

```
######################################################################
#....................................................................#
#..........................g.........................................#
#....................................o...............................#
#..............................@*....................................#
#....................................................................#
#....................................................................#
######################################################################
Move: q/s/z/d   Fire: j   Level: 1   Health: 100  Damage: 3   Quit: Q
Enemies left: 2
```

## Features

- **Real-time combat** — move and fire arrows in the direction you're facing, no turn order.
- **Bombs** — trigger an area-of-effect explosion (with a screen flash) that damages every enemy in radius.
- **Three enemy types**
  - **Melee** — charges straight at you.
  - **Archer** — keeps its distance, backs off if you get too close, and fires when lined up with you.
  - **Boss** — spawns every 5th level, has much higher health, and both chases and shoots.
- **Progression shop** — clear a level to open a shop between rounds. Spend gold on:
  - Max health
  - Damage
  - Heal speed
  - Fire rate
  - Movement speed
  - Bomb count
  - Bomb radius
  - Bomb damage
- **Configurable controls** — choose Vim, WASD, or ZQSD (AZERTY) bindings on first launch; your choice is saved to `controls.cfg` and reloaded automatically next time.
- **Scaling difficulty** — enemies spawn in greater numbers and move faster as you progress, with a boss fight every 5 levels.

## Controls

Movement and fire keys depend on the layout you pick at startup:

| Action | Vim | WASD | ZQSD |
|---|---|---|---|
| Up | `k` | `w` | `z` |
| Down | `j` | `s` | `s` |
| Left | `h` | `a` | `q` |
| Right | `l` | `d` | `d` |
| Fire | `f` | `j` | `j` |

Other keys:

| Key | Action |
|---|---|
| `e` | Detonate a bomb (if you have one) |
| `Q` | Quit |
| `c` | Change controls (in the shop menu) |

## Building

Requires a C++ compiler with C++17 support and CMake. Terminal input relies on POSIX APIs (`termios`, `unistd.h`), so this currently targets **Linux/macOS** only.

```bash
git clone https://github.com/<your-username>/cracked_dungeon.git
cd cracked_dungeon
cmake -B build
cmake --build build
./build/cracked_dungeon
```

## Project structure

```
.
├── include/          # Public headers, one module per concern
│   ├── bullet.h
│   ├── config.h       # Map dimensions & tunable constants
│   ├── controls.h
│   ├── enemy.h
│   ├── entities.h     # Shared structs & extern globals
│   ├── globals.h       # Global game state
│   ├── input.h
│   ├── menu.h
│   ├── player.h
│   ├── progression.h
│   └── render.h
├── src/               # One .cpp per header
│   ├── bullet.cpp
│   ├── controls.cpp
│   ├── enemy.cpp
│   ├── input.cpp
│   ├── main.cpp
│   ├── map.cpp
│   ├── menu.cpp
│   ├── player.cpp
│   ├── progression.cpp
│   └── render.cpp
└── CMakeLists.txt
```

## How it works

- The game loop polls for input non-blockingly (`select()` on stdin) and advances player movement, enemy AI, and bullets on independent timers, so speed upgrades genuinely change the pacing of the game rather than just a stat number.
- The dungeon is a fixed `char[HEIGHT][WIDTH]` grid; entities are drawn by overlaying their symbol on top of the base tile each frame.
- Enemies and bullets are tracked in flat `std::vector`s and rebuilt/pruned each frame rather than using pointers, keeping the update logic simple.

## Roadmap ideas

- [ ] Windows support (swap `termios`/`select` for a portable input layer)
- [ ] Persistent high scores
- [ ] More enemy types / level variety
- [ ] Save/resume mid-run

