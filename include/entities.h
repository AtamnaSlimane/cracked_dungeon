#pragma once
#include <chrono>
#include <vector>

enum class Direction { Up, Down, Left, Right };
enum class EnemyType { Melee, Archer, Boss };
enum class Owner { Player, Enemy };

struct Enemy {
  int x, y;
  char symbol;
  int hp;
  int goldReward;
  EnemyType type;
};

struct Bullet {
  int x, y;
  Direction dir;
  Owner owner;
  char symbol;
};
struct Cost {
  int damage = 40;
  int maxHealth = 80;
  int healSpeed = 20;
  int fireSpeed = 30;
  int moveSpeed = 30;
  int bomb = 30;
  int bomb_radius = 30;
  int bomb_damage = 30;
};

struct CombatStats {
  int playerDamage = 3;
  int meleeEnemyDamage = 8;
  int archerEnemyDamage = 5;
  int bossMeleeEnemyDamage = 20;
  int playerHealInterval = 500;
  int playershootInterval = 250;
  int playermovementInterval = 50;
};

// Global game state. Declared here, defined once in a matching .cpp.
extern int playerX;
extern int playerY;
extern int playerHealth;
extern int playerMaxHealth;
extern int bombs;
extern Direction facing;
