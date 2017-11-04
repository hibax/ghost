
#include <cmath>
#include "Evaluation.h"

double Evaluation::computeScore(const Factory &destinationFactory, int turnsToArrive, int neededTroops) {

    double score = 0.000001 + destinationFactory.getProduction();
    score /= std::pow(turnsToArrive, 2);

    if (neededTroops > 0) {
        score /= neededTroops;
    }
    else {
        neededTroops = 0;
        score = 0;
    }

    if (destinationFactory.getOwner() == OWNER::ME) {
        score *= 2;
    }
    else if (destinationFactory.getOwner() != OWNER::ME) {
        score *= 1;
    }

    return score;
}

// If attacking an enemy, should we send more troops (just in case) ?
int Evaluation::computeTroopsToSend(int neededTroops, int availableTroops, ACTION_TYPE actionType, OWNER destinationOwner) {

    int troopsToSend;
    if (neededTroops > availableTroops) {
        troopsToSend = availableTroops;
    }
    else {
        troopsToSend = neededTroops;
    }

    if (destinationOwner == OPPONENT) {
        troopsToSend = availableTroops;
    }

    return troopsToSend;
}
