#include "EPlayer.h"

#include "Application/AppPartGetter.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Simulation/ECS/ECS.h"
#include "Simulation/ECS/Features/LifetimeControl/CActivityTags.h"
#include "Simulation/ECS/Features/Movable/CCanCollide.h"
#include "Simulation/ECS/Features/Visual/CCameraOffset.h"
#include "Simulation/ECS/Features/Visual/SViewport.h"
#include "Simulation/Features/Abilities/Moving/CFallVelocity.h"
#include "Simulation/Features/Abilities/Moving/CJump.h"
#include "Simulation/Features/Abilities/Moving/CSpeedBooster.h"
#include "Simulation/Features/Abilities/Shooting/CCannon.h"
#include "Simulation/Features/Score/CPlayerScore.h"


EPlayer::EPlayer()
: ECS::Entity("player")
{
    const ConfigPlayer& configPlayer = getConfig().simulation.player;

    Claim<CTagPlayerControllable>();

    Claim<CSprite>() = getConfig().resources.textures.player.idle.sprite.value();
    Claim<CZOrder>() = ZOrder::PLAYER;
    Claim<CPosition>() = SViewport::Get().size * configPlayer.startOffset;
    Claim<CCameraOffset>() = Claim<CPosition>().cur;

    Claim<CPhysics>() = { .mass = configPlayer.mass };

    Claim<CPlayerScore>();
    Claim<CCannon>();

    float maxJumpHeight =
        Get<CPosition>().cur.y
        + Get<CSprite>()->GetSize().y
        + getConfig().resources.textures.platform.sprites().front()->GetSize().y;

    Log("Max jump height", maxJumpHeight);
    Log("Max jump height screen percent", maxJumpHeight / SViewport::Get().size.y * 100);

    Claim<CJump>() = {
        .maxHeight = maxJumpHeight,
        .duration = configPlayer.jumpDurationSec
    };

    Claim<CFallVelocity>() = getConfig().simulation.player.fallVelocity;

    Claim<CCanCollide>() = true;

    Claim<CSpeedBooster>() = Vector2f { 1, 1 };

    Claim<CTagActive>();
}
