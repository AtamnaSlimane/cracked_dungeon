#include "bullet.h"
#include "config.h"
#include "entities.h"
#include "globals.h"

#include <iterator>

namespace {
void step(Bullet &b) {
  switch (b.dir) {
  case Direction::Up:
    b.y--;
    break;
  case Direction::Down:
    b.y++;
    break;
  case Direction::Left:
    b.x--;
    break;
  case Direction::Right:
    b.x++;
    break;
  }
}

bool hitsWall(const Bullet &b) {
  // Order matters: inBounds() is checked first so an out-of-bounds
  // bullet never indexes dungeon[][] out of range.
  return !inBounds(b.x, b.y) || dungeon[b.y][b.x] == '#';
}

// Returns true (and applies damage) if the bullet connects with a target.
bool hitsTarget(Bullet &b) {
  if (b.owner == Owner::Player) {
    for (auto &e : enemies) {
      if (e.x == b.x && e.y == b.y) {
        e.hp -= stats.playerDamage;
        return true;
      }
    }
    return false;
  }
  if (b.x == playerX && b.y == playerY) {
    playerHealth -= stats.archerEnemyDamage;
    return true;
  }
  return false;
}
} // namespace

void moveBullets() {
  for (auto it = bullets.begin(); it != bullets.end();) {
    step(*it);
    bool remove = hitsWall(*it) || hitsTarget(*it);
    it = remove ? bullets.erase(it) : std::next(it);
  }
}
