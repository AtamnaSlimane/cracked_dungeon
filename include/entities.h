#pragma once
#include <vector>

enum class Direction { Up, Down, Left, Right };
enum class EnemyType { Melee, Archer };
enum class Owner { Player, Enemy };

struct Enemy {
  int x, y;
  char symbol;
  int hp;
  EnemyType type;
};

struct Bullet {
  int x, y;
  Direction dir;
  Owner owner;
  char symbol;
};

struct CombatStats {
  int playerDamage = 3;
  int meleeEnemyDamage = 8;
  int archerEnemyDamage = 5;
};
// Global game state. Declared here, defined once in a matching .cpp.
extern int playerX;
extern int playerY;
extern int playerHealth;
extern int playerMaxHealth;
extern Direction facing;
extern std::vector<Enemy> enemies;
extern std::vector<Bullet> bullets;
extern CombatStats stats;
