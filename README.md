# Terminal Dungeon Crawler

A small ASCII dungeon crawler that runs in the terminal. Work in progress.

## Build

```bash
make
```

or with CMake:

```bash
mkdir build && cd build
cmake ..
make
```

## Run

```bash
./dungeon
```

Needs a real terminal (not a build tool's output pane) since it reads raw
keyboard input.

## Controls

- `h` / `j` / `k` / `l` — move
- `f` — fire an arrow
- `q` — quit

## Structure

Code is split by subsystem under `include/` and `src/` — player, enemies,
bullets, rendering, input, and the map itself each have their own file.

More to come.
