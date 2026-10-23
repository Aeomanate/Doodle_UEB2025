#include "SInputInjector.h"

#include "Application/Details/Logger.h"
#include "Math/Vector2.h"

template<class CInputQueue, class ActionT>
void injectPendingAction (std::optional<ActionT>& action)
{
    if(action)
    {
        auto actionsQueue = CInputQueue::TryGetData();
        if (!actionsQueue)
        {
            Log("No properly set actionsQueue");
        }

        actionsQueue->push(*action);

        action = std::nullopt;
    }
};

bool SInputInjector::Update(float)
{
    injectPendingAction<CInputMouseClicks>(pendingInputActions.mouseClick);
    injectPendingAction<CInputMousePositions>(pendingInputActions.mousePos);
    injectPendingAction<CInputKeyHoldingEvent>(pendingInputActions.keyHoldingEvent);
    return true;
}

SInputInjector::SInputInjector()
: ECS::System(ECS::System::Order::INPUT_INJECT)
{ }

void SInputInjector::InjectKeyEvent(KeyHoldingEvent&& keyHoldingEvent)
{
    pendingInputActions.keyHoldingEvent = keyHoldingEvent;
}

void SInputInjector::InjectMouseClick(Vector2f position)
{
    pendingInputActions.mouseClick = position;
}

void SInputInjector::InjectMousePosition(Vector2f position)
{
    pendingInputActions.mousePos = position;
}
