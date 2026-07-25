#pragma once
#include <vector>

enum Direction { UP, DOWN, LEFT, RIGHT };
enum EnemyType { MELEE, ARCHER };
enum Owner { PLAYER, ENEMY };

struct Enemy {
  int x, y;
  char symbol;
  bool alive;
  int hp;
  EnemyType type;
};

struct Bullet {
  int x, y;
  Direction dir;
  Owner owner;
  char symbol;
};
// Global game state. Declared here, defined once in a matching .cpp.
extern int playerX;
extern int playerY;
extern int playerHealth;
extern Direction facing;
extern std::vector<Enemy> enemies;
extern std::vector<Bullet> bullets;
