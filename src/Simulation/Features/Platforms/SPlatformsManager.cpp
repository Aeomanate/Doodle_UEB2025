// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SPlatformsManager.h"

#include "CPlatformsStorage.h"
#include "EPlatform.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Math/Random.h"
#include "Simulation/ECS/Features/Input/CTagPlayerControllable.h"
#include "Simulation/ECS/Features/LifetimeControl/CNewEntities.h"
#include "Simulation/ECS/Features/LifetimeControl/CTagDespawn.h"
#include "Simulation/ECS/Features/Movable/CPosition.h"
#include "Simulation/ECS/Features/Visual/CSceneElement.h"
#include "Simulation/ECS/Features/Visual/SViewport.h"
#include "Simulation/Features/Abilities/Moving/CJump.h"

SPlatformsManager::SPlatformsManager()
: System(Order::ENTITY_CREATION)
{
    platformSize = getConfig().resources.textures.platform.sprites().front()->GetSize();
    platformOriginOffset = getConfig().resources.textures.platform.originOffset;

    minSpawnDistance = platformSize.y;
    maxSpawnDistance = CTagPlayerControllable::GetEntity().Get<CJump>().maxHeight / 2;

    SpawnBottomPlatforms();
    // SpawnPlatform(Vector2f{ SViewport::Get().size.x / 2, maxSpawnDistance * 3 });
}

bool SPlatformsManager::Update(float dt)
{
    if (IsSpawnRequired())
    {
        SpawnPlatform(DetermineSpawnPos());
        Log("Spawned new platform at",
            std::string(CPlatformsStorage::GetData().back()->Get<CPosition>().cur),
            Logger::Verbosity::GABBY);
    }

    if (IsLastPlatformRemovable())
    {
        RemoveLastPlatform();
    }

    return true;
}

void SPlatformsManager::SpawnPlatform(Vector2f centerPos)
{
    std::unique_ptr<EPlatform> newPlatform = std::make_unique<EPlatform>(centerPos);
    CPlatformsStorage::GetData().push_back(newPlatform.get());
    CNewEntities::GetData().push_back(std::move(newPlatform));
}

void SPlatformsManager::SpawnBottomPlatforms()
{
    // Let's make a bottom row with platforms.
    // At first, need to calc how many of them will be.
    // Then we need an out-of-bound pixel's rest for centering all platforms.
    Vector2f viewportSize = SViewport::Get().size;
    float countPlatformsF = viewportSize.x / platformSize.x;
    float platformRest = countPlatformsF - static_cast<int>(countPlatformsF);
    float pixelsRest = platformRest * platformSize.x;
    int centeringOffset = static_cast<int>(std::round(pixelsRest / 2));
    int countPlatformsI = static_cast<int>(std::round(countPlatformsF));

    Log(std::format(
        "Spawning first {} platforms in a row. Centering offset {}",
        countPlatformsI,
        centeringOffset));

    int x = platformOriginOffset.x * platformSize.x + centeringOffset * 0;
    for (int i = 0; i < countPlatformsI; ++i)
    {
        SpawnPlatform(Vector2f{ x + i * platformSize.x, 0 });
    }
}

bool SPlatformsManager::IsSpawnRequired()
{
    Vector2f highestPos = CPlatformsStorage::GetData().back()->Get<CPosition>().cur + platformSize;

    float viewportPos = SViewport::Get().pos.y;
    float viewportHeight = SViewport::Get().size.y;

    return highestPos.y < viewportPos + viewportHeight;
}

Vector2f SPlatformsManager::DetermineSpawnPos()
{
    Vector2f highestPos = CPlatformsStorage::GetData().back()->Get<CPosition>().cur;
    highestPos.y += platformSize.y;

    Vector2f viewSize = SViewport::Get().size;

    Vector2f choosePos = Vector2f{
        Random::Float(
            platformSize.x * platformOriginOffset.x,
            viewSize.x - platformSize.x * platformOriginOffset.x
        ),
        highestPos.y + Random::Float(minSpawnDistance, maxSpawnDistance)
    };
    return choosePos;
}

void SPlatformsManager::RemoveLastPlatform()
{
    CPlatformsStorage::GetData().front()->Claim<CTagDespawn>();
    CPlatformsStorage::GetData().erase(
        r::remove(
            CPlatformsStorage::GetData(),
            CPlatformsStorage::GetData().front()
        ).begin()
    );
}

bool SPlatformsManager::IsLastPlatformRemovable()
{
    float screenPlatformY = SViewport::ToScreen(
        CPlatformsStorage::GetData().front()->Get<CPosition>().cur + platformSize
    ).y;
    return SViewport::ToScreen(SViewport::Get().pos).y < screenPlatformY;
}
