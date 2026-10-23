#include "SSpriteAnimator.h"
#include "CSceneElement.h"

SSpriteAnimator::SSpriteAnimator()
: System(Order::GAMEPLAY)
{

}

bool SSpriteAnimator::Update(float dt)
{
    return true;
}
