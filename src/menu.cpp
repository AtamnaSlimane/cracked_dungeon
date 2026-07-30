#include "menu.h"
#include "globals.h"
#include "input.h"
#include "menu.h"
#include "player.h"
#include "progression.h"
#include <string>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

bool promptLevelUpChoice(int level) {
  std::string message = "Welcome to the shop!";

  while (true) {
    std::cout << "\033[2J\033[H";

    std::cout << "=========================================\n";
    std::cout << "               SHOP\n";
    std::cout << "=========================================\n\n";

    if (level % 5 == 0)
      std::cout << ">>> WARNING: NEXT LEVEL IS A BOSS FIGHT! <<<\n\n";

    std::cout << "Gold: " << gold << "g\n\n";

    std::cout << "Current Stats\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "Health      : " << playerHealth << "/" << playerMaxHealth
              << '\n';
    std::cout << "Damage      : " << stats.playerDamage << '\n';
    std::cout << "Heal Speed  : " << stats.playerHealInterval << " ms\n\n";

    std::cout << "Upgrades\n";
    std::cout << "-----------------------------------------\n";

    std::cout << "[1] +50 Max Health    " << cost.maxHealth << "g\n";
    std::cout << "[2] +1 Damage         " << cost.damage << "g\n";

    std::cout << "[3] Faster Healing    ";
    if (stats.playerHealInterval == MIN_HEAL_INTERVAL)
      std::cout << "MAX\n";
    else
      std::cout << cost.healSpeed << "g\n";

    std::cout << "[4] Faster Fire Rate  ";
    if (stats.playershootInterval == MIN_SHOOT_INTERVAL)
      std::cout << "MAX\n";
    else
      std::cout << cost.fireSpeed << "g\n";

    std::cout << "[5] Faster Movement   ";
    if (stats.playermovementInterval == MIN_MOVE_INTERVAL)
      std::cout << "MAX\n";
    else
      std::cout << cost.moveSpeed << "g\n";

    std::cout << "[Q] Continue\n\n";
    std::cout << "=========================================\n";
    std::cout << message << '\n';
    std::cout << "=========================================\n";

    if (!isKeyPressed()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      continue;
    }

    switch (getInput()) {
    case '1':
      if (buy(gold, cost.maxHealth)) {
        int old = playerMaxHealth;
        increaseMaxHealth();

        message = "SUCCESS! Bought +50 Max Health.\n"
                  "Max Health: " +
                  std::to_string(old) + " -> " +
                  std::to_string(playerMaxHealth);
      } else {
        message = "Not enough gold!";
      }
      break;

    case '2':
      if (buy(gold, cost.damage)) {
        int old = stats.playerDamage;
        increaseDamage();

        message = "SUCCESS! Bought +1 Damage.\n"
                  "Damage: " +
                  std::to_string(old) + " -> " +
                  std::to_string(stats.playerDamage);
      } else {
        message = "Not enough gold!";
      }
      break;

    case '3':
      if (stats.playerHealInterval == MIN_HEAL_INTERVAL) {
        message = "Healing Speed is already MAX!";
      } else if (buy(gold, cost.healSpeed)) {
        int old = stats.playerHealInterval;
        increaseHealthGenSpeed();

        message = "SUCCESS!\n"
                  "Heal Interval: " +
                  std::to_string(old) + " ms -> " +
                  std::to_string(stats.playerHealInterval) + " ms";
      } else {
        message = "Not enough gold!";
      }
      break;

    case '4':
      if (stats.playershootInterval == MIN_SHOOT_INTERVAL) {
        message = "Fire Rate is already MAX!";
      } else if (buy(gold, cost.fireSpeed)) {
        int old = stats.playershootInterval;
        increaseBulletSpeed();

        message = "SUCCESS!\n"
                  "Fire Interval: " +
                  std::to_string(old) + " ms -> " +
                  std::to_string(stats.playershootInterval) + " ms";
      } else {
        message = "Not enough gold!";
      }
      break;

    case '5':
      if (stats.playermovementInterval == MIN_MOVE_INTERVAL) {
        message = "Movement Speed is already MAX!";
      } else if (buy(gold, cost.moveSpeed)) {
        int old = stats.playermovementInterval;
        increasePlayerSpeed();

        message = "SUCCESS!\n"
                  "Move Interval: " +
                  std::to_string(old) + " ms -> " +
                  std::to_string(stats.playermovementInterval) + " ms";
      } else {
        message = "Not enough gold!";
      }
      break;

    case 'q':
    case 'Q':
      return true;
    }
  }
}
