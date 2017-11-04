#pragma once

#include "Entity.h"

class Bomb : public Entity {
public:
    int getFrom() const;

    int getTo() const;

    int getTurnsToArrive() const;

    Bomb(int id, OWNER owner, int from, int to, int turnsToArrive);

    void setTurnsToArrive(int turnsToArrive);

private:
    int from;
    int to;
    int turnsToArrive;
};


