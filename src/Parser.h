
#ifndef GHOSTINTHECELL_PARSER_H
#define GHOSTINTHECELL_PARSER_H


#include "GameState.h"

class Parser {
public:
    static void initGame();
    static void initGameIDE(int factoryCount, int linkCount, std::vector <std::tuple <int, int, int> > &factoryDirectDistances);
    static GameState initRound();
    static GameState initRoundIDE();

private:
    Parser() = default;
};


#endif //GHOSTINTHECELL_PARSER_H
