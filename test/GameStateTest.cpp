

#include <gtest/gtest.h>
#include <Factory.h>
#include <GameState.h>
#include <Parser.h>
#include <Utils.h>
#include <Writer.h>


void areActionsEquals(const Action &expected, const Action &actual) {
    EXPECT_EQ(expected.getActionType(), actual.getActionType());
    EXPECT_EQ(expected.getSourceId(), actual.getSourceId());
    EXPECT_EQ(expected.getDestinationId(), actual.getDestinationId());
    EXPECT_EQ(expected.getCyborgCount(), actual.getCyborgCount());
    //EXPECT_EQ(expected.getScore(), actual.getScore());
}

// Global Test
TEST(ComputeActions, globalTest) {
    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 1);
    factoryDirectDistances.emplace_back(0, 2, 1);
    factoryDirectDistances.emplace_back(1, 2, 4);
    Parser::initGameIDE(3, 3, factoryDirectDistances);

    // Init Factories
    std::vector<Factory> factories;
    factories.emplace_back(Factory(0, OWNER::ME, 6, 2));
    factories.emplace_back(Factory(1, OWNER::ME, 6, 2));
    factories.emplace_back(Factory(2, OWNER::NEUTRAL, 5, 2));
    factories.emplace_back(Factory(3, OWNER::OPPONENT, 5, 2));

    int round = 2;
    GameState gameState(round, factories);

    std::vector<Action> actualActions = gameState.computeActions();

    std::vector<Action> expectedActions;
    //expectedActions.emplace_back(Action(0, ACTION_TYPE::MOVE, 0, 0, 6));
    expectedActions.emplace_back(Action(0, ACTION_TYPE::MOVE, 0, 1, 6));
    expectedActions.emplace_back(Action(10, ACTION_TYPE::MOVE, 0, 2, 6));
    expectedActions.emplace_back(Action(9, ACTION_TYPE::MOVE, 0, 3, 6));
    expectedActions.emplace_back(Action(0, ACTION_TYPE::MOVE, 1, 0, 6));
    //expectedActions.emplace_back(Action(0, ACTION_TYPE::MOVE, 1, 1, 6));
    expectedActions.emplace_back(Action(10, ACTION_TYPE::MOVE, 1, 2, 6));
    expectedActions.emplace_back(Action(9, ACTION_TYPE::MOVE, 1, 3, 6));

    EXPECT_EQ(expectedActions.size(), actualActions.size());
    for (int i = 0; i< expectedActions.size(); ++i) {
        areActionsEquals(expectedActions.at(i), actualActions.at(i));
    }
}

TEST(ComputeActions, shouldChooseClosestNeutralFactory) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 2);
    factoryDirectDistances.emplace_back(0, 2, 8);
    factoryDirectDistances.emplace_back(1, 2, 6);
    Parser::initGameIDE(3, 3, factoryDirectDistances);

    // Init Factories
    std::vector<Factory> factories;
    factories.emplace_back(Factory(0, OWNER::ME, 6, 2));
    factories.emplace_back(Factory(1, OWNER::NEUTRAL, 5, 1));
    factories.emplace_back(Factory(2, OWNER::NEUTRAL, 5, 3));

    int round = 2;
    GameState gameState(round, factories);

    std::vector<Action> actualActions = gameState.computeActions();
    Utils::sortActions(actualActions);

    EXPECT_EQ(1, actualActions.at(0).getDestinationId());
}

TEST(ComputeActions, shouldChooseClosestOpponentFactory) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 10);
    factoryDirectDistances.emplace_back(0, 2, 3);
    Parser::initGameIDE(3, 2, factoryDirectDistances);

    // Init Factories
    std::vector<Factory> factories;
    factories.emplace_back(Factory(0, OWNER::ME, 15, 3));
    factories.emplace_back(Factory(1, OWNER::OPPONENT, 2, 3));
    factories.emplace_back(Factory(2, OWNER::OPPONENT, 5, 1));

    int round = 2;
    GameState gameState(round, factories);

    std::vector<Action> actualActions = gameState.computeActions();
    Utils::sortActions(actualActions);

    EXPECT_EQ(2, actualActions.at(0).getDestinationId());
}

TEST(ComputeActions, shouldChooseWeakestFactory) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 2);
    factoryDirectDistances.emplace_back(0, 2, 2);
    factoryDirectDistances.emplace_back(1, 2, 2);
    Parser::initGameIDE(3, 3, factoryDirectDistances);

    // Init Factories
    std::vector<Factory> factories;
    factories.emplace_back(Factory(0, OWNER::ME, 12, 2));
    factories.emplace_back(Factory(1, OWNER::OPPONENT, 5, 3));
    factories.emplace_back(Factory(2, OWNER::OPPONENT, 1, 2));

    int round = 2;
    GameState gameState(round, factories);

    std::vector<Action> actualActions = gameState.computeActions();
    Utils::sortActions(actualActions);

    EXPECT_EQ(2, actualActions.at(0).getDestinationId());
}

TEST(ComputeActions, shouldNotMoveOnItself) {

    std::vector<Factory> factories;
    factories.emplace_back(Factory(0, OWNER::ME, 5, 2));

    int round = 2;
    GameState gameState(round, factories);

    std::vector<Action> actualActions = gameState.computeActions();

    EXPECT_EQ(0, actualActions.size());
}
