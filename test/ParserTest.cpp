#include <Parser.h>
#include <Globals.h>
#include "gtest/gtest.h"


TEST(Parser, initGameTest) {

    std::vector <std::tuple <int, int, int> > factoryDirectDistances;
    factoryDirectDistances.push_back(std::make_tuple(0, 1, 1));
    factoryDirectDistances.push_back(std::make_tuple(0, 2, 1));
    factoryDirectDistances.push_back(std::make_tuple(1, 2, 4));

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
