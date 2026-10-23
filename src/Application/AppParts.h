#ifndef APPOBJECTS_H
#define APPOBJECTS_H
#include "AssetsStorage.h"
#include "Singleton.h"
#include "Config/MainConfig.h"
#include "Simulation/Simulation.h"
#include "Simulation/GameLevels/Base/LevelsFabric.h"
#include "Simulation/GameLevels/Base/LevelsManager.h"


// A template for lazy initializing
// and prevent errors before main() started
template <class App>
struct AppParts: Singleton<AppParts<App>>
{
    std::tuple<
        MainConfig,

        AssetsStorage,
        Simulation,

        LevelsManager
    > parts;
};

#endif //APPOBJECTS_H
