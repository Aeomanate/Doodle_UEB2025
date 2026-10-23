#include "SScoreTracker.h"

SScoreTracker::SScoreTracker()
: System(Order::POST_GAMEPLAY)
{ }

bool SScoreTracker::Update(float dt)
{
    return true;
}
