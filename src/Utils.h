#pragma once

#include "Factory.h"
#include "Action.h"

class Utils {

public:
    static void sortActions(std::vector<Action> &actions);
    static void computeFactoryDanger(const std::vector<Factory> &factories);

private:
    Utils() = default;
};
