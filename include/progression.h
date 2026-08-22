#pragma once

constexpr int MIN_HEAL_INTERVAL = 100;
constexpr int MIN_SHOOT_INTERVAL = 0;
constexpr int MIN_MOVE_INTERVAL = 0;
constexpr int MAX_BOMB_RADIUS = 72;

// Level-up effects, triggered from the choice screen in main.cpp.
void increaseMaxHealth();
void increaseDamage();
void increaseHealthGenSpeed();
void increaseEnemySpeed();
void increaseHealthGenSpeed();
void increaseBulletSpeed();
void increasePlayerSpeed();
