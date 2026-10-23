#ifndef SINPUTINJECTOR_H
#define SINPUTINJECTOR_H


#include "Simulation/ECS/System.h"
#include "CInputKeyHoldingEvent.h"
#include "CInputMouseClicks.h"
#include "CInputMousePositions.h"

struct PendingInputActions
{
    std::optional<KeyHoldingEvent> keyHoldingEvent;
    std::optional<Vector2f> mouseClick;
    std::optional<Vector2f> mousePos;
};

class SInputInjector: public ECS::System
{
protected:
    bool Update(float dt) override;

public:
    SInputInjector();

    void InjectKeyEvent(KeyHoldingEvent&& keyHoldingEvent);
    void InjectMouseClick(Vector2f position);
    void InjectMousePosition(Vector2f position);

private:
    PendingInputActions pendingInputActions;
};


#endif //SINPUTINJECTOR_H
