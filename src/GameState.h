#pragma once

#include "Factory.h"
#include "Action.h"

class GameState {

public:
    GameState(int round, std::vector<Factory> &factories);
    std::string computeActions() const;

private:
    const int round;
public:
    int getRound() const;

    const std::vector<Factory> &getFactories() const;

private:
    const std::vector<Factory> factories;

};
