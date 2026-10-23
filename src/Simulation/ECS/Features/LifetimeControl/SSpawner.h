#ifndef SSPAWNER_H
#define SSPAWNER_H


#include "Simulation/ECS/System.h"

class SSpawner: public ECS::System
{
public:
    SSpawner();

    bool Update(float dt) override;
};


#endif //SSPAWNER_H
