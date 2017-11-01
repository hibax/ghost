#pragma once

#include <string>

enum ACTION_TYPE {
    MOVE, WAIT, BOMB, MSG, INC
};

class Action {
public:
    Action(float score, ACTION_TYPE actionType, int from, int to, int cyborgCount, std::string message);
    Action(float score, ACTION_TYPE actionType, int from, int to, int cyborgCount);

    ACTION_TYPE getActionType() const;
    float getScore() const;
    int getSourceId() const;
    int getDestinationId() const;
    int getCyborgCount() const;
    const std::string &getMessage() const;
    bool isValid() const;
    std::string toString();

    bool operator > (const Action &action) const;
    bool operator == (const Action &other) const;

private:
    float score;
    ACTION_TYPE actionType;
    int sourceId;
    int destinationId;
    int cyborgCount;
    std::string message;

};