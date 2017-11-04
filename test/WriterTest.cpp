
#include <gtest/gtest.h>
#include <Action.h>
#include <Writer.h>

TEST(Writer, actionsOutputTest) {

    Action action(10, ACTION_TYPE::MOVE, 1, 3, 5);

    std::string expectedOutput = "MOVE 1 3 5;";
    std::string actualOutput = Writer::actionsOutput(action);

    EXPECT_EQ(expectedOutput, actualOutput);
}
