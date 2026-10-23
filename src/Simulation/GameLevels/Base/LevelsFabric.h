#ifndef LEVELCREATORSSTORAGE_H
#define LEVELCREATORSSTORAGE_H


#include "LevelBase.h"
#include "Application/AppPartGetter.h"
#include "Application/Singleton.h"
#include "Application/Config/ConfigGeneral.h"

class LevelsFabric: public Singleton<LevelsFabric>
{
    template <class UserLevel, ConfigLevel ConfigLevels::*configLevelMemberPtr>
    friend class UserLevelBase;

public:
    template <class PrevLevel = int>
    LevelBase::LevelUPtr Create(const ConfigLevel& configLevel, PrevLevel&& prevLevel = {})
    {
        return fabricWorkers[configLevel.name](std::move(prevLevel));
    }

private:
    template <class UserLevel, ConfigLevel ConfigLevels::*configLevelPtr>
    bool RegisterLevel()
    {
        // Use the default config to get the level name at registration time,
        // since the main config may not be loaded yet
        auto defaultConfig = getDefaultConfigSimulation();
        auto configLevel = defaultConfig.configLevels.*configLevelPtr;
        fabricWorkers.try_emplace(configLevel.name, [] (LevelBase::LevelUPtr&& prevLevel) {
            return std::make_unique<UserLevel>(std::move(prevLevel));
        });
        return true;
    }

private:
    using LevelCreatorFunc = std::function<LevelBase::LevelUPtr(LevelBase::LevelUPtr)>;
    std::unordered_map<std::string, LevelCreatorFunc> fabricWorkers;
};

#endif //LEVELCREATORSSTORAGE_H
