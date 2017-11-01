
#include "Action.h"

#include <utility>
#include <sstream>

Action::Action(float score, ACTION_TYPE actionType, int from, int to, int cyborgCount, std::string message) :
        score(score), actionType(actionType), sourceId(from), destinationId(to), cyborgCount(cyborgCount), message(
        std::move(message)) {

}

Action::Action(float score, ACTION_TYPE actionType, int from, int to, int cyborgCount) :
        Action(score, actionType, from, to, cyborgCount, ""){
}

ACTION_TYPE Action::getActionType() const {
    return actionType;
}

int Action::getSourceId() const {
    return sourceId;
}

int Action::getDestinationId() const {
    return destinationId;
}

int Action::getCyborgCount() const {
    return cyborgCount;
}

const std::string &Action::getMessage() const {
    return message;
}

float Action::getScore() const {
    return score;
}

bool Action::operator>(const Action &action) const {
    return (score > action.getScore());
}

bool Action::operator==(const Action &other) const {
    return (actionType == other.actionType) &&
            (sourceId == other.sourceId) &&
            (destinationId == other.destinationId) &&
            (cyborgCount == other.cyborgCount) &&
            (score == other.score);
}

bool Action::isValid() const {
    if (actionType == ACTION_TYPE::MOVE) {
        return (sourceId != destinationId);
    }
    return true;
}

std::string Action::toString() {
    std::stringstream ss;
    ss << "[Action]" << " type " << actionType
       << " from " << sourceId << " to " << destinationId
       << " cyborgs " << cyborgCount << " score " << score;
    return ss.str();
}



