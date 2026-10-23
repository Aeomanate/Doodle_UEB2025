// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "CSpeedBooster.h"
#include "SSpeedBoosterHAlfScreen.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/Input/CTagPlayerControllable.h"
#include "Simulation/ECS/Features/Movable/CPhysics.h"
#include "Simulation/ECS/Features/Movable/CPosition.h"
#include "Simulation/ECS/Features/Visual/SViewport.h"

SSpeedBoosterHalfScreen::SSpeedBoosterHalfScreen()
: System(Order::SPEED_BOOST)
{ }

bool SSpeedBoosterHalfScreen::Update(float dt)
{
    ECS::Entity& player = CTagPlayerControllable::GetEntity();
    {
        if (player.Get<CPosition>().cur.x > SViewport::Get().size.x / 2)
        {
            player.Get<CSpeedBooster>() = Vector2f { 1.5, 1.5 };
        } else
        {
            player.Get<CSpeedBooster>() = Vector2f { 1, 1 };
        }
    }

    player.Get<CPhysics>().speed *= player.Get<CSpeedBooster>();

    return true;
}
