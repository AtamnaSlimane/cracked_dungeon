#include "player.h"
#include "config.h"
#include "enemy.h"
#include "entities.h"

int playerX = WIDTH / 2;
int playerY = HEIGHT / 2;
int playerHealth = 100;
Direction facing = DOWN;

void movePlayer(char input) {
  int newX = playerX;
  int newY = playerY;
  if (input == 'k') {
    newY--;
    facing = UP;
  }
  if (input == 'j') {
    newY++;
    facing = DOWN;
  }
  if (input == 'h') {
    newX--;
    facing = LEFT;
  }
  if (input == 'l') {
    newX++;
    facing = RIGHT;
  }

  if (dungeon[newY][newX] == '#')
    return; // wall, no move

  if (enemyAt(newX, newY))
    return;

  playerX = newX;
  playerY = newY;
}

// void attack() {
//   int attackX = playerX;
//   int attackY = playerY;
//   switch (facing) {
//   case UP:
//     attackY--;
//     break;
//   case DOWN:
//     attackY++;
//     break;
//   case LEFT:
//     attackX--;
//     break;
//   case RIGHT:
//     attackX++;
//     break;
//   }
//   for (auto &e : enemies) {
//     if (!e.alive)
//       continue;
//     if (e.x == attackX && e.y == attackY) {
//       e.hp -= 5;
//       if (e.hp <= 0)
//         e.alive = false;
//       break; // only hit one enemy
//     }
//   }
// }

void fireArrow() { bullets.push_back({playerX, playerY, facing, PLAYER, '*'}); }

void heal() { playerHealth += 2; }
