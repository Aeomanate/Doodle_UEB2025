#include "SInputShoot.h"
#include "CCannon.h"
#include "CRequestFire.h"
#include "Simulation/ECS/ECS.h"

SInputShoot::SInputShoot()
: System(Order::INPUT_PROPAGATE)
{ }

bool SInputShoot::Update(float dt)
{
    auto* clickQueue = CInputMouseClicks::TryGetData();
    if (!clickQueue)
    {
        Log("CInputMouseClicks absent for player", Logger::Verbosity::CRITICAL);
    }

    if (clickQueue->empty())
    {
        return true;
    }

    CTagPlayerControllable::GetEntity().Claim<CRequestFire>();

    return true;
}
