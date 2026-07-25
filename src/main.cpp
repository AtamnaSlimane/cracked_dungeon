#include "bullet.h"
#include "config.h"
#include "enemy.h"
#include "entities.h"
#include "input.h"
#include "player.h"
#include "render.h"

#include <chrono>
#include <iostream>
#include <thread>

int main() {
  enableRawMode();

  char input = '\0';
  auto lastEnemyMove = std::chrono::steady_clock::now();

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
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                       now - lastEnemyMove)
                       .count();
    if (elapsed >= 200) {
      moveEnemies();
      lastEnemyMove = now;
    }

    draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  disableRawMode();
  return 0;
}
