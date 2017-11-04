#pragma once

#include "Factory.h"
#include "Action.h"

class GameState {

public:
    GameState(int round, std::vector<Factory> &factories);
    std::string computeActions();
    int getRound() const;

    const std::vector<Factory> &getFactories() const;
    std::string computeOutput(std::vector<Action> &possibleActions, Factory &sourceFactory);


private:
    void performAction(Action &action);
    std::string adaptOutput(std::string &output) const;

    const int round;
    std::vector<Factory> factories;
};
