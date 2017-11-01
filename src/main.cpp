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

        std::vector<Action> actions = gameState.computeActions();

        Utils::sortActions(actions);

        for (Action action : actions) {
            Writer::debug(action.toString());
        }

        std::string output = Writer::actionsOutput(actions);

        std::cout << output << std::endl;

        ++round;
    }
}