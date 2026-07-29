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
        if (e.x == x && e.y == y) {
          tile = '0' + e.hp;
        }
      }

      if (x == playerX && y == playerY)
        tile = '@';

      for (auto &b : bullets) {
        if (b.x == x && b.y == y)
          tile = b.symbol;
      }

      std::cout << tile;
    }
    std::cout << "\n";
  }
  std::cout << "Move: h/j/k/l   Fire: f   Health: " << playerHealth
            << "  Damage: " << stats.playerDamage << "   Quit: q \n";
  std::cout << "Enemies left: " << enemies.size() << '\n';
  std::cout << "Heal speed: " << stats.playerHealInterval << '\n';
  std::cout << std::flush;
}
