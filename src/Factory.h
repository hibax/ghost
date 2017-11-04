#pragma once

#include <vector>
#include "Entity.h"
#include "Troop.h"
#include "Action.h"
#include "Bomb.h"

class Factory : public Entity {

public:
    Factory(int id, OWNER owner, int cyborgs, int production);
    Factory(int id, OWNER owner, int cyborgs, int production, int disabled);

    void setMyTroops(const std::vector<Troop> &myTroops);
    void setOpTroops(const std::vector<Troop> &opTroops);
    void addTroop(const Troop &troop);
    void addBomb(const Bomb &bomb);
    int getProduction() const;
    int getCyborgs() const;
    const std::vector<Troop> &getMyTroops() const;
    const std::vector<Troop> &getOpTroops() const;
    void setProduction(int production);
    void setCyborgs(int cyborgs);
    void setAvailableTroops(int availableTroops);
    int getAvailableTroops() const;
    const std::vector<Bomb> &getMyBombs() const;
    std::vector<Bomb> & getOpBombs();
    int getDisabled() const;
    void setDisabled(int value);

    int computeBattle(int turn) const;
    int computeBattle(int turn, bool isLookingForAvailableTroops) const;
    std::vector<Action> computePossibleActions(const std::vector<Factory> &factories) const;
    int countAvailableTroops(int turns) const;
    int predictNeededTroops(int turnA, int turnB, const Factory &factory) const;

    std::string toString();

private:
    int production;
    int disabled;
    int cyborgs;
    int availableTroops;
    std::vector<Troop> myTroops;
    std::vector<Troop> opTroops;
    std::vector<Bomb> myBombs;
    std::vector<Bomb> opBombs;

    int fightCoef(OWNER factoryOwner, OWNER troopOwner) const;
    Action generateMoveAction(const Factory &destinationFactory, int availableTroops) const;
    Action generateBombAction(const Factory &destinationFactory) const;
    int computeNeededTroops(const Factory &destinationFactory, const int turnsToGetToDestination) const;
};
