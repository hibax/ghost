#pragma once

#include "GameState.h"

class Parser {
public:
    static void initGame();
    static void initGameIDE(int factoryCount, int linkCount, std::vector <std::tuple <int, int, int> > &factoryDirectDistances);
    static GameState initRound(int round);
    static GameState initRoundIDE(int round, std::vector <std::tuple <int, std::string, int, int, int, int, int> > &entities);

private:
    Parser() = default;
    static void fillFactories(std::vector<Factory> &factories, int entityId, const std::string &entityType, int arg1, int arg2, int arg3,
                              int arg4, int arg5);
};
