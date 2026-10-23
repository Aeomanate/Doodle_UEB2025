// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SEnemyManager.h"

#include "CTagEnemy.h"
#include "CTagNoEnemySpawner.h"
#include "EEnemy.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Math/Random.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/LifetimeControl/CNewEntities.h"
#include "Simulation/ECS/Features/LifetimeControl/CTagDespawn.h"
#include "Simulation/ECS/Features/Movable/CCollisions.h"
#include "Simulation/ECS/Features/Movable/CPosition.h"
#include "Simulation/ECS/Features/Visual/SViewport.h"
#include "Simulation/Features/Platforms/CPlatformsStorage.h"

SEnemyManager::SEnemyManager()
: System(Order::ENTITY_CREATION)
{
    enemySize = getConfig().resources.textures.enemy.idle.sprite.get()->GetSize();
}

bool SEnemyManager::Update(float dt)
{
    ECS::Entity* lastPlatform = CPlatformsStorage::GetData().back();
    if (!lastPlatform->Has<CTagNoEnemySpawner>())
    {
        lastPlatform->Claim<CTagNoEnemySpawner>();

        if (Random::Float() <= getConfig().simulation.enemies.spawnProbability)
        {
            std::unique_ptr<ECS::Entity> newEnemy = std::make_unique<EEnemy>(lastPlatform);
            enemies.push_back(newEnemy.get());
            CNewEntities::GetData().push_back(std::move(newEnemy));
        }
    }

    if (IsLastEnemyRemovable())
    {
        RemoveEnemy(enemies.front());
    }

    ProcessKilledEnemy();
    return true;
}

void SEnemyManager::RemoveEnemy(ECS::Entity* entity)
{
    enemies.front()->Claim<CTagDespawn>();
    enemies.erase(r::remove(enemies, entity).begin());
}

bool SEnemyManager::IsLastEnemyRemovable()
{
    if (enemies.empty())
    {
        return false;
    }

    // TODO REFACTOR
    // Duplicate with PlatformManager
    float screenEnemyY = SViewport::ToScreen(
        enemies.front()->Get<CPosition>().cur + enemySize
    ).y;
    return SViewport::ToScreen(SViewport::Get().pos).y < screenEnemyY;
}

void SEnemyManager::ProcessKilledEnemy()
{
    for (auto& collision: CCollisions::GetData())
    {
        if (collision.collider2->Has<CTagEnemy>() && collision.isBottomTopCollision)
        {
            RemoveEnemy(collision.collider2);
        }
    }
}
