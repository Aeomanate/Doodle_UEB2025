#include "SInputMove.h"

#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Application/Details/Logger.h"
#include "Math/Vector2.h"
#include "Simulation/ECS/ECS.h"
#include "Simulation/Features/Abilities/Shooting/CCannon.h"
#include "Simulation/Features/Abilities/Shooting/CRequestFire.h"

SInputMove::SInputMove()
: ECS::System(ECS::System::Order::PRE_PHYSICS)
{
    const auto& keys = getConfig().simulation.keys;
    moveMapping = {
        { keys.left , [] () { return Vector2i { -1, 0 }; } },
        { keys.right, [] () { return Vector2i {  1, 0 }; } },
        { keys.noop1, [] () { return Vector2i {  0, 0 }; } },
        { keys.noop2, [] () { return Vector2i {  0, 0 }; } },
    };
}

bool SInputMove::Update(float)
{
    auto* keyQueuePtr = CInputKeyHoldingEvent::TryGetData();
    if (!keyQueuePtr)
    {
        Log("CInputKeyHoldingEvent absent for player", Logger::Verbosity::WARNING);
    }

    ECS::Entity& player = CTagPlayerControllable::GetEntity();
    const ConfigPlayer& configPlayer = getConfig().simulation.player;

    KeyHoldingEvent keyEvent = keyQueuePtr->empty()
                               ? KeyHoldingEvent { .key = getConfig().simulation.keys.noop1 }
                               : keyQueuePtr->front();
    currentMoveDir += (-1 + 2 * keyEvent.isKeyHolding) * moveMapping.at(keyEvent.key)();
    currentMoveDir.x = std::clamp(currentMoveDir.x, -1, 1); // If input sticks suddenly

    auto playerTextures = getConfig().resources.textures.player;
    const ConfigTexture& playerTexture = currentMoveDir.x < 0
                                         ? playerTextures.left
                                         : currentMoveDir.x > 0
                                         ? playerTextures.right
                                         : playerTextures.idle;
    player.Get<CSprite>() = playerTexture.sprite.value();


    PhysicBody& physicBody = player.Get<CPhysics>();
    physicBody.speed += configPlayer.movingSpeedPxS * currentMoveDir;

    return true;
}
