
#ifndef GHOSTINTHECELL_ENTITY_H
#define GHOSTINTHECELL_ENTITY_H


#include "Globals.h"

class Entity {
public:
    Entity(int id, OWNER owner);


private:
    int id;
public:
    int getId() const;

    OWNER getOwner() const;

private:
    OWNER owner;
};


#endif //GHOSTINTHECELL_ENTITY_H
