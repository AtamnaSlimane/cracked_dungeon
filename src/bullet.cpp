#include "bullet.h"
#include "config.h"
#include "entities.h"

void moveBullet() {
  if (!bullet.on)
    return;

  switch (bullet.dir) {
  case UP:
    bullet.y--;
    break;
  case DOWN:
    bullet.y++;
    break;
  case LEFT:
    bullet.x--;
    break;
  case RIGHT:
    bullet.x++;
    break;
  }

  // hit wall?
  if (dungeon[bullet.y][bullet.x] == '#') {
    bullet.on = false;
    return;
  }

  // hit enemy?
  for (auto &e : enemies) {
    if (!e.alive)
      continue;
    if (e.x == bullet.x && e.y == bullet.y) {
      e.hp -= 5;
      if (e.hp <= 0)
        e.alive = false;
      bullet.on = false;
      return;
    }
  }
}
