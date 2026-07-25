#pragma once
#include <vector>

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Enemy {
  int x, y;
  char symbol;
  bool alive;
  int hp;
};

struct Bullet {
  int x, y;
  Direction dir;
  bool on;
  char symbol;
};

// Global game state. Declared here, defined once in a matching .cpp.
extern int playerX;
extern int playerY;
extern int playerHealth;
extern Direction facing;
extern Bullet bullet;
extern std::vector<Enemy> enemies;
