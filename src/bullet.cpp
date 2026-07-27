#include "bullet.h"
#include "config.h"
#include "entities.h"

std::vector<Bullet> bullets;
int damage = 10;
void moveBullets() {
  for (auto it = bullets.begin(); it != bullets.end();) {
    switch (it->dir) {
    case UP:
      it->y--;
      break;
    case DOWN:
      it->y++;
      break;
    case LEFT:
      it->x--;
      break;
    case RIGHT:
      it->x++;
      break;
    }

    bool remove = false;

    if (it->x < 0 || it->x >= WIDTH || it->y < 0 || it->y >= HEIGHT) {
      remove = true;
    } else if (dungeon[it->y][it->x] == '#') {
      remove = true;
    } else if (it->owner == PLAYER) {
      for (auto &e : enemies) {
        if (e.x == it->x && e.y == it->y) {
          e.hp -= damage;
          remove = true;
          break;
        }
      }
    } else { // owner == ENEMY
      if (it->x == playerX && it->y == playerY) {
        playerHealth -= 8;
        remove = true;
      }
    }

    it = remove ? bullets.erase(it) : std::next(it);
  }
}
