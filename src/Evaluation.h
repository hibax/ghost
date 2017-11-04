
#ifndef GHOSTINTHECELL_EVALUATION_H
#define GHOSTINTHECELL_EVALUATION_H


#include "Factory.h"

class Evaluation {

public:
    static double computeScore(const Factory &destinationFactory, int turnsToArrive, int neededTroops);
    static int
    computeTroopsToSend(int neededTroops, int availableTroops, ACTION_TYPE actionType, OWNER destinationOwner);

private:
    Evaluation() = default;
};


#endif //GHOSTINTHECELL_EVALUATION_H
