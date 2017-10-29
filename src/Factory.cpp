#include "Factory.h"

Factory::Factory(int id, OWNER owner, int production, int cyborgs) : Entity(id, owner){
    this->production = production;
    this->cyborgs = cyborgs;
}
