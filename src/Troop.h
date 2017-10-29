
#ifndef GHOSTINTHECELL_TROOP_H
#define GHOSTINTHECELL_TROOP_H


#include "Entity.h"

class Troop : public Entity {
public:
    Troop(int id, OWNER owner, int turnsToArrive);

private:
    int turnsToArrive;
};


#endif //GHOSTINTHECELL_TROOP_H
