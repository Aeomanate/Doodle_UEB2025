#include "SDebugInfo.h"


#include "Application/Details/Logger.h"
#include "Simulation/ECS/ECS.h"

SDebugInfo::SDebugInfo()
: System(Order::GAMEPLAY)
{ }

bool SDebugInfo::Update(float dt)
{
    auto* mousePosQueuePtr = CInputMousePositions::TryGetData();
    if (!mousePosQueuePtr)
    {
        Log("Tried to get mouse position but failed", Logger::Verbosity::WARNING);
    }
    if(mousePosQueuePtr->empty())
    {
        return true;
    }

    auto [mouse_x, mouse_y] = mousePosQueuePtr->front();


    CText::TryGetData()->SetString(std::format(
        "Mouse pos: [{:4}; {:4}]",
        mouse_x, mouse_y
    ));

    return true;
}
