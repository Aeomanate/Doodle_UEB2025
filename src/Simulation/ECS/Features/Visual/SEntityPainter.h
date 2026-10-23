#ifndef SENTITYDRAWER_H
#define SENTITYDRAWER_H


#include "CSceneElement.h"
#include "EventsHandling/ListenersEmitters.h"
#include "Math/Vector2.h"
#include "Simulation/ECS/System.h"

struct DrawNode
{
    const CustomSprite* sprite;
    Vector2f position;
};

class SEntityPainter: public ECS::System
{
public:
    SEntityPainter();

public:
    DATA_EMITTER(DrawRequest, DrawNode);

protected:
    bool Update(float) override;

};


#endif //SENTITYDRAWER_H
