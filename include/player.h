#pragma once

void movePlayer(char input);
void fireArrow(); // ranged: spawns a bullet traveling in the facing direction
void regenerateHealth();
void fullHeal();
void upgradeHealth();
bool buy(int &gold, int cost);
void explosion(int radius, int damage);
