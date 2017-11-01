#pragma once

namespace  globals {
    extern int factoryCount;
    extern int linkCount;
    extern int factoryDirectDistances[15][15];
}


enum OWNER {ME, OPPONENT, NEUTRAL};
extern OWNER argToOwner(int arg);
