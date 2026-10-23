#ifndef LEVEL1_H
#define LEVEL1_H


#include "Simulation/GameLevels/Base/UserLevelBase.h"

class Level1: public UserLevelBase<Level1, &ConfigLevels::level1>
{
public:
    Level1(LevelUPtr&& prevLevel = nullptr);
};


#endif //LEVEL1_H
