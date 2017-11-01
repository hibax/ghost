
#include <functional>
#include <cmath>
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

std::vector<Action> GameState::computeActions() const {
    std::vector<Action> actions;

    // Compute actions for each factory
    for (const Factory &sourceFactory : factories) {

        // Generate actions only for my factories. Could be improved by predicting opponent actions
        if (sourceFactory.getOwner() == OWNER::ME) {

            // Check all possible actions
            for (const Factory &destinationFactory : factories) {

                // Generate action with score
                const Action action = generateActionAndComputeScore(sourceFactory, destinationFactory);

                // Avoid bad moves
                if (action.getScore() >= 0 && action.isValid()) {
                    actions.emplace_back(action);
                }
            }
        }
    }

    return actions;
}

/*
 * Need rework
 * TODO : implement pow
 */
Action GameState::generateActionAndComputeScore(const Factory &sourceFactory, const Factory &destinationFactory) const {

    float score = destinationFactory.getProduction();
    score /= std::pow(globals::factoryDirectDistances[destinationFactory.getId()][sourceFactory.getId()], 2);
    score *= sourceFactory.getCyborgs();
    score /= 1 + (destinationFactory.getCyborgs()/5.);


    if (destinationFactory.getOwner() == OWNER::NEUTRAL) {
        score *= 3;
    }
    else if (destinationFactory.getOwner() == OWNER::OPPONENT) {
        score *= 2;
        if (sourceFactory.getCyborgs() <= destinationFactory.getCyborgs()) {
            score *= 0;
        }
    }
    else {
        score *= 0;
    }

    return Action(score, ACTION_TYPE::MOVE, sourceFactory.getId(), destinationFactory.getId(), sourceFactory.getCyborgs());
}
