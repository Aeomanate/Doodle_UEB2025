#ifndef SLEVELSTATEFORWARDER_H
#define SLEVELSTATEFORWARDER_H


#include "Simulation/ECS/System.h"

class SLevelStateObserver: public ECS::System
{
protected:
    bool Update(float) override;

public:
    SLevelStateObserver();
};


#endif //SLEVELSTATEFORWARDER_H
