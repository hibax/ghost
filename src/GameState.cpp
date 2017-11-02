
#include <functional>
#include <cmath>
#include "GameState.h"
#include "Utils.h"
#include "Writer.h"

GameState::GameState(int round, std::vector<Factory> &factories) :
        factories(factories), round(round) {
}

int GameState::getRound() const {
    return round;
}

const std::vector<Factory> &GameState::getFactories() const {
    return factories;
}

std::string GameState::computeActions() const {
    std::string output;

    // Compute actions for each factory
    for (const Factory &sourceFactory : factories) {

        // Generate actions only for my factories. Could be improved by predicting opponent actions
        if (sourceFactory.getOwner() == OWNER::ME) {

            // Check all possible actions
            std::vector<Action> possibleActions = sourceFactory.computePossibleActions(factories);
            Utils::sortActions(possibleActions);

            for (Action action : possibleActions) {
                if (action.getScore() > 0){
                    Writer::debug(action.toString());
                }
            }

            if (!output.empty()) {
                output += ";";
            }

            output += Writer::actionsOutput(possibleActions);
        }
    }

    return output;
}

