#pragma once

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

