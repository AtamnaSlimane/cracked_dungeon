#include "bullet.h"
#include "config.h"
#include "enemy.h"
#include "entities.h"
#include "input.h"
#include "player.h"
#include "progression.h"
#include "render.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

namespace {
using Clock = std::chrono::steady_clock;

bool promptLevelUpChoice() {
  std::cout << "\033[2J\033[H";
  std::cout << "=== LEVEL COMPLETE ===\n\n";
  std::cout << "1. Increase Health\n";
  std::cout << "2. Increase Damage\n";
  std::cout << "3. Increase Heal Speed\n";

  while (true) {
    if (isKeyPressed()) {
      switch (getInput()) {
      case '1':
        increaseMaxHealth();
        return true;
      case '2':
        increaseDamage();
        return true;
      case '3':
        increaseHealthGenSpeed();
        return true;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void removeDeadEnemies() {
  enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                               [](const Enemy &e) { return e.hp <= 0; }),
                enemies.end());
}
} // namespace

int main() {
  enableRawMode();

  char input = '\0';
  auto lastEnemyMove = Clock::now();
  auto lastHeal = Clock::now();
  int level = 1;
  loadLevel(level);

  while (true) {
    if (isKeyPressed()) {
      input = getInput();
      if (input == 'f')
        fireArrow();
      else
        movePlayer(input);
    }

    moveBullets();

    if (playerHealth <= 0) {
      disableRawMode();
      std::cout << "you're dead" << std::endl;
      return 0;
    }

    if (input == 'q')
      break;

    auto now = Clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                              lastEnemyMove)
            .count() >= ENEMY_MOVE_INTERVAL_MS) {
      moveEnemies();
      lastEnemyMove = now;
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastHeal)
            .count() >= stats.playerHealInterval) {
      regenerateHealth();
      lastHeal = now;
    }

    removeDeadEnemies();

    if (allDead()) {
      while (!promptLevelUpChoice()) {
      }
      level++;
      loadLevel(level);
      fullHeal();
    }

    draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  disableRawMode();
  return 0;
}
