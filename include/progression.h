#pragma once

constexpr int MIN_HEAL_INTERVAL = 100;
constexpr int MIN_SHOOT_INTERVAL = 0;
constexpr int MIN_MOVE_INTERVAL = 0;

// Level-up effects, triggered from the choice screen in main.cpp.
void increaseMaxHealth();
void increaseDamage();
void increaseHealthGenSpeed();
void increaseEnemySpeed();
void increaseHealthGenSpeed();
void increaseBulletSpeed();
void increasePlayerSpeed();
