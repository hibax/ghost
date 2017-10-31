
#include "Troop.h"


Troop::Troop(int id, OWNER owner, int from, int to, int cyborgs, int turnsToArrive) :
        Entity(id, owner), from(from), to(to), cyborgs(cyborgs), turnsToArrive(turnsToArrive) {
}

int Troop::getFrom() const {
    return from;
}

int Troop::getTo() const {
    return to;
}

int Troop::getCyborgs() const {
    return cyborgs;
}

int Troop::getTurnsToArrive() const {
    return turnsToArrive;
}
