
#include <iostream>
#include "Writer.h"

void Writer::debug(std::string log) {
    std::cerr << log << std::endl;
}

std::string Writer::actionsOutput(const std::vector<Action> &actions) {
    std::string output;

    if (actions.empty()) {
        return "WAIT";
    }

    const Action &action = actions.at(0);
    switch(action.getActionType()) {
        case ACTION_TYPE::MOVE:
            output += "MOVE " +
                    std::to_string(action.getSourceId()) + " " +
                    std::to_string(action.getDestinationId()) + " " +
                    std::to_string(action.getCyborgCount());
            break;
        default:
            output += "WAIT";
            break;
    }

    return output;
}
