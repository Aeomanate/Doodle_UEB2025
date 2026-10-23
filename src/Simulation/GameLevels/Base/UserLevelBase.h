#ifndef LEVEL_H
#define LEVEL_H

#include "LevelsFabric.h"
#include "LevelBase.h"

template <class PassedLevel, ConfigLevel ConfigLevels::*configLevelMemberPtr>
class UserLevelBase: public LevelBase
{
protected:
    UserLevelBase()
    {
        // Because unused static field IS_REGISTERED will be deleted from template instantiation
        // https://timsong-cpp.github.io/cppwp/n4868/temp.spec#temp.inst-11
        if(!IS_REGISTERED)
        { return; }
    }
    static inline bool IS_REGISTERED = getFabricLevels().RegisterLevel<PassedLevel, configLevelMemberPtr>();
};

#endif //LEVEL_H
