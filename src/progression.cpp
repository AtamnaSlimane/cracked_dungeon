#include "progression.h"
#include "entities.h"

void increaseMaxHealth() { playerMaxHealth += 50; }

void increaseDamage() {
  stats.playerDamage++;
  stats.meleeEnemyDamage++;
  stats.archerEnemyDamage++;
}
