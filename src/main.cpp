#include "bullet.h"
#include "config.h"
#include "enemy.h"
#include "entities.h"
#include "input.h"
#include "player.h"
#include "render.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  enableRawMode();

  char input = '\0';
  auto lastEnemyMove = std::chrono::steady_clock::now();
  auto lastHeal = std::chrono::steady_clock::now();
  int level = 1;
  loadLevel(level);
  while (true) {

    if (isKeyPressed()) {
      input = getInput();
      if (input == 'f') {
        fireArrow();
      } else {
        movePlayer(input);
      }
    }

    moveBullets();

    if (playerHealth <= 0) {
      disableRawMode();
      std::cout << "youre dead" << std::endl;
      return 0;
    }

    if (input == 'q')
      break;

    auto now = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(now -
                                                              lastEnemyMove)
            .count() >= 150) {
      moveEnemies();
      lastEnemyMove = now;
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastHeal)
            .count() >= 500) {
      heal();
      lastHeal = now;
    }
    // if (elapsed >= 450) {
    //   heal();
    // }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](const Enemy &e) { return e.hp <= 0; }),
                  enemies.end());

    std::cerr << "Enemies left: " << enemies.size() << '\n';

    if (allDead()) {
      fullHeal();
      std::cout << "Loading level " << level << '\n';
      loadLevel(level++);
      std::cout << "Enemies spawned: " << enemies.size() << '\n';
    }
    draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  disableRawMode();
  return 0;
}
