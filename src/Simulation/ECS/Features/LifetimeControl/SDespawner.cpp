// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SDespawner.h"

#include "CActivityTags.h"
#include "CTagDespawn.h"
#include "Application/AppPartGetter.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/GameLevels/Base/LevelsManager.h"

SDespawner::SDespawner()
: System(Order::GARBAGE_COLLECTOR)
{ }

bool SDespawner::Update(float dt)
{
    while (!CTagDespawn::Empty())
    {
        ECS::Entity& entity = CTagDespawn::GetEntity();
        getLevelsManager().GetCurrentLevel().Remove(&entity);
    }
    return true;
}
