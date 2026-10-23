#include "EInputContainer.h"
#include "CInputMousePositions.h"
#include "CInputMouseClicks.h"
#include "CInputKeyHoldingEvent.h"


EInputContainer::EInputContainer()
: ECS::Entity("InputContainer")
{
    Claim<CInputMouseClicks>();
    Claim<CInputMousePositions>();
    Claim<CInputKeyHoldingEvent>();
}
