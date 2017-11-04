
#include <iostream>
#include <sstream>
#include "Parser.h"
#include "Writer.h"
#include "Utils.h"
#include "Globals.h"

void Parser::initGame() {
    int factoryCount; // the number of factories
    std::cin >> factoryCount; std::cin.ignore();
    globals::factoryCount = factoryCount;

    int linkCount; // the number of links between factories
    std::cin >> linkCount; std::cin.ignore();
    globals::linkCount = linkCount;


    for (int i = 0; i < linkCount; i++) {
        int factory1;
        int factory2;
        int distance;
        std::cin >> factory1 >> factory2 >> distance; std::cin.ignore();

        globals::factoryDirectDistances[factory1][factory2] = distance;
        globals::factoryDirectDistances[factory2][factory1] = distance;

        std::stringstream ss;
        ss << "[Distance] " << factory1 << "-" << factory2 << " = " << globals::factoryDirectDistances[factory1][factory2];
        Writer::debug(ss.str());

    }
}

void Parser::initGameIDE(int factoryCount, int linkCount, std::vector <std::tuple <int, int, int> > &factoryDirectDistances) {
    globals::factoryCount = factoryCount;
    globals::linkCount = linkCount;

    for (std::tuple <int, int, int> &factoryDirectDistance : factoryDirectDistances) {
        int &factory1 = std::get<0>(factoryDirectDistance);
        int &factory2 = std::get<1>(factoryDirectDistance);
        int &distance = std::get<2>(factoryDirectDistance);

        globals::factoryDirectDistances[factory1][factory2] = distance;
        globals::factoryDirectDistances[factory2][factory1] = distance;
    }

}

GameState Parser::initRound(int round) {
    std::vector<Factory> factories;
    std::vector<Troop> troops;

    int entityCount; // the number of entities (e.g. factories and troops)
    std::cin >> entityCount; std::cin.ignore();

    for (int i = 0; i < entityCount; i++) {
        int entityId;
        std::string entityType;
        int arg1, arg2, arg3, arg4, arg5;
        std::cin >> entityId >> entityType >> arg1 >> arg2 >> arg3 >> arg4 >> arg5; std::cin.ignore();

        fillFactories(factories, entityId, entityType, arg1, arg2, arg3, arg4, arg5);
    }

    //Utils::computeFactoryDanger(factories);
    //
    //for (int i = 0; i < globals::factoryCount; ++i) {
    //    Writer::debug("[Factory " + std::to_string(i) + "] Attractiveness " + std::to_string(globals::factoryDanger[i]));
    //}

    return GameState(round, factories);
}

GameState Parser::initRoundIDE(int round, std::vector <std::tuple <int, std::string, int, int, int, int, int> > &entities) {
    std::vector<Factory> factories;
    std::vector<Troop> troops;

    for (std::tuple <int, std::string, int, int, int, int, int> &entity : entities) {
        int &entityId = std::get<0>(entity);
        std::string &entityType = std::get<1>(entity);
        int &arg1 = std::get<2>(entity);
        int &arg2 = std::get<3>(entity);
        int &arg3 = std::get<4>(entity);
        int &arg4 = std::get<5>(entity);
        int &arg5 = std::get<6>(entity);

        fillFactories(factories, entityId, entityType, arg1, arg2, arg3, arg4, arg5);
    }
    return GameState(round, factories);
}


void Parser::fillFactories(std::vector<Factory> &factories, int entityId, const std::string &entityType, int arg1, int arg2, int arg3,
                           int arg4, int arg5) {

    if (entityType == "FACTORY") {

        factories.emplace_back(entityId, argToOwner(arg1), arg2, arg3, arg4);
    }
    else if (entityType == "TROOP") {

        auto targetFactoryId = (size_t)arg3;
        factories.at(targetFactoryId).addTroop(Troop(entityId, argToOwner(arg1), arg2, arg3, arg4, arg5));
    }
    else {
        // BOMBS

        if (argToOwner(arg1) == ME) {

            auto targetFactoryId = (size_t)arg3;
            factories.at(targetFactoryId).addBomb(Bomb(entityId, ME, arg2, arg3, arg4));
        }
        else
        {
            bool newBomb = true;
            int bombTurnsCount = 0;

            for (Bomb &bomb : globals::opponentBombs) {
                if (bomb.getId() == entityId) {
                    newBomb = false;
                    bombTurnsCount = bomb.getTurnsToArrive() + 1;
                    bomb.setTurnsToArrive(bombTurnsCount);

                    Writer::debug("[Global] Bomb " + std::to_string(entityId)
                                  + " was launched " + std::to_string(bombTurnsCount) + " turns ago");

                }
            }
            if (newBomb) {
                globals::opponentBombs.emplace_back(entityId, OPPONENT, arg2, -1, 0);

                Writer::debug("[Global] Bomb " + std::to_string(entityId) + " was just launched");
            }


            for (Factory &factory : factories) {

                factory.addBomb(Bomb(entityId, OPPONENT, arg2, factory.getId(),
                                     globals::factoryDirectDistances[arg2][factory.getId()] - bombTurnsCount));

                Writer::debug("[Factory " + std::to_string(factory.getId())
                              + "] Bomb incoming in "
                              + std::to_string(globals::factoryDirectDistances[arg2][factory.getId()] - bombTurnsCount)
                              + " turns");
            }
        }
    }

}
