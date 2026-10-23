#ifndef SDESPAWNER_H
#define SDESPAWNER_H
#include "Simulation/ECS/System.h"


class SDespawner: public ECS::System
{
public:
    SDespawner();

    bool Update(float dt) override;

};



#endif //SDESPAWNER_H
