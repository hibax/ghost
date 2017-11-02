#include <sstream>
#include <cmath>
#include "Factory.h"
#include "Writer.h"

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

    for (const Factory &destinationFactory : factories) {

        // Generate action with score
        const Action action = generateActionAndComputeScore(destinationFactory);

        // Avoid bad moves
        if (action.getScore() >= 0 && action.isValid()) {
            possibleActions.emplace_back(action);
        }
    }

    return possibleActions;
}


/*
 * Need rework
 * TODO : implement pow
 */
Action Factory::generateActionAndComputeScore(const Factory &destinationFactory) const {

    int availableTroopsForAttack = cyborgs;

    int neededTroopsForDefense = 0;

    for (int i = 1; i < 6; ++i) {
        int tmpAvailableTroopsForAttack = computeBattle(i);

        if (tmpAvailableTroopsForAttack < availableTroopsForAttack) {
            availableTroopsForAttack = tmpAvailableTroopsForAttack;
        }
    }

    //Writer::debug("[Factory " + std::to_string(id) + "]  Available troops for attack : " + std::to_string(availableTroopsForAttack));

    if (availableTroopsForAttack <= 0) {
        return Action(0, ACTION_TYPE::MOVE, id, destinationFactory.getId(), 0);
    }

    int turnsToGetToDestination = globals::factoryDirectDistances[id][destinationFactory.getId()] + 1;

    int neededTroopsForAttack = 0;
    if (destinationFactory.getOwner() == OPPONENT) {
        neededTroopsForAttack = (-1) * destinationFactory.computeBattle(turnsToGetToDestination);
    }
    else {
        neededTroopsForAttack = (-1) * destinationFactory.computeBattle(turnsToGetToDestination);
    }


    float score = 0.000001 + destinationFactory.getProduction();
    score /= std::pow(turnsToGetToDestination, 2);

    if (neededTroopsForAttack > 0) {
        score /= neededTroopsForAttack;
    }
    else {
        neededTroopsForAttack = 0;
        score = 0;
    }

    if (destinationFactory.getOwner() == OWNER::NEUTRAL) {
        score *= 3;
    }
    else if (destinationFactory.getOwner() == OWNER::OPPONENT) {
        score *= 2;
    }

    int troopsToSend;
    if (neededTroopsForAttack > availableTroopsForAttack) {
        troopsToSend = availableTroopsForAttack;
    }
    else {
        troopsToSend = neededTroopsForAttack;
    }

    return Action(score, ACTION_TYPE::MOVE, id, destinationFactory.getId(), troopsToSend);
}
