
#include "GameState.h"
#include <functional>
#include <algorithm>
#include <cmath>
#include "Utils.h"
#include "Writer.h"
#include "Globals.h"

void Utils::sortActions(std::vector<Action> &actions) {
    std::sort(actions.begin(), actions.end(), std::greater<Action>());
}

void Utils::computeFactoryDanger(const std::vector<Factory> &factories) {

    for (int i = 0; i < globals::factoryCount; ++i) {

        float tmpFactoryDanger = 0;

        for (int j = 0; j < globals::factoryCount; ++j) {

            double coef;
            if (factories.at(j).getOwner() == ME) {
                coef = -1.0;
            }
            else {
                coef = 1.0;
            }

            if (i != j) {

                tmpFactoryDanger += (coef * factories.at(j).getCyborgs() / ( std::pow(globals::factoryDirectDistances[i][j] + 1, 2)));
            }
            else {
                tmpFactoryDanger += (coef * factories.at(j).getCyborgs());
            }
        }
        globals::factoryDanger[i] = tmpFactoryDanger;
    }

}
