#include "progression.h"
#include "entities.h"
#include "globals.h"
#include <algorithm>

void increaseMaxHealth() { playerMaxHealth += 50; }

void increaseDamage() {
  stats.playerDamage++;
  stats.meleeEnemyDamage++;
  stats.archerEnemyDamage++;
}

void increaseHealthGenSpeed() {
  stats.playerHealInterval = std::max(100, stats.playerHealInterval - 50);
}

void increaseBulletSpeed() {
  stats.playershootInterval = std::max(0, stats.playershootInterval - 50);
}

void increasePlayerSpeed() {
  stats.playermovementInterval = std::max(0, stats.playermovementInterval - 10);
}
