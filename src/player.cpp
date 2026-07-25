#include "player.h"
#include "config.h"
#include "entities.h"

int playerX = WIDTH / 2;
int playerY = HEIGHT / 2;
int playerHealth = 100;
Direction facing = DOWN;
Bullet bullet = {0, 0, RIGHT, false, '*'};

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

  playerX = newX;
  playerY = newY;
}

void attack() {
  int attackX = playerX;
  int attackY = playerY;
  switch (facing) {
  case UP:
    attackY--;
    break;
  case DOWN:
    attackY++;
    break;
  case LEFT:
    attackX--;
    break;
  case RIGHT:
    attackX++;
    break;
  }
  for (auto &e : enemies) {
    if (!e.alive)
      continue;
    if (e.x == attackX && e.y == attackY) {
      e.hp -= 5;
      if (e.hp <= 0)
        e.alive = false;
      break; // only hit one enemy
    }
  }
}

void fireArrow() {
  if (bullet.on)
    return; // only one arrow at a time
  bullet.on = true;
  bullet.dir = facing;
  bullet.x = playerX;
  bullet.y = playerY;
}

void heal() { playerHealth += 2; }
