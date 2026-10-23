#include "SInputCleaner.h"
#include "CInputMousePositions.h"
#include "CInputKeyHoldingEvent.h"
#include "CInputMouseClicks.h"


SInputCleaner::SInputCleaner()
: ECS::System(Order::GARBAGE_COLLECTOR)
{ }

bool SInputCleaner::Update(float)
{
    auto popHandledElement = [] (auto queuePtr)
    {
        if(queuePtr and !queuePtr->empty())
        {
            Log("Cleaning", typeid(*queuePtr).name(), Logger::Verbosity::GABBY);
            queuePtr->pop();
        }
    };

    popHandledElement(CInputMousePositions::TryGetData());
    popHandledElement(CInputMouseClicks::TryGetData());
    popHandledElement(CInputKeyHoldingEvent::TryGetData());
    return true;
}
