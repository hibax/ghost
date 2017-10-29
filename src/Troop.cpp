
#include "Troop.h"

Troop::Troop(int id, OWNER owner, int turnsToArrive) : Entity(id, owner){
    this->turnsToArrive = turnsToArrive;
}
