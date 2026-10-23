// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SFall.h"

#include "CFallVelocity.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/Movable/CPhysics.h"

SFall::SFall()
: System(Order::PRE_PHYSICS)
{ }

bool SFall::Update(float dt)
{
    for (ECS::Entity* entity: CFallVelocity::AllEntities())
    {
        entity->Get<CPhysics>().speed += -entity->Get<CFallVelocity>();
    }
    return true;
}
