#pragma once

#include <vector>
#include "Action.h"

class Writer {
public:

    static void debug(std::string log);
    static std::string actionsOutput(const Action &action);

private:
    Writer() = default;
};
