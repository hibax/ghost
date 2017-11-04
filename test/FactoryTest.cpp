#include <Parser.h>
#include <Utils.h>
#include "gtest/gtest.h"
#include "Factory.h"


TEST(Factory, simpleTest) {

    Factory myFactory(0, OWNER::ME, 0, 3);

    int expectedProduction(3);

    EXPECT_EQ(expectedProduction, myFactory.getProduction());
}

TEST(Factory, computeBattleTest) {

    Factory myFactory(0, OWNER::ME, 5, 3);


    myFactory.addTroop(Troop(10, OWNER::ME , 1, 0, 5, 2));
    myFactory.addTroop(Troop(10, OWNER::ME , 4, 0, 15, 8));
    myFactory.addTroop(Troop(10, OWNER::OPPONENT , 2, 0, 10, 2));
    myFactory.addTroop(Troop(11, OWNER::OPPONENT , 2, 0, 12, 4));
    myFactory.addTroop(Troop(12, OWNER::OPPONENT , 3, 0, 10, 6));

    EXPECT_EQ(5, myFactory.computeBattle(0));
    EXPECT_EQ(8, myFactory.computeBattle(1));
    EXPECT_EQ(6, myFactory.computeBattle(2));
    EXPECT_EQ(9, myFactory.computeBattle(3));
    EXPECT_EQ(0, myFactory.computeBattle(4));
    EXPECT_EQ(3, myFactory.computeBattle(5));
    EXPECT_EQ(-5, myFactory.computeBattle(6));
    EXPECT_EQ(-8, myFactory.computeBattle(7));
    EXPECT_EQ(5, myFactory.computeBattle(8));
    EXPECT_EQ(8, myFactory.computeBattle(9));

}

// This test is to ensure that we add an extra -1 in case the factory was mine, then opponent's, and let to him with 0 troop
TEST(Factory, shouldNotLetFactoryToOpponentWithZeroTroop) {

    Factory myFactory(0, OWNER::ME, 5, 3);

    myFactory.addTroop(Troop(10, OWNER::ME , 4, 0, 7, 3));
    myFactory.addTroop(Troop(10, OWNER::OPPONENT , 2, 0, 15, 2));

    EXPECT_EQ(5, myFactory.computeBattle(0));
    EXPECT_EQ(8, myFactory.computeBattle(1));
    EXPECT_EQ(-5, myFactory.computeBattle(2));
    EXPECT_EQ(-1, myFactory.computeBattle(3));
    EXPECT_EQ(-4, myFactory.computeBattle(4));
}

TEST(Factory, computeBattleOnNeutralFactory) {
    Factory neutralFactory(0, OWNER::NEUTRAL, 5, 3);

    // 2 more troops incoming for opponent
    neutralFactory.addTroop(Troop(10, OWNER::ME , 4, 0, 10, 2));
    neutralFactory.addTroop(Troop(10, OWNER::OPPONENT , 2, 0, 12, 2));

    // 2 more troops incoming for me
    neutralFactory.addTroop(Troop(10, OWNER::ME , 4, 0, 12, 4));
    neutralFactory.addTroop(Troop(10, OWNER::OPPONENT , 2, 0, 10, 4));

    // Opponent takes the neutral
    neutralFactory.addTroop(Troop(10, OWNER::OPPONENT , 2, 0, 12, 6));

    // And I take it back
    neutralFactory.addTroop(Troop(10, OWNER::ME , 4, 0, 20, 8));


    EXPECT_EQ(-6, neutralFactory.computeBattle(0));
    EXPECT_EQ(-6, neutralFactory.computeBattle(1));
    EXPECT_EQ(-4, neutralFactory.computeBattle(2));
    EXPECT_EQ(-2, neutralFactory.computeBattle(4));
    EXPECT_EQ(-12, neutralFactory.computeBattle(6));
    EXPECT_EQ(3, neutralFactory.computeBattle(8));

}



TEST(Factory, shouldNotGoIfAlreadyOnTheWay) {
    Factory neutralFactory(0, OWNER::NEUTRAL, 5, 3);

    neutralFactory.addTroop(Troop(10, OWNER::ME , 4, 0, 10, 1));

    EXPECT_EQ(-6, neutralFactory.computeBattle(0));
    EXPECT_EQ(5, neutralFactory.computeBattle(1));

}

TEST(Factory, shouldChooseClosestNeutralFactory) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 2);
    factoryDirectDistances.emplace_back(0, 2, 8);
    factoryDirectDistances.emplace_back(1, 2, 6);
    Parser::initGameIDE(3, 3, factoryDirectDistances);

    // Init Factories
    Factory myFactory(0, OWNER::ME, 6, 2);
    std::vector<Factory> factories;
    factories.emplace_back(myFactory);
    factories.emplace_back(Factory(1, OWNER::NEUTRAL, 5, 1));
    factories.emplace_back(Factory(2, OWNER::NEUTRAL, 5, 3));


    std::vector<Action> actualActions = myFactory.computePossibleActions(factories);
    Utils::sortActions(actualActions);

    EXPECT_EQ(1, actualActions.at(0).getDestinationId());
}



TEST(Factory, shouldNotMoveOnItself) {

    Factory myFactory(0, OWNER::ME, 5, 2);
    std::vector<Factory> factories;
    factories.emplace_back(myFactory);


    std::vector<Action> actualActions = myFactory.computePossibleActions(factories);

    EXPECT_EQ(0, actualActions.size());
}


TEST(Factory, shouldChooseWeakestFactory) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 2);
    factoryDirectDistances.emplace_back(0, 2, 2);
    factoryDirectDistances.emplace_back(1, 2, 2);
    Parser::initGameIDE(3, 3, factoryDirectDistances);

    // Init Factories
    Factory myFactory(0, OWNER::ME, 12, 2);
    std::vector<Factory> factories;
    factories.emplace_back(myFactory);
    factories.emplace_back(Factory(1, OWNER::OPPONENT, 5, 0));
    factories.emplace_back(Factory(2, OWNER::OPPONENT, 1, 0));


    std::vector<Action> actualActions = myFactory.computePossibleActions(factories);
    Utils::sortActions(actualActions);

    EXPECT_EQ(2, actualActions.at(0).getDestinationId());
}

TEST(Factory, shouldChooseClosestOpponentFactory) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 10);
    factoryDirectDistances.emplace_back(0, 2, 3);
    Parser::initGameIDE(3, 2, factoryDirectDistances);

    // Init Factories
    Factory myFactory(0, OWNER::ME, 15, 3);
    std::vector<Factory> factories;
    factories.emplace_back(myFactory);
    factories.emplace_back(Factory(1, OWNER::OPPONENT, 2, 0));
    factories.emplace_back(Factory(2, OWNER::OPPONENT, 5, 0));


    std::vector<Action> actualActions = myFactory.computePossibleActions(factories);
    Utils::sortActions(actualActions);

    EXPECT_EQ(2, actualActions.at(0).getDestinationId());
}


TEST(Factory, underAttackDontSendTroops) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 3);
    factoryDirectDistances.emplace_back(0, 2, 3);
    Parser::initGameIDE(3, 2, factoryDirectDistances);

    // Init Factories
    Factory myFactory(0, OWNER::ME, 3, 3);

    std::vector<Factory> factories;
    factories.emplace_back(myFactory);
    factories.emplace_back(Factory(1, OWNER::OPPONENT, 2, 2));
    factories.emplace_back(Factory(2, OWNER::OPPONENT, 1, 2));

    // Init troops
    myFactory.addTroop(Troop(6, OWNER::OPPONENT, 4, 0, 6, 1));


    // TODO : do something for "availableTroops"
    int availableTroops = myFactory.countAvailableTroops(5);
    myFactory.setAvailableTroops(availableTroops);
    std::vector<Action> actualActions = myFactory.computePossibleActions(factories);

    bool isAttacking = false;
    for (const Action &action : actualActions) {
        if (action.getActionType() == MOVE) {
            isAttacking = true;
        }
    }

    EXPECT_FALSE(isAttacking);
}


TEST(Factory, shouldPredictThatFactoryWillNeedHelp) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 1);
    factoryDirectDistances.emplace_back(0, 2, 8);
    Parser::initGameIDE(1, 1, factoryDirectDistances);

    // Init Factories
    Factory myFactory(0, OWNER::ME, 3, 3);
    Factory friendFactory(1, OWNER::ME, 2, 1);

    // Init troops
    friendFactory.addTroop(Troop(6, OWNER::OPPONENT, 2, 1, 12, 4));

    std::vector<Factory> factories;
    factories.emplace_back(myFactory);
    factories.emplace_back(friendFactory);
    factories.emplace_back(Factory(2, OWNER::NEUTRAL, 2, 1));


    std::vector<Action> actualActions = myFactory.computePossibleActions(factories);
    Utils::sortActions(actualActions);

    EXPECT_EQ(1, actualActions.at(0).getDestinationId());
}


TEST(Factory, shouldDefendFactoryThatIsReceivingBomb) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 3);
    factoryDirectDistances.emplace_back(0, 2, 3);
    factoryDirectDistances.emplace_back(1, 2, 3);
    Parser::initGameIDE(1, 1, factoryDirectDistances);

    // Init Factories
    Factory myFactory(0, OWNER::ME, 10, 3);
    Factory friendFactory(1, OWNER::ME, 0, 2);

    // Init troops
    friendFactory.addBomb(Bomb(5, OWNER::OPPONENT, 2, 1, 5));
    friendFactory.addTroop(Troop(6, OWNER::OPPONENT, 2, 1, 1, 6));

    std::vector<Factory> factories;
    factories.emplace_back(myFactory);
    factories.emplace_back(friendFactory);
    factories.emplace_back(Factory(2, OWNER::NEUTRAL, 9, 3));


    std::vector<Action> actualActions = myFactory.computePossibleActions(factories);
    Utils::sortActions(actualActions);

    EXPECT_EQ(1, actualActions.at(0).getDestinationId());
}

// In particular there was an issue with the availableTroop computation
TEST(Factory, ShouldEmptyFactoryBeforeBomb) {

    // Init distances
    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(1, 3, 2);
    factoryDirectDistances.emplace_back(1, 4, 7);
    factoryDirectDistances.emplace_back(3, 4, 3);
    Parser::initGameIDE(3, 3, factoryDirectDistances);

    // Init Factories
    Factory myFactory(1, OWNER::ME, 2, 2);
    Factory friendFactory(3, OWNER::ME, 7, 3);
    Factory enemyFactory(4, OWNER::OPPONENT, 7, 3);

    // Init troops
    friendFactory.addBomb(Bomb(5, OWNER::OPPONENT, 4, 3, 1));
    friendFactory.addTroop(Troop(6, OWNER::OPPONENT, 4, 3, 3, 2));
    friendFactory.addTroop(Troop(6, OWNER::ME, 1, 3, 2, 2));
    enemyFactory.addBomb(Bomb(7, OWNER::ME, 1, 4, 4));

    myFactory.addBomb(Bomb(5, OWNER::OPPONENT, 4, 1, 4));

    std::vector<Factory> factories;
    factories.emplace_back(myFactory);
    factories.emplace_back(friendFactory);
    factories.emplace_back(enemyFactory);

    int actualAvailableTroops1 = myFactory.countAvailableTroops(5);
    int actualAvailableTroops3 = friendFactory.countAvailableTroops(5);

    EXPECT_EQ(2, actualAvailableTroops1);
    EXPECT_EQ(7, actualAvailableTroops3);

    std::vector<Action> actualActions = myFactory.computePossibleActions(factories);
    Utils::sortActions(actualActions);

    EXPECT_EQ(3, actualActions.at(0).getDestinationId());
}

TEST(Factory, shouldTakeBackFactoryThatReceivedBomb) {

    // TODO
}


TEST(Factory, shouldAttackFactoryThatIsReceivingBomb) {

    // TODO
}