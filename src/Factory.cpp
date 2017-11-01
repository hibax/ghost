#include <sstream>
#include "Factory.h"

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

void Factory::addTroop(OWNER owner, Troop troop) {
    if (OWNER::ME == owner) {
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
