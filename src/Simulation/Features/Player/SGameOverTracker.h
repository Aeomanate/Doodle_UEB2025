#ifndef SGAMEOVERTRACKER_H
#define SGAMEOVERTRACKER_H
#include "Simulation/ECS/System.h"


class SGameOverTracker: public ECS::System
{
public:
    SGameOverTracker();

    bool Update(float dt) override;
};


#endif //SGAMEOVERTRACKER_H
