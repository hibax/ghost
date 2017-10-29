#include "Factory.h"

Factory::Factory(int id, OWNER owner, int production, int cyborgs) : Entity(id, owner){
    this->production = production;
    this->cyborgs = cyborgs;
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
