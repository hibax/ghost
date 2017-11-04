
#include <sstream>
#include "Entity.h"

Entity::Entity(int id, OWNER owner) {
    this->id = id;
    this->owner = owner;
}

int Entity::getId() const {
    return id;
}

OWNER Entity::getOwner() const {
    return owner;
}

std::string Entity::toString() {
    std::stringstream ss;
    ss << "Entity " << id << " " << owner;
    return ss.str();
}


OWNER argToOwner(int arg) {
    switch (arg) {
        case 1:
            return ME;
        case -1:
            return OPPONENT;
        default:
            return NEUTRAL;
    }
}