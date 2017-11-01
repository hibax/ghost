
#include "GameState.h"
#include <functional>
#include <algorithm>
#include "Utils.h"

void Utils::sortActions(std::vector<Action> &actions) {
    std::sort(actions.begin(), actions.end(), std::greater<Action>());
}