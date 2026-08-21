#pragma once
#include "entities.h"
#include <vector>

inline CombatStats stats;
inline int level = 1;
inline int gold = 0;
inline Cost cost;
inline int playerMaxHealth = 100;
inline int explosionRadius = 7;
inline int explosionDuration = 100;
inline int bombs = 0;

inline std::vector<Enemy> enemies;
inline std::vector<Bullet> bullets;
