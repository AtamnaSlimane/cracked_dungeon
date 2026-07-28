#pragma once

// Map dimensions.
constexpr int WIDTH = 72;
constexpr int HEIGHT = 30;

// Enemy AI / regen timing (milliseconds).
constexpr int ENEMY_MOVE_INTERVAL_MS = 150;
constexpr int PLAYER_HEAL_INTERVAL_MS = 500;
constexpr int PLAYER_HEAL_AMOUNT = 2;

// Archers try to hover within
// [ARCHER_PREFERRED_RANGE, ARCHER_PREFERRED_RANGE + ARCHER_RANGE_BUFFER]
// tiles of the player.
constexpr int ARCHER_PREFERRED_RANGE = 6;
constexpr int ARCHER_RANGE_BUFFER = 3;

// Keeps enemies from spawning flush against the outer wall.
constexpr int SPAWN_MARGIN = 1;

// Defined once in map.cpp; every other file just declares it exists.
extern char dungeon[HEIGHT][WIDTH];

// inside map boundaries
inline bool inBounds(int x, int y) {
  return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}
