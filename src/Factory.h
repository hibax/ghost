#pragma once

#include <vector>
#include "Entity.h"
#include "Troop.h"

class Factory : public Entity {

public:
    Factory(int id, OWNER owner, int cyborgs, int production);

    void setMyTroops(const std::vector<Troop> &myTroops);
    void setOpTroops(const std::vector<Troop> &opTroops);
    void addTroop(OWNER owner, Troop troop);
    int getProduction() const;
    int getCyborgs() const;
    const std::vector<Troop> &getMyTroops() const;
    const std::vector<Troop> &getOpTroops() const;

    std::string toString();

private:
    int production;
    int cyborgs;
    std::vector<Troop> myTroops;
    std::vector<Troop> opTroops;
};
