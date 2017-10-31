
#include "GameState.h"

GameState::GameState(int round, std::vector<Factory> &factories) :
        factories(factories), round(round) {
}

int GameState::getRound() const {
    return round;
}

const std::vector<Factory> &GameState::getFactories() const {
    return factories;
}
