#include "render.h"
#include "config.h"
#include "entities.h"
#include "globals.h"
#include <algorithm>
#include <iostream>

void draw() {
  std::cout << "\033[H";
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      char tile = dungeon[y][x];

      for (auto &e : enemies) {
        if (e.x == x && e.y == y) {
          if (e.hp < 10) {
            tile = '0' + e.hp;
          } else {
            tile = e.symbol;
          }
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
  std::cout << "Move: h/j/k/l   Fire: f    Level:  " << level
            << "   Health: " << playerHealth
            << "  Damage: " << stats.playerDamage << "   Quit: q \n";
  std::cout << "Enemies left: " << enemies.size() << '\n';
  std::cout << "Heal speed: " << stats.playerHealInterval << '\n';
  std::cout << "Enemy speed: " << ENEMY_MOVE_INTERVAL_MS << '\n';
  std::cout << "gold : " << gold << '\n';
  if (level % 5 == 0) {

    const int BAR_WIDTH = 30;

    int bossMaxHealth = BOSS_BASE_HEALTH * (level / 5);
    int filled = enemies[0].hp * BAR_WIDTH / bossMaxHealth;

    std::cout << "Boss: [";
    for (int i = 0; i < BAR_WIDTH; i++) {
      std::cout << (i < filled ? '=' : ' ');
    }
    std::cout << "] " << enemies[0].hp << "/" << bossMaxHealth << '\n';
  }

  std::cout << std::flush;
}
