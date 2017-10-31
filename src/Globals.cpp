
#include "Globals.h"

int globals::factoryCount = 0;
int globals::linkCount = 0;
int globals::factoryDirectDistances[15][15] = { { 0 } };


OWNER argToOwner(int arg) {
    switch (arg) {
        case 1:
            return ME;
        case -1:
            return OPPONENT;
        default:
            return NEUTRAL;
    }
}