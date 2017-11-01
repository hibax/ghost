
#include <gtest/gtest.h>
#include <Action.h>
#include <Utils.h>

TEST(Utils, sortActionsTest) {


    std::vector<Action> actions;
    actions.emplace_back(Action(1, ACTION_TYPE::MOVE, 0, 0, 5));
    actions.emplace_back(Action(3, ACTION_TYPE::MOVE, 0, 2, 5));
    actions.emplace_back(Action(2, ACTION_TYPE::MOVE, 0, 3, 5));
    actions.emplace_back(Action(10, ACTION_TYPE::MOVE, 1, 3, 5));


    std::vector<Action> sortedActions;
    sortedActions.emplace_back(Action(10, ACTION_TYPE::MOVE, 1, 3, 5));
    sortedActions.emplace_back(Action(3, ACTION_TYPE::MOVE, 0, 2, 5));
    sortedActions.emplace_back(Action(2, ACTION_TYPE::MOVE, 0, 3, 5));
    sortedActions.emplace_back(Action(1, ACTION_TYPE::MOVE, 0, 0, 5));

    EXPECT_NE(sortedActions, actions);

    Utils::sortActions(actions);

    EXPECT_EQ(sortedActions, actions);

}