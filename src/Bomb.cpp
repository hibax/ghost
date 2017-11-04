
#include "Bomb.h"

Bomb::Bomb(int id, OWNER owner, int from, int to, int turnsToArrive) :
        Entity(id, owner), from(from), to(to), turnsToArrive(turnsToArrive) {

}

int Bomb::getFrom() const {
    return from;
}

int Bomb::getTo() const {
    return to;
}

int Bomb::getTurnsToArrive() const {
    return turnsToArrive;
}

void Bomb::setTurnsToArrive(int turnsToArrive) {
    Bomb::turnsToArrive = turnsToArrive;
}
