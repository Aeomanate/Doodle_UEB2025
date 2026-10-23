#include "AppParts.h"
#include "AppPartGetter.h"
#include "Application/Application.h"

MainConfig& getMainConfig()
{
    return std::get<MainConfig>(AppParts<Application>::GetInstance().parts);
}
ConfigGeneral& getConfig()
{
    return getMainConfig().general;
}

LevelsManager& getLevelsManager()
{
    return std::get<LevelsManager>(AppParts<Application>::GetInstance().parts);
}

LevelsFabric& getFabricLevels()
{
    return LevelsFabric::GetInstance();
}

AssetsStorage& getAssetsStorage()
{
    return std::get<AssetsStorage>(AppParts<Application>::GetInstance().parts);
}

Simulation& getSimulation()
{
    return std::get<Simulation>(AppParts<Application>::GetInstance().parts);
}

