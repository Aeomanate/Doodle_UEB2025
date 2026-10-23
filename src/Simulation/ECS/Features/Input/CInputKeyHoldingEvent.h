#ifndef CINPUTKEYHOLDINGEVENT_H
#define CINPUTKEYHOLDINGEVENT_H


#include "3rd-party/Framework.h"
#include "Simulation/ECS/Component.h"

struct KeyHoldingEvent
{
    FRKey key;
    bool isKeyHolding;
};

struct CInputKeyHoldingEvent: public ECS::Component<CInputKeyHoldingEvent, std::queue<KeyHoldingEvent>>
{

};

#endif //CINPUTKEYHOLDINGEVENT_H
