#include "SEntityMover.h"
#include "Application/Details/Logger.h"

#include "Simulation/ECS/ECS.h"
#include "Math/Vector2.h"
#include "Simulation/ECS/Features/LifetimeControl/CActivityTags.h"
#include "Simulation/Features/Abilities/Moving/CSpeedBooster.h"

SEntityMover::SEntityMover()
: ECS::System(Order::PHYSICS)
{ }

bool SEntityMover::Update(float dt)
{
    for(ECS::Entity* entity: CPosition::AllEntities() | CTagActive::Filter() | CPhysics::Filter())
    {
        PhysicBody* physics = entity->TryGet<CPhysics>();
        if (!physics)
        {
            continue;
        }
        Vector2f& v = physics->speed;
        if(v.IsZero())
        {
            continue;
        }

        ScenePosition& pos = entity->Get<CPosition>();

        pos.prev = pos.cur;
        pos.cur += v * dt;

        // Log("Moving entity",
        //     std::format("P: {}; V: {}", pos.cur, v),
        //     Logger::Verbosity::VERBOSE);

        physics->speed = Vector2f{0, 0};
    }
    return true;
}
