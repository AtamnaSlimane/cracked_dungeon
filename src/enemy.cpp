#include "enemy.h"
#include "config.h"
#include "entities.h"

std::vector<Enemy> enemies = {
    {5, 3, 'g', true, 9},   // goblin
    {15, 27, 'g', true, 9}, // goblin
    {20, 8, 'o', true, 9}   // orc
};

bool enemyAt(int x, int y) {
  for (const auto &e : enemies) {
    if (e.alive && e.x == x && e.y == y)
      return true;
  }
  return false;
}

void moveEnemies() {
  for (auto &e : enemies) {
    if (!e.alive)
      continue;

    int newX = e.x;
    int newY = e.y;

    // Compute the candidate step against the enemy's *current* position,
    // then check occupancy, then commit. No mutation inside a condition.
    if (e.x < playerX && !enemyAt(e.x + 1, e.y))
      newX = e.x + 1;
    else if (e.x > playerX && !enemyAt(e.x - 1, e.y))
      newX = e.x - 1;

    if (e.y < playerY && !enemyAt(newX, e.y + 1))
      newY = e.y + 1;
    else if (e.y > playerY && !enemyAt(newX, e.y - 1))
      newY = e.y - 1;

    // Check if enemy reaches player
    if (newX == playerX && newY == playerY) {
      playerHealth -= 10;
      continue;
    }

    // Check walls before moving
    if (dungeon[newY][newX] != '#') {
      e.x = newX;
      e.y = newY;
    }
  }
}
