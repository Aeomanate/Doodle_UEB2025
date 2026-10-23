#ifndef SHANDLERPLAYERSHOOT_H
#define SHANDLERPLAYERSHOOT_H


#include "Simulation/ECS/System.h"

class SInputShoot: public ECS::System
{
public:
    SInputShoot();

    bool Update(float dt) override;

public:


};


#endif //SHANDLERPLAYERSHOOT_H
