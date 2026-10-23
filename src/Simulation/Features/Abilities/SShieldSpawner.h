#ifndef SSHIELDSPAWNER_H
#define SSHIELDSPAWNER_H
#include "Simulation/ECS/System.h"


class SShieldSpawner: public ECS::System
{
public:
    SShieldSpawner();

    bool Update(float dt) override;

};



#endif //SSHIELDSPAWNER_H
