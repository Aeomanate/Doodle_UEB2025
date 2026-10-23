#ifndef SCOLLISIONDETECTOR_H
#define SCOLLISIONDETECTOR_H
#include "Simulation/ECS/System.h"


class SCollisionDetector: public ECS::System
{
public:
    SCollisionDetector();

protected:
    bool Update(float dt) override;
};


#endif //SCOLLISIONDETECTOR_H
