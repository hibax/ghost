
#ifndef GHOSTINTHECELL_GAMESTATE_H
#define GHOSTINTHECELL_GAMESTATE_H


#include "Factory.h"

class GameState {

public:
    GameState(int factoryCount, int linkCount);

private:
    const int factoryCount;
    const int linkCount;
    int round;
    std::vector<Factory> factories;

};


#endif //GHOSTINTHECELL_GAMESTATE_H
