#include <iostream>
#include "Parser.h"
#include "Utils.h"
#include "Writer.h"


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int round = 0;
    Parser::initGame();

    // game loop
    while (1) {
        GameState gameState = Parser::initRound(round);

        std::string output = gameState.computeActions();

        std::cout << output << std::endl;

        ++round;
    }
}