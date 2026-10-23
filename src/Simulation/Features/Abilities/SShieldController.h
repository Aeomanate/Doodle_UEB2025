#ifndef SSHIELDCONTROLLER_H
#define SSHIELDCONTROLLER_H
#include "Simulation/ECS/System.h"


class SShieldController: ECS::System
{
public:
    SShieldController();

    bool Update(float dt) override;

};



#endif //SSHIELDCONTROLLER_H
