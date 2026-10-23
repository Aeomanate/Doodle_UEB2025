// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SJump.h"

#include "CFallVelocity.h"
#include "CJump.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/Movable/CCollisions.h"
#include "Simulation/ECS/Features/Movable/CPhysics.h"
#include "Simulation/ECS/Features/LifetimeControl/CTagDespawn.h"

SJump::SJump()
: System(Order::PRE_PHYSICS)
{ }

bool SJump::Update(float dt)
{
    for (ECS::Entity* entity: CJump::AllEntities())
    {
        JumpData& jump = entity->Get<CJump>();

        CheckCollision();

        if (jump.isActive)
        {
            entity->Get<CPhysics>().speed += (
                getConfig().simulation.player.fallVelocity
                + Vector2f{ 0, jump.maxHeight / jump.duration }
            );

            jump.curDuration += dt;
            if (jump.curDuration > jump.duration)
            {
                jump.isActive = false;
                jump.curDuration = 0.0f;
            }
        }
    }
    return true;
}

void SJump::CheckCollision()
{
    for (CollisionData& collision: CCollisions::GetData())
    {
        if (!collision.isBottomTopCollision)
        {
            continue;
        }

        collision.collider1->Get<CJump>().isActive = true;
    }
}
