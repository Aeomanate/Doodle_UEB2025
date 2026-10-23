// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "EEnemy.h"

#include "CTagEnemy.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Math/Random.h"
#include "Simulation/ECS/Features/Movable/CCanCollide.h"
#include "Simulation/ECS/Features/Movable/CPhysics.h"
#include "Simulation/ECS/Features/Visual/CSceneElement.h"
#include "Simulation/Features/Abilities/Moving/CFallVelocity.h"
#include "Simulation/Features/Abilities/Moving/CJump.h"
#include "Simulation/Features/Platforms/CTagPlatform.h"

EEnemy::EEnemy(Entity* platform)
: Entity("Enemy")
{
    int spriteIndex = Random::Int(0, 3);
    Claim<CSprite>() =
        spriteIndex == 0
            ? getConfig().resources.textures.enemy.left.sprite.value()
            : spriteIndex == 1
                  ? getConfig().resources.textures.enemy.idle.sprite.value()
                  : getConfig().resources.textures.enemy.right.sprite.value();

    Claim<CZOrder>() = ZOrder::PLATFORMS;
    Claim<CPosition>() =
        platform->Get<CPosition>().cur
        + Vector2f{
            0, extractCustomSprite(platform)->GetShiftValue().y
        } * 1.5;
    Claim<CCanCollide>() = true;
    Claim<CTagEnemy>();

    Claim<CPhysics>();
    Claim<CFallVelocity>() = getConfig().simulation.player.fallVelocity / 2;

    Claim<CJump>() = JumpData {
        .maxHeight = 30,
        .duration = 5,
    };

    Log("Created", GetName());
}
