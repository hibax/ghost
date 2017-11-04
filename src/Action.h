#pragma once

#include <string>

enum ACTION_TYPE {
    MOVE, WAIT, BOMB, MSG, INC
};

class Action {
public:
    Action(double score, ACTION_TYPE actionType, int from, int to, int cyborgCount, std::string message);
    Action(double score, ACTION_TYPE actionType, int from, int to, int cyborgCount);

    ACTION_TYPE getActionType() const;
    double getScore() const;
    int getSourceId() const;
    int getDestinationId() const;
    int getCyborgCount() const;
    const std::string &getMessage() const;
    bool isValid() const;
    std::string toString() const;
    std::string getActionTypeAsString() const;

    bool operator > (const Action &action) const;
    bool operator == (const Action &other) const;

    void setCyborgCount(int cyborgCount);

private:
    double score;
    ACTION_TYPE actionType;
    int sourceId;
    int destinationId;
    int cyborgCount;
    std::string message;

};