
#ifndef GHOSTINTHECELL_TROOP_H
#define GHOSTINTHECELL_TROOP_H


#include "Entity.h"

class Troop : public Entity {
public:
    Troop(int id, OWNER owner, int from, int to, int cyborgs, int turnsToArrive);

public:
    int getFrom() const;

    int getTo() const;

    int getCyborgs() const;

    int getTurnsToArrive() const;

private:
    int from;
    int to;
    int cyborgs;
    int turnsToArrive;
};


#endif //GHOSTINTHECELL_TROOP_H
