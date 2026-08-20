#include "player.h"
#include "config.h"
#include "controls.h"
#include "enemy.h"
#include "entities.h"
#include "globals.h"
#include <chrono>
#include <math.h>

#include <utility>

int playerX = WIDTH / 2;
int playerY = HEIGHT / 2;
int playerHealth = 100;
Direction playerFacing = Direction::Down;

namespace {
std::pair<int, int> tileInFront() {
  switch (playerFacing) {
  case Direction::Up:
    return {playerX, playerY - 1};
  case Direction::Down:
    return {playerX, playerY + 1};
  case Direction::Left:
    return {playerX - 1, playerY};
  case Direction::Right:
    return {playerX + 1, playerY};
  }
  return {playerX, playerY};
}
} // namespace

void movePlayer(char input) {
  int newX = playerX;
  int newY = playerY;

  if (input == controls.up) {
    newY--;
    playerFacing = Direction::Up;
  } else if (input == controls.down) {
    newY++;
    playerFacing = Direction::Down;
  } else if (input == controls.left) {
    newX--;
    playerFacing = Direction::Left;
  } else if (input == controls.right) {
    newX++;
    playerFacing = Direction::Right;
  } else {
    return;
  }

  // Move if valid...
  // Bounds check added: the old version indexed dungeon[newY][newX]
  // straight away, which is only safe because the border is walled off.
  // Cheap insurance against future map edits removing that guarantee.
  if (!inBounds(newX, newY) || dungeon[newY][newX] == '#')
    return;
  if (enemyAt(newX, newY))
    return;

  playerX = newX;
  playerY = newY;
}

void fireArrow() {
  bullets.push_back({playerX, playerY, playerFacing, Owner::Player, '*'});
}

void attack() {
  auto [tx, ty] = tileInFront();
  for (auto &e : enemies) {
    if (e.x == tx && e.y == ty) {
      e.hp -= stats.playerDamage;
      return;
    }
  }
}
void explosion() {
  bullets.push_back({playerX, playerY, Direction::Up, Owner::Player, '*'});

  bullets.push_back({playerX, playerY, Direction::Down, Owner::Player, '*'});

  bullets.push_back({playerX, playerY, Direction::Left, Owner::Player, '*'});

  bullets.push_back({playerX, playerY, Direction::Right, Owner::Player, '*'});
}
void regenerateHealth() {
  if (playerHealth < playerMaxHealth)
    playerHealth += PLAYER_HEAL_AMOUNT;
}

void fullHeal() { playerHealth = playerMaxHealth; }

bool buy(int &gold, int cost) {
  if (cost > gold) {
    return false;
  } else {
    gold -= cost;
    return true;
  }
}
