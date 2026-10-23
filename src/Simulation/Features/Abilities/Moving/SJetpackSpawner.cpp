// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SJetpackSpawner.h"

SJetpackSpawner::SJetpackSpawner()
: System(Order::GAMEPLAY)
{ }

bool SJetpackSpawner::Update(float dt)
{
    return true;
}
