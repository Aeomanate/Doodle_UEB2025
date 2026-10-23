// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SBackground.h"

#include "CTagBackground.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/Movable/CPosition.h"
#include "Simulation/ECS/Features/Visual/SViewport.h"

SBackground::SBackground()
: System(Order::GAMEPLAY)
{ }

bool SBackground::Update(float dt)
{
    CTagBackground::GetEntity().Get<CPosition>() = SViewport::Get().pos + Vector2f{ 0, SViewport::Get().size.y };

    return true;
}
