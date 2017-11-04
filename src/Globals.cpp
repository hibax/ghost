
#include <vector>
#include "Globals.h"

int globals::bombsCount = 2;
int globals::factoryCount = 0;
int globals::linkCount = 0;
int globals::factoryDirectDistances[15][15] = { { 0 } };
int globals::shortestPath[15][15] = { { 0 } };
int globals::shortestDistance[15][15] = { { 0 } };
std::vector<Bomb> globals::opponentBombs;
double globals::factoryDanger[15] = { 0 };
