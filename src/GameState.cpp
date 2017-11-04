
#include <functional>
#include <cmath>
#include "GameState.h"
#include "Utils.h"
#include "Writer.h"
#include "Globals.h"

GameState::GameState(int round, std::vector<Factory> &factories) :
        factories(factories), round(round) {
}

int GameState::getRound() const {
    return round;
}

const std::vector<Factory> &GameState::getFactories() const {
    return factories;
}

std::string GameState::computeActions() {
    std::string output;

    // Compute actions for each factory
    for (Factory &sourceFactory : factories) {

        // Generate actions only for my factories. Could be improved by predicting opponent actions
        if (sourceFactory.getOwner() == OWNER::ME) {

            // Count not needed troops for the next 5 turns. (5 is arbitrary)
            int availableTroops = sourceFactory.countAvailableTroops(5);
            sourceFactory.setAvailableTroops(availableTroops);

            // Check all possible actions
            std::vector<Action> possibleActions = sourceFactory.computePossibleActions(factories, round);
            Utils::sortActions(possibleActions);

            // Perform best actions
            output += computeOutput(possibleActions, sourceFactory);
        }
    }

    return adaptOutput(output);
}

void GameState::performAction(Action &action) {

    Factory *destinationFactory = nullptr;
    Factory *sourceFactory = nullptr;

    for (Factory &factory : factories) {
        if (factory.getId() == action.getSourceId()) {
            sourceFactory = &factory;
        }
        if (factory.getId() == action.getDestinationId()) {
            destinationFactory = &factory;
        }
    }
    if (destinationFactory != nullptr && sourceFactory != nullptr) {

        int nextAvailableTroops = sourceFactory->getAvailableTroops() - action.getCyborgCount();

        if (nextAvailableTroops < 0) {
            nextAvailableTroops = 0;
            action.setCyborgCount(sourceFactory->getAvailableTroops());
        }

        sourceFactory->setAvailableTroops(nextAvailableTroops);

        destinationFactory->addTroop(
                Troop(0,
                      sourceFactory->getOwner(),
                      action.getSourceId(),
                      action.getDestinationId(),
                      action.getCyborgCount(),
                      globals::factoryDirectDistances[action.getSourceId()][action.getDestinationId()] + 1));

        Writer::debug(action.toString());
    }

}

std::string GameState::computeOutput(std::vector<Action> &possibleActions, Factory &sourceFactory) {
    std::string output;

    for (Action &action : possibleActions) {
        if (action.getScore() > 0){

            if (action.getActionType() == BOMB && globals::bombsCount > 0) {

                performAction(action);
                output += Writer::actionsOutput(action);
                globals::bombsCount -= 1;
            }
            else if (action.getActionType() == MOVE) {

                performAction(action);

                if (action.getCyborgCount() > 0) {
                    output += Writer::actionsOutput(action);
                }
            }

            if (sourceFactory.getAvailableTroops() == 0) {
                break;
            }
        }
    }
    return output;
}

std::string GameState::adaptOutput(std::string &output) const {

    if (output.empty()) {
        output = "WAIT;";
    }
    output.pop_back();

    return output;
}


