#include "render.h"
#include "config.h"
#include "entities.h"
#include <iostream>

void draw() {
  std::cout << "\033[H";
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      char tile = dungeon[y][x];

      for (auto &e : enemies) {
        if (e.alive && e.x == x && e.y == y) {
          tile = '0' + e.hp;
        }
      }

      if (x == playerX && y == playerY)
        tile = '@';

      if (bullet.on && x == bullet.x && y == bullet.y) {
        tile = bullet.symbol;
      }

      std::cout << tile;
    }
    std::cout << "\n";
  }
  std::cout << "Move: h/j/k/l   Fire: f   Health: " << playerHealth
             << "   Quit: q \n";
  std::cout << std::flush;
}
