
#include <gtest/gtest.h>
#include <Action.h>
#include <Writer.h>

TEST(Writer, actionsOutputTest) {

    std::vector<Action> sortedActions;
    sortedActions.emplace_back(Action(10, ACTION_TYPE::MOVE, 1, 3, 5));
    sortedActions.emplace_back(Action(3, ACTION_TYPE::MOVE, 0, 2, 5));
    sortedActions.emplace_back(Action(2, ACTION_TYPE::MOVE, 0, 3, 5));
    sortedActions.emplace_back(Action(1, ACTION_TYPE::MOVE, 0, 0, 5));

    std::string expectedOutput = "MOVE 1 3 5";
    std::string actualOutput = Writer::actionsOutput(sortedActions);

    EXPECT_EQ(expectedOutput, actualOutput);
}

TEST(Writer, shouldReturnWaitIfNoActions) {

    std::vector<Action> actions;

    std::string expectedOutput = "WAIT";
    std::string actualOutput = Writer::actionsOutput(actions);

    EXPECT_EQ(expectedOutput, actualOutput);
}