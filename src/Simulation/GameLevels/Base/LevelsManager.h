#ifndef LEVELPROVIDER_H
#define LEVELPROVIDER_H

#include "Application/AppPartGetter.h"
#include "UserLevelBase.h"
#include "Application/Config/ConfigSimulation.h"


class LevelsManager
{
public:
    LevelBase* LoadLevel(const ConfigLevel& configLevel);

    const ConfigLevel& GetCurrentLevelConfig() const;

    const LevelBase& GetCurrentLevel() const;

    LevelBase& GetCurrentLevel();

private:
    const ConfigLevel* currentLevelConfig = nullptr;
    std::unique_ptr<LevelBase> currentLevel{};
};


#endif //LEVELPROVIDER_H
