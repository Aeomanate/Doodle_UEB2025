#ifndef SPOSDEPENDENTSPEED_H
#define SPOSDEPENDENTSPEED_H
#include "Simulation/ECS/System.h"


class SSpeedBoosterHalfScreen: public ECS::System
{
public:
    SSpeedBoosterHalfScreen();

    bool Update(float dt) override;

};



#endif //SPOSDEPENDENTSPEED_H
