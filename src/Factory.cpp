#include <sstream>
#include <cmath>
#include "Factory.h"
#include "Writer.h"
#include "Evaluation.h"

Factory::Factory(int id, OWNER owner, int cyborgs, int production) :
        Entity(id, owner), cyborgs(cyborgs), production(production){
}

int Factory::getProduction() const {
    return production;
}

int Factory::getCyborgs() const {
    return cyborgs;
}

const std::vector<Troop> &Factory::getMyTroops() const {
    return myTroops;
}

const std::vector<Troop> &Factory::getOpTroops() const {
    return opTroops;
}

void Factory::setMyTroops(const std::vector<Troop> &myTroops) {
    Factory::myTroops = myTroops;
}

void Factory::setOpTroops(const std::vector<Troop> &opTroops) {
    Factory::opTroops = opTroops;
}

void Factory::addTroop(Troop troop) {
    if (OWNER::ME == troop.getOwner()) {
        myTroops.push_back(troop);
    } else {
        opTroops.push_back(troop);
    }
}

std::string Factory::toString() {
    std::stringstream ss;
    ss << "[Factory]" << " id " << id
       << " owner " << owner << " cyborgs " << cyborgs
       << " production " << production;
    return ss.str();
}

int Factory::computeBattle(const int turn) const {
    int battleResult = 0;

    battleResult = cyborgs;

    OWNER tmpOwner = owner;
    for (int i = 1; i <= turn; ++i) {

        if (tmpOwner != NEUTRAL) {
            battleResult += production;
        }

        int incomingTroopsAtThisTurn = 0;
        for (const Troop &opTroop : opTroops) {
            if (opTroop.getTurnsToArrive() == i) {
                incomingTroopsAtThisTurn -= opTroop.getCyborgs();
            }
        }
        for (const Troop &myTroop : myTroops) {
            if (myTroop.getTurnsToArrive() == i) {
                incomingTroopsAtThisTurn += myTroop.getCyborgs();
            }
        }

        if (incomingTroopsAtThisTurn != 0) {

            OWNER incomingTroopOwner;
            if (incomingTroopsAtThisTurn >= 0) {
                incomingTroopOwner = ME;
            }
            else {
                incomingTroopOwner = OPPONENT;
                incomingTroopsAtThisTurn *= (-1);
            }

            battleResult += fightCoef(tmpOwner, incomingTroopOwner) * incomingTroopsAtThisTurn;

            if (battleResult < 0) {
                // Owner switch
                tmpOwner = incomingTroopOwner;
                battleResult *= -1;
            }
            else {
                // Same owner
            }
        }
    }

    // This is to be sure to not let the opponent keep the factory with 0 troop
    // And Neutral need 1 unit as result to take it
    if (tmpOwner != OWNER::ME) {
        battleResult += 1;

        return (-1) * battleResult;
    }

    return battleResult;
}

int Factory::fightCoef(OWNER factoryOwner, OWNER troopOwner) const {
    if (factoryOwner == troopOwner) {
        return 1;
    }
    return -1;
}

std::vector<Action> Factory::computePossibleActions(const std::vector<Factory> &factories) const {

    std::vector<Action> possibleActions;

    // Count not needed troops for the next 5 turns. (5 is arbitrary)
    int availableTroops = countAvailableTroops(5);

    if (availableTroops > 0) {

        for (const Factory &destinationFactory : factories) {

            // Generate action with score
            const Action action = generateActionAndComputeScore(destinationFactory, availableTroops);

            // Avoid bad moves
            if (action.getScore() >= 0 && action.isValid()) {
                possibleActions.emplace_back(action);
            }
        }
    }

    return possibleActions;
}


/*
 * Need rework
 * TODO : implement pow
 */
Action Factory::generateActionAndComputeScore(const Factory &destinationFactory, int availableTroops) const {

    int turnsToGetToDestination = globals::factoryDirectDistances[id][destinationFactory.getId()] + 1;

    int neededTroops = (-1) * destinationFactory.computeBattle(turnsToGetToDestination);

    float score = Evaluation::computeScore(destinationFactory, turnsToGetToDestination, neededTroops);

    int troopsToSend = Evaluation::computeTroopsToSend(neededTroops, availableTroops, ACTION_TYPE::MOVE);

    return Action(score, ACTION_TYPE::MOVE, id, destinationFactory.getId(), troopsToSend);
}

// count how many troops are available (= not needed for defense) for the next X turns (taking into account the production)
int Factory::countAvailableTroops(int turns) const {
    int availableTroopsForAttack = cyborgs;

    for (int i = 1; i <= turns; ++i) {
        int tmpAvailableTroopsForAttack = computeBattle(i);

        if (tmpAvailableTroopsForAttack < availableTroopsForAttack) {
            availableTroopsForAttack = tmpAvailableTroopsForAttack;
        }
    }

    Writer::debug("[Factory " + std::to_string(id) + "]  Available troops for attack : " + std::to_string(availableTroopsForAttack));

    return availableTroopsForAttack;
}
