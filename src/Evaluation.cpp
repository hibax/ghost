
#include <cmath>
#include "Evaluation.h"

float Evaluation::computeScore(const Factory &destinationFactory, int turnsToArrive, int neededTroops) {

float score = 0.000001 + destinationFactory.getProduction();
    score /= std::pow(turnsToArrive, 2);

    if (neededTroops > 0) {
        score /= neededTroops;
    }
    else {
        neededTroops = 0;
        score = 0;
    }

    if (destinationFactory.getOwner() == OWNER::NEUTRAL) {
        score *= 3;
    }
    else if (destinationFactory.getOwner() == OWNER::OPPONENT) {
        score *= 2;
    }

    return score;
}

// If attacking an enemy, should we send more troops (just in case) ?
int Evaluation::computeTroopsToSend(int neededTroops, int availableTroops, ACTION_TYPE actionType) {

    int troopsToSend;
    if (neededTroops > availableTroops) {
        troopsToSend = availableTroops;
    }
    else {
        troopsToSend = neededTroops;
    }

    return troopsToSend;
}
