#ifndef SENTITYMOVER_H
#define SENTITYMOVER_H


#include "Simulation/ECS/System.h"

class SEntityMover: public ECS::System
{
public:
    SEntityMover();

protected:
    bool Update(float dt) override;

public:

};



#endif //SENTITYMOVER_H
