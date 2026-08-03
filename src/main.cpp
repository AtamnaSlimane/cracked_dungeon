#include "bullet.h"
#include "config.h"
#include "controls.h"
#include "enemy.h"
#include "entities.h"
#include "globals.h"
#include "input.h"
#include "menu.h"
#include "player.h"
#include "progression.h"
#include "render.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

namespace {
using Clock = std::chrono::steady_clock;

void removeDeadEnemies() {
  for (auto it = enemies.begin(); it != enemies.end();) {
    if (it->hp <= 0) {
      gold += it->goldReward;
      it = enemies.erase(it);
    } else {
      ++it;
    }
  }
}
} // namespace

int main() {
  enableRawMode();

  char input = '\0';
  auto lastEnemyMove = Clock::now();
  auto lastPlayerMove = Clock::now();
  auto lastShot = Clock::now();
  auto lastHeal = Clock::now();
  chooseControls();
  loadLevel(level);

  while (true) {
    if (isKeyPressed()) {
      input = getInput();
      auto now = Clock::now();
      if (std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                                lastPlayerMove)
              .count() >= stats.playermovementInterval) {
        movePlayer(input);
        lastPlayerMove = now;
      }

      if (input == 'f') {
        auto now = Clock::now();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                                  lastShot)
                .count() >= stats.playershootInterval) {
          fireArrow();
          lastShot = now;
        }
      }
    }

    moveBullets();

    if (playerHealth <= 0) {
      disableRawMode();
      std::cout << "you're dead" << std::endl;
      return 0;
    }

    if (input == 'Q')
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
      while (!promptLevelUpChoice(level + 1)) {
      }
      level++;
      if (level % 5 == 0) {

        loadBoss(level / 5);
      } else {
        loadLevel(level);
      }
      increaseEnemySpeed();
      fullHeal();
    }

    draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  disableRawMode();
  return 0;
}
