#include "STimer.h"
#include "CTimer.h"
#include "Simulation/ECS/Entity.h"

STimer::STimer()
: System(Order::GAMEPLAY)
{ }

bool STimer::Update(float dt)
{
    float* timer = CTimer::TryGetData();
    if (!timer)
    {
        Log("CTimer absent", Logger::Verbosity::WARNING);
    }

    *timer += dt;

    return true;
}
