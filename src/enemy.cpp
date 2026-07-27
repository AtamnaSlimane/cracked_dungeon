#include "enemy.h"
#include "config.h"
#include "entities.h"
#include <cmath>
std::vector<Enemy> enemies;

bool enemyAt(int x, int y) {
  for (const auto &e : enemies) {
    if (e.x == x && e.y == y)
      return true;
  }
  return false;
}

std::pair<int, int> randomSpawn() {
  int x, y;

  do {
    x = 1 + rand() % (WIDTH - 4);
    y = 1 + rand() % (HEIGHT - 4);
  } while (dungeon[y][x] == '#' || enemyAt(x, y) ||
           (x == playerX && y == playerY));

  return {x, y};
}
void loadLevel(int level) {
  enemies.clear();

  for (int i = 0; i < level + 1; ++i) {
    auto [x, y] = randomSpawn();
    enemies.push_back({x, y, 'g', 9, MELEE});
  }

  for (int i = 0; i < level; ++i) {
    auto [x, y] = randomSpawn();
    enemies.push_back({x, y, 'o', 7, ARCHER});
  }
}
bool allDead() { return enemies.empty(); }
bool inBounds(int x, int y) {
  return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}
void moveEnemies() {
  for (auto &e : enemies) {

    if (e.type == MELEE) {
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
      if (inBounds(newX, newY) && dungeon[newY][newX] != '#') {
        e.x = newX;
        e.y = newY;
      }
    } else if (e.type == ARCHER) {
      int dx = playerX - e.x;
      int dy = playerY - e.y;
      int distX = std::abs(dx), distY = std::abs(dy);

      int newX = e.x, newY = e.y;

      // if too close, back away; if too far, close in a little
      const int preferredRange = 6;
      if (distX + distY < preferredRange) {
        if (dx > 0)
          newX = e.x - 1;
        else if (dx < 0)
          newX = e.x + 1;
      } else if (distX + distY > preferredRange + 3) {
        if (dx > 0)
          newX = e.x + 1;
        else if (dx < 0)
          newX = e.x - 1;
      }

      if (inBounds(newX, e.y) && !enemyAt(newX, e.y) &&
          dungeon[e.y][newX] != '#')
        e.x = newX;

      // fire toward the player if roughly aligned on one axis
      if (e.x == playerX || e.y == playerY) {
        Direction dir;
        if (e.x == playerX)
          dir = (playerY < e.y) ? UP : DOWN;
        else
          dir = (playerX < e.x) ? LEFT : RIGHT;
        bullets.push_back({e.x, e.y, dir, ENEMY, '+'});
      }
    }
  }
}
