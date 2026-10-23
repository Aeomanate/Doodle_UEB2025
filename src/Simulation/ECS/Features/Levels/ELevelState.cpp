#include "ELevelState.h"

#include "CLevelState.h"

ELevelState::ELevelState()
: ECS::Entity("LevelState")
{
    Claim<CLevelState>() = LevelState::RUNNING;
}
