#include "enemy.h"
#include "config.h"
#include "entities.h"

#include <cmath>
#include <random>

std::vector<Enemy> enemies;

namespace {
std::mt19937 rng{std::random_device{}()};

std::pair<int, int> randomSpawn() {
  std::uniform_int_distribution<int> xDist(SPAWN_MARGIN,
                                           WIDTH - SPAWN_MARGIN - 3);
  std::uniform_int_distribution<int> yDist(SPAWN_MARGIN,
                                           HEIGHT - SPAWN_MARGIN - 3);
  int x, y;
  do {
    x = xDist(rng);
    y = yDist(rng);
  } while (dungeon[y][x] == '#' || enemyAt(x, y) ||
           (x == playerX && y == playerY));
  return {x, y};
}

void moveMelee(Enemy &e) {
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

  if (newX == playerX && newY == playerY) {
    playerHealth -= stats.meleeEnemyDamage;
    return;
  }
  if (inBounds(newX, newY) && dungeon[newY][newX] != '#') {
    e.x = newX;
    e.y = newY;
  }
}

void moveArcher(Enemy &e) {
  int dx = playerX - e.x;
  int dy = playerY - e.y;
  int dist = std::abs(dx) + std::abs(dy);
  int newX = e.x;

  // Too close: back away. Too far: close in a little. Otherwise hold.
  if (dist < ARCHER_PREFERRED_RANGE) {
    if (dx > 0)
      newX = e.x - 1;
    else if (dx < 0)
      newX = e.x + 1;
  } else if (dist > ARCHER_PREFERRED_RANGE + ARCHER_RANGE_BUFFER) {
    if (dx > 0)
      newX = e.x + 1;
    else if (dx < 0)
      newX = e.x - 1;
  }

  if (inBounds(newX, e.y) && !enemyAt(newX, e.y) && dungeon[e.y][newX] != '#')
    e.x = newX;

  // Fire toward the player if roughly aligned on one axis.
  if (e.x == playerX || e.y == playerY) {
    Direction dir;
    if (e.x == playerX)
      dir = (playerY < e.y) ? Direction::Up : Direction::Down;
    else
      dir = (playerX < e.x) ? Direction::Left : Direction::Right;
    bullets.push_back({e.x, e.y, dir, Owner::Enemy, '+'});
  }
}
} // namespace

bool enemyAt(int x, int y) {
  for (const auto &e : enemies) {
    if (e.x == x && e.y == y)
      return true;
  }
  return false;
}

void loadLevel(int level) {
  enemies.clear();
  for (int i = 0; i < level + 1; ++i) {
    auto [x, y] = randomSpawn();
    enemies.push_back({x, y, 'g', 9, EnemyType::Melee});
  }
  for (int i = 0; i < level; ++i) {
    auto [x, y] = randomSpawn();
    enemies.push_back({x, y, 'o', 7, EnemyType::Archer});
  }
}

bool allDead() { return enemies.empty(); }

void moveEnemies() {
  for (auto &e : enemies) {
    if (e.type == EnemyType::Melee)
      moveMelee(e);
    else
      moveArcher(e);
  }
}
