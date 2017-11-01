
#ifndef GHOSTINTHECELL_GAMESTATE_H
#define GHOSTINTHECELL_GAMESTATE_H


#include "Factory.h"
#include "Action.h"

class GameState {

public:
    GameState(int round, std::vector<Factory> &factories);
    std::vector<Action> computeActions() const;
    Action generateActionAndComputeScore(const Factory &sourceFactory, const Factory &destinationFactory) const;

private:
    const int round;
public:
    int getRound() const;

    const std::vector<Factory> &getFactories() const;

private:
    const std::vector<Factory> factories;

};


#endif //GHOSTINTHECELL_GAMESTATE_H
