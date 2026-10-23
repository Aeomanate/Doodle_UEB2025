// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SJetpackController.h"

SJetpackController::SJetpackController()
: System(Order::GAMEPLAY)
{ }

bool SJetpackController::Update(float dt)
{
    return true;
}
