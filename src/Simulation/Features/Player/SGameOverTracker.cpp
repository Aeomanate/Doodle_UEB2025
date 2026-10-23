// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SGameOverTracker.h"

#include "Application/AppPartGetter.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/Input/CTagPlayerControllable.h"
#include "Simulation/ECS/Features/Levels/CLevelState.h"
#include "Simulation/ECS/Features/Movable/CCollisions.h"
#include "Simulation/ECS/Features/Movable/CPosition.h"
#include "Simulation/ECS/Features/Visual/SViewport.h"
#include "Simulation/Features/Enemies/CTagEnemy.h"
#include "Simulation/Features/Platforms/CPlatformsStorage.h"

SGameOverTracker::SGameOverTracker()
: System(Order::POST_GAMEPLAY)
{ }

bool SGameOverTracker::Update(float dt)
{
    for (auto& collision: CCollisions::GetData())
    {
        if (collision.collider1->Has<CTagPlayerControllable>()
            && collision.collider2->Has<CTagEnemy>()
            && !collision.isBottomTopCollision)
        {
            CLevelState::GetData() = LevelState::COMPLETED;
            return true;
        }
    }

    ECS::Entity& player = CTagPlayerControllable::GetEntity();
    ECS::Entity* firstPlatform = CPlatformsStorage::GetData().front();
    float platformY = SViewport::ToScreen(firstPlatform->Get<CPosition>().cur).y;
    float playerY = SViewport::ToScreen(player.Get<CPosition>().cur).y;
    float diff = platformY - playerY;
    if (std::abs(diff) > SViewport::Get().size.y)
    {
        CLevelState::GetData() = LevelState::COMPLETED;
        return true;
    }

    return true;
}
