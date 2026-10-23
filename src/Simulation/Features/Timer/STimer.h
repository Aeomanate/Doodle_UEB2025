#ifndef STIMER_H
#define STIMER_H

#include "Simulation/ECS/System.h"

class STimer: public ECS::System
{
public:
    STimer();

protected:
    bool Update(float dt) override;
};

#endif //STIMER_H
