// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SShieldController.h"

SShieldController::SShieldController()
: System(Order::GAMEPLAY)
{ }

bool SShieldController::Update(float dt)
{
    return true;
}
