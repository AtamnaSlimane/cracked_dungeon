#include "player.h"
#include "config.h"
#include "enemy.h"
#include "entities.h"
#include "globals.h"

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

  switch (input) {
  case 'k':
    newY--;
    playerFacing = Direction::Up;
    break;
  case 'j':
    newY++;
    playerFacing = Direction::Down;
    break;
  case 'h':
    newX--;
    playerFacing = Direction::Left;
    break;
  case 'l':
    newX++;
    playerFacing = Direction::Right;
    break;
  default:
    return; // not a movement key
  }

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
