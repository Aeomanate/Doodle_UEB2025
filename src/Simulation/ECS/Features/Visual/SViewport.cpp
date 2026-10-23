// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "SViewport.h"

#include "CCameraOffset.h"
#include "Application/AppPartGetter.h"
#include "Application/Config/ConfigGeneral.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/Input/CTagPlayerControllable.h"
#include "Simulation/ECS/Features/Movable/CPosition.h"
#include "Simulation/Features/Abilities/Moving/CJump.h"

SViewport::SViewport()
: System(Order::POST_GAMEPLAY)
{
    Get().pos = { 0, 0 };
    Get().size = getConfig().window.screenSize;
}

bool SViewport::Update(float dt)
{
    Vector2f localPlayerPos = CTagPlayerControllable::GetEntity().Get<CPosition>().cur;
    Vector2f localCameraOffset = CCameraOffset::GetData();

    Vector2f screenViewportPos = localCameraOffset - localPlayerPos;

    Get().pos = {
        Get().pos.x,
        -screenViewportPos.y
    };
    return true;
}

Vector2f SViewport::ToScreen(Vector2f inViewport)
{
    return {
        inViewport.x,
        Get().pos.y + SViewport::Get().size.y - inViewport.y
    };
}

Vector2f SViewport::ToLocal(Vector2f screenPoint)
{
    return {
        screenPoint.x,
       Get().pos.y + SViewport::Get().size.y - screenPoint.y
    };
}

RectF& SViewport::Get()
{
    static RectF screenViewport = { };
    return screenViewport;
}

RectF SViewport::GetLocal()
{
    return { ToLocal(Get().pos), Get().size };
}
