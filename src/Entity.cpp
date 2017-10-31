
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
