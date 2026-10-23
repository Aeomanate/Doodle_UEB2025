#include "SLevelStateObserver.h"
#include "CLevelState.h"
#include "Application/AppPartGetter.h"
#include "Simulation/GameLevels/Base/LevelsManager.h"

SLevelStateObserver::SLevelStateObserver()
: ECS::System(ECS::System::Order::POST_GAMEPLAY)
{ }

bool SLevelStateObserver::Update(float)
{
    LevelState cachedState = getLevelsManager().GetCurrentLevel().GetLevelState();

    auto newStatePtr = CLevelState::TryGetData();
    if (!newStatePtr)
    {
        Log("CLevelState absent", Logger::Verbosity::WARNING);
        return true;
    }

    if (*newStatePtr != cachedState)
    {
        getLevelsManager().GetCurrentLevel().SetLevelState(*newStatePtr);
    }
    return true;
}
