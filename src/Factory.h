#pragma once

#include <vector>
#include "Entity.h"
#include "Troop.h"
#include "Action.h"

class Factory : public Entity {

public:
    Factory(int id, OWNER owner, int cyborgs, int production);

    void setMyTroops(const std::vector<Troop> &myTroops);
    void setOpTroops(const std::vector<Troop> &opTroops);
    void addTroop(Troop troop);
    int getProduction() const;
    int getCyborgs() const;
    const std::vector<Troop> &getMyTroops() const;
    const std::vector<Troop> &getOpTroops() const;

    int computeBattle(int turn) const;
    std::vector<Action> computePossibleActions(const std::vector<Factory> &factories) const;

    std::string toString();

private:
    int production;
    int cyborgs;
    std::vector<Troop> myTroops;
    std::vector<Troop> opTroops;
    int fightCoef(OWNER factoryOwner, OWNER troopOwner) const;
    Action generateActionAndComputeScore(const Factory &destinationFactory, int availableTroops) const;
    int countAvailableTroops(int turns) const;
};
