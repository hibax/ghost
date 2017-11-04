#pragma once


#include "Bomb.h"

namespace  globals {
    extern int bombsCount;
    extern int factoryCount;
    extern int linkCount;
    extern int factoryDirectDistances[15][15];
    extern int shortestPath[15][15];
    extern int shortestDistance[15][15];
    extern double factoryDanger[15];
    extern std::vector<Bomb> opponentBombs;
}
