
#ifndef GHOSTINTHECELL_UTILS_H
#define GHOSTINTHECELL_UTILS_H


#include "Factory.h"
#include "Action.h"

class Utils {

public:
    static void sortActions(std::vector<Action> &actions);

private:
    Utils() = default;
};


#endif //GHOSTINTHECELL_UTILS_H
