#include <Parser.h>
#include "gtest/gtest.h"


TEST(Parser, initGameTest) {

    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.emplace_back(0, 1, 1);
    factoryDirectDistances.emplace_back(0, 2, 1);
    factoryDirectDistances.emplace_back(1, 2, 4);

    Parser::initGameIDE(3, 3, factoryDirectDistances);

    EXPECT_EQ(3, globals::factoryCount);
    EXPECT_EQ(3, globals::linkCount);
    EXPECT_EQ(1, globals::factoryDirectDistances[0][1]);
    EXPECT_EQ(1, globals::factoryDirectDistances[1][0]);
    EXPECT_EQ(1, globals::factoryDirectDistances[0][2]);
    EXPECT_EQ(1, globals::factoryDirectDistances[2][0]);
    EXPECT_EQ(4, globals::factoryDirectDistances[1][2]);
    EXPECT_EQ(4, globals::factoryDirectDistances[2][1]);
}

TEST(Parser, initRountTest) {
    std::vector <std::tuple <int, std::string, int, int, int, int, int> > entities;
    entities.emplace_back(0, "FACTORY", 1, 5, 2, 0, 0);
    entities.emplace_back(1, "FACTORY", 1, 5, 2, 0, 0);
    entities.emplace_back(2, "FACTORY", 0, 5, 2, 0, 0);
    entities.emplace_back(3, "FACTORY", -1, 5, 2, 0, 0);
    entities.emplace_back(4, "TROOP", 1, 0, 1, 4, 2);
    entities.emplace_back(5, "TROOP", -1, 2, 1, 8, 4);

    GameState gameState = Parser::initRoundIDE(2, entities);
    auto &actualFactories = gameState.getFactories();

    EXPECT_EQ(2, gameState.getRound());
    EXPECT_EQ(4, actualFactories.size());

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(i, actualFactories.at(i).getId());
        EXPECT_EQ(5, actualFactories.at(i).getCyborgs());
        EXPECT_EQ(2, actualFactories.at(i).getProduction());
    }

    EXPECT_EQ(0, (int)actualFactories.at(0).getOwner());
    EXPECT_EQ(0, (int)actualFactories.at(1).getOwner());
    EXPECT_EQ(OWNER::NEUTRAL, actualFactories.at(2).getOwner());
    EXPECT_EQ(OWNER::OPPONENT, actualFactories.at(3).getOwner());

    EXPECT_EQ(OWNER::OPPONENT, actualFactories.at(1).getOpTroops().at(0).getOwner());
    EXPECT_EQ(5, actualFactories.at(1).getOpTroops().at(0).getId());
    EXPECT_EQ(2, actualFactories.at(1).getOpTroops().at(0).getFrom());
    EXPECT_EQ(1, actualFactories.at(1).getOpTroops().at(0).getTo());
    EXPECT_EQ(8, actualFactories.at(1).getOpTroops().at(0).getCyborgs());
    EXPECT_EQ(4, actualFactories.at(1).getOpTroops().at(0).getTurnsToArrive());

    EXPECT_EQ(0, (int)actualFactories.at(1).getMyTroops().at(0).getOwner());
    EXPECT_EQ(4, actualFactories.at(1).getMyTroops().at(0).getId());
    EXPECT_EQ(0, actualFactories.at(1).getMyTroops().at(0).getFrom());
    EXPECT_EQ(1, actualFactories.at(1).getMyTroops().at(0).getTo());
    EXPECT_EQ(4, actualFactories.at(1).getMyTroops().at(0).getCyborgs());
    EXPECT_EQ(2, actualFactories.at(1).getMyTroops().at(0).getTurnsToArrive());

}
