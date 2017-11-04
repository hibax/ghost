
#include <iostream>
#include "Writer.h"

void Writer::debug(std::string log) {
    std::cerr << log << std::endl;
}

std::string Writer::actionsOutput(const Action &action) {
    std::string output;

    switch(action.getActionType()) {
        case ACTION_TYPE::MOVE:
            output += "MOVE " +
                    std::to_string(action.getSourceId()) + " " +
                    std::to_string(action.getDestinationId()) + " " +
                    std::to_string(action.getCyborgCount()) + ";";
            break;
        case ACTION_TYPE::BOMB:
            output += "BOMB " +
                    std::to_string(action.getSourceId()) + " " +
                    std::to_string(action.getDestinationId()) + ";";
        default:
            output += "WAIT;";
            break;
    }

    return output;
}
