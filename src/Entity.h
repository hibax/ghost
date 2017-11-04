#pragma once

#include <string>

enum OWNER {ME, OPPONENT, NEUTRAL};
extern OWNER argToOwner(int arg);

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


