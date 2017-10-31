
#include <iostream>
#include "Parser.h"
#include "Globals.h"

void Parser::initGame() {
    int factoryCount; // the number of factories
    std::cin >> factoryCount; std::cin.ignore();
    globals::factoryCount = factoryCount;

    int linkCount; // the number of links between factories
    std::cin >> linkCount; std::cin.ignore();
    globals::linkCount = linkCount;


    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        std::cin >> factory1 >> factory2 >> distance; std::cin.ignore();

        globals::factoryDirectDistances[factory1][factory2] = distance;
        globals::factoryDirectDistances[factory2][factory1] = distance;

    }
}

GameState Parser::initRound() {
    return GameState(0, 0);
}

void Parser::initGameIDE(int factoryCount, int linkCount, std::vector <std::tuple <int, int, int> > &factoryDirectDistances) {
    globals::factoryCount = factoryCount;
    globals::linkCount = linkCount;

    for (std::tuple <int, int, int> &factoryDirectDistance : factoryDirectDistances) {
        int &factory1 = std::get<0>(factoryDirectDistance);
        int &factory2 = std::get<1>(factoryDirectDistance);
        int &distance = std::get<2>(factoryDirectDistance);

        globals::factoryDirectDistances[factory1][factory2] = distance;
        globals::factoryDirectDistances[factory2][factory1] = distance;
    }
}
