// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "EPlatform.h"

#include "CTagPlatform.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Simulation/ECS/Features/LifetimeControl/CActivityTags.h"
#include "Simulation/ECS/Features/Movable/CCanCollide.h"
#include "Simulation/ECS/Features/Movable/CPosition.h"
#include "Simulation/ECS/Features/Visual/CSceneElement.h"

EPlatform::EPlatform(Vector2f position)
: Entity(std::format("Platform {}, pos: {}", ++platformCount, position))
{
    Claim<CSprite>() = getConfig().resources.textures.platform.sprites().front();
    Claim<CZOrder>() = ZOrder::PLATFORMS;
    Claim<CPosition>() = position;
    Claim<CCanCollide>() = true;
    Claim<CTagPlatform>();

    Log("Created", GetName());
}
