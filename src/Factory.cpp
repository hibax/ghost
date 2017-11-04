#include <sstream>
#include <cmath>
#include "Factory.h"
#include "Writer.h"
#include "Evaluation.h"
#include "Globals.h"

Factory::Factory(int id, OWNER owner, int cyborgs, int production) :
        Factory(id, owner, cyborgs, production, 0){
}
Factory::Factory(int id, OWNER owner, int cyborgs, int production, int disabled) :
        Entity(id, owner), cyborgs(cyborgs), production(production), availableTroops(cyborgs), disabled(disabled){
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

void Factory::addTroop(const Troop &troop) {
    if (OWNER::ME == troop.getOwner()) {
        myTroops.push_back(troop);
    } else {
        opTroops.push_back(troop);
    }
}

void Factory::addBomb(const Bomb &bomb) {
    if (OWNER::ME == bomb.getOwner()) {
        myBombs.push_back(bomb);
    } else {
        opBombs.push_back(bomb);
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
    return Factory::computeBattle(turn, false);
}
int Factory::computeBattle(const int turn, bool isLookingForAvailableTroops) const {
    int battleResult = 0;
    int bombCounter = disabled;
    battleResult = cyborgs;

    OWNER tmpOwner = owner;
    for (int i = 1; i <= turn; ++i) {

        if (tmpOwner != NEUTRAL) {
            if (bombCounter == 0) {
                battleResult += production;
            }
        }
        if (bombCounter > 0) {
            bombCounter -= 1;
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

        for (const Bomb &opBomb : opBombs) {
            if (opBomb.getTurnsToArrive() == i) {

                if (isLookingForAvailableTroops) {
                    return cyborgs;
                }

                bombCounter = 5;
                if (battleResult >= 0) {

                    if (battleResult <= 10) {
                        battleResult = 0;
                    }
                    else if (battleResult <= 20) {
                        battleResult -= 10;
                    }
                    else {
                        battleResult /= 2;
                    }
                }
                else {
                    if (battleResult >= -10) {
                        battleResult = 0;
                    }
                    else if (battleResult >= -20) {
                        battleResult += 10;
                    }
                    else {
                        battleResult /= 2;
                    }
                }
            }
        }


        for (const Bomb &myBomb : myBombs) {
            if (myBomb.getTurnsToArrive() == i) {

                if (isLookingForAvailableTroops) {
                    return cyborgs;
                }

                bombCounter = 5;
                if (battleResult >= 0) {

                    if (battleResult <= 10) {
                        battleResult = 0;
                    }
                    else if (battleResult <= 20) {
                        battleResult -= 10;
                    }
                    else {
                        battleResult /= 2;
                    }
                }
                else {
                    if (battleResult >= -10) {
                        battleResult = 0;
                    }
                    else if (battleResult >= -20) {
                        battleResult += 10;
                    }
                    else {
                        battleResult /= 2;
                    }
                }
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

std::vector<Action> Factory::computePossibleActions(const std::vector<Factory> &factories, const int round) const {

    std::vector<Action> possibleActions;


    for (const Factory &destinationFactory : factories) {

        if (availableTroops > 0) {

            // Generate move action with score
            const Action moveAction = generateMoveAction(destinationFactory, availableTroops, round);

            // Avoid bad moves
            if (moveAction.getScore() > 0 && moveAction.isValid()) {
                possibleActions.emplace_back(moveAction);
            }
        }

        // Generate bomb action with score
        const Action bombAction = generateBombAction(destinationFactory);

        if (bombAction.getScore() > 0) {
            possibleActions.emplace_back(bombAction);
        }
    }

    return possibleActions;
}


/*
 * Need rework
 * TODO : implement pow
 */
Action Factory::generateMoveAction(const Factory &destinationFactory, int availableTroops, const int round) const {

    int turnsToGetToDestination = globals::factoryDirectDistances[id][destinationFactory.getId()] + 1;

    int neededTroops = computeNeededTroops(destinationFactory, turnsToGetToDestination);

    double score = Evaluation::computeScore(destinationFactory, turnsToGetToDestination, neededTroops);

    Writer::debug("[Factory " + std::to_string(id)
                  + "] Needed troops for Factory " + std::to_string(destinationFactory.getId())
                  + " : " + std::to_string(neededTroops) + " with score : " + std::to_string(score));

    int troopsToSend = Evaluation::computeTroopsToSend(neededTroops, availableTroops, ACTION_TYPE::MOVE, destinationFactory.getOwner());

    int destinationId;
    if (round == 0) {
        destinationId = destinationFactory.getId();
    }
    else {
        destinationId = globals::shortestPath[id][destinationFactory.getId()];
    }

    return Action(score, ACTION_TYPE::MOVE, id, destinationId, troopsToSend);
}

// count how many troops are available (= not needed for defense) for the next X turns (taking into account the production)
int Factory::countAvailableTroops(int turns) const {
    int availableTroopsForAttack = cyborgs;

    for (int i = 1; i <= turns; ++i) {
        int tmpAvailableTroopsForAttack = computeBattle(i, true);

        if (tmpAvailableTroopsForAttack < availableTroopsForAttack) {
            availableTroopsForAttack = tmpAvailableTroopsForAttack;
        }
    }

    Writer::debug("[Factory " + std::to_string(id) + "] Available troops : " + std::to_string(availableTroopsForAttack));

    return availableTroopsForAttack;
}

void Factory::setProduction(int production) {
    Factory::production = production;
}

void Factory::setCyborgs(int cyborgs) {
    Factory::cyborgs = cyborgs;
}

void Factory::setAvailableTroops(int availableTroops) {
    Factory::availableTroops = availableTroops;
}

int Factory::getAvailableTroops() const {
    return availableTroops;
}

int Factory::predictNeededTroops(int turnA, int turnB, const Factory &factory) const {
    int neededTroops = 0;

    if (id != factory.getId()) {

        for (int i = turnA; i <= turnB; ++i) {
            int tmpNeededTroops = (-1) * factory.computeBattle(i);

            if (tmpNeededTroops > neededTroops) {
                neededTroops = tmpNeededTroops;
            }
        }

        //Writer::debug("[Factory " + std::to_string(id) + "] Friendly factory : " + std::to_string(factory.id) + " is needing " + std::to_string(neededTroops) + " troops");
    }

    return neededTroops;
}

Action Factory::generateBombAction(const Factory &destinationFactory) const {

    double score;
    int turnsToGetThere = globals::factoryDirectDistances[id][destinationFactory.getId()] + 1;

    if (destinationFactory.getOwner() == OPPONENT
        && destinationFactory.getMyBombs().empty()
        && destinationFactory.computeBattle(turnsToGetThere)) {

        score = 1.0 * std::pow(destinationFactory.getProduction(), 3)/turnsToGetThere;
    }
    else {
        score = 0;
    }

    return Action(score, BOMB, id, destinationFactory.getId(), 0);
}

const std::vector<Bomb> &Factory::getMyBombs() const {
    return myBombs;
}

std::vector<Bomb> & Factory::getOpBombs() {
    return opBombs;
}

void Factory::setDisabled(int disabled) {
    Factory::disabled = disabled;
}

int Factory::getDisabled() const {
    return disabled;
}

int Factory::computeNeededTroops(const Factory &destinationFactory, const int turnsToGetToDestination) const {
    int neededTroops = 0;

    if (destinationFactory.getOwner() == ME) {
        neededTroops = predictNeededTroops(turnsToGetToDestination, turnsToGetToDestination + 5, destinationFactory);
    }
    else if (destinationFactory.getOwner() == NEUTRAL ){
        neededTroops = (-1) * destinationFactory.computeBattle(turnsToGetToDestination);
    }
    else {
        neededTroops = (-1) * destinationFactory.computeBattle(turnsToGetToDestination);
    }

    return neededTroops;
}
