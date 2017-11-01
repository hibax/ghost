
#ifndef GHOSTINTHECELL_ENTITY_H
#define GHOSTINTHECELL_ENTITY_H


#include <string>
#include "Globals.h"

class Entity {
public:
    Entity(int id, OWNER owner);


public:
    int getId() const;
    OWNER getOwner() const;

    virtual std::string toString();

protected:
    int id;
    OWNER owner;
};


#endif //GHOSTINTHECELL_ENTITY_H
