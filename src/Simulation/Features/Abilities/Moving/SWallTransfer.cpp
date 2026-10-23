// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SWallTransfer.h"

#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/Movable/CPhysics.h"
#include "Simulation/ECS/Features/Movable/CPosition.h"
#include "Simulation/ECS/Features/Visual/SViewport.h"

SWallTransfer::SWallTransfer()
: System(Order::GAMEPLAY)
{ }

bool SWallTransfer::Update(float dt)
{
    for (ECS::Entity* entity: CPhysics::AllEntities())
    {
        Vector2f& pos = entity->Get<CPosition>().cur;
        pos.x = pos.x < 0
                    ? SViewport::Get().size.x
                    : pos.x > SViewport::Get().size.x
                          ? 0
                          : pos.x;
    }

    return true;
}
