#ifndef GHOSTINTHECELL_FACTORY_H
#define GHOSTINTHECELL_FACTORY_H

#include <vector>
#include "Entity.h"
#include "Troop.h"

class Factory : public Entity {

public:
    Factory(int id, OWNER owner, int production, int cyborgs);

private:
    int production;
    int cyborgs;
    std::vector<Troop> myTroops;
    std::vector<Troop> opTroops;
public:
    int getProduction() const;

    int getCyborgs() const;

    const std::vector<Troop> &getMyTroops() const;

    const std::vector<Troop> &getOpTroops() const;
};


#endif //GHOSTINTHECELL_FACTORY_H
