#include "LevelsManager.h"

#include "Application/Details/Logger.h"
#include "Simulation/GameLevels/Base/LevelBase.h"

LevelBase* LevelsManager::LoadLevel(const ConfigLevel& configLevel)
{
    Log("Loading level", configLevel.name);
    LevelBase::LevelUPtr nextLevel = nullptr;
    nextLevel = getFabricLevels().Create(configLevel, std::move(currentLevel));

    currentLevel = std::move(nextLevel);

    if(currentLevel)
    {
        Log("UserLevel loaded", configLevel.name);
    }
    else
    {
        Log("UserLevel wasn't load", configLevel.name, Logger::Verbosity::CRITICAL);
    }

    currentLevelConfig = &configLevel;
    return currentLevel.get();
}

const ConfigLevel& LevelsManager::GetCurrentLevelConfig() const
{
    return *currentLevelConfig;
}

const LevelBase& LevelsManager::GetCurrentLevel() const
{
    return *currentLevel;
}

LevelBase& LevelsManager::GetCurrentLevel()
{
    return *currentLevel;
}
