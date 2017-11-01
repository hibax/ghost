#pragma once

#include "Factory.h"
#include "Action.h"

class Utils {

public:
    static void sortActions(std::vector<Action> &actions);

private:
    Utils() = default;
};
