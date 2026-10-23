// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SCollisionDetector.h"

#include "CCanCollide.h"
#include "CCollisions.h"
#include "CPhysics.h"
#include "CPosition.h"
#include "Math/Rect.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/LifetimeControl/CActivityTags.h"
#include "Simulation/ECS/Features/Visual/CSceneElement.h"
#include "Simulation/Features/Platforms/CTagPlatform.h"

SCollisionDetector::SCollisionDetector()
: System(Order::POST_GAMEPLAY)
{ }

bool SCollisionDetector::Update(float dt)
{
    CCollisions::GetData().clear();

    for (ECS::Entity* movable: CPhysics::AllEntities())
    {
        const CustomSprite* movableSprite = extractCustomSprite(movable);
        RectF prev = movableSprite->GetScreenRect(movable->Get<CPosition>().prev);
        RectF cur = movableSprite->GetScreenRect(movable->Get<CPosition>().cur);

        for (ECS::Entity* fixed: ECS::Concat<CSprite, CAnimation>())
        {
            if (movable == fixed || !fixed->Get<CCanCollide>())
            {
                continue;
            }
            RectF target = extractCustomSprite(fixed)->GetScreenRect(fixed->Get<CPosition>().cur);

            if (cur.IntersectAABB(target))
            {
                bool isBottomTopIntersect = CheckBottomTopIntersect(prev, cur, target);
                CCollisions::GetData().push_back({
                    movable,
                    fixed,
                    isBottomTopIntersect
                });

                if (isBottomTopIntersect)
                {
                    Log("Bottom - Top collision",
                        std::format("{} above {}", movable->GetName(), fixed->GetName()),
                        Logger::Verbosity::VERBOSE);
                }
            }
        }
    }
    return true;
}
