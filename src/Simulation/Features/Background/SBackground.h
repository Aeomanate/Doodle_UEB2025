#ifndef SBACKGROUND_H
#define SBACKGROUND_H
#include "Simulation/ECS/System.h"


class SBackground: public ECS::System
{
public:
    SBackground();

    bool Update(float dt) override;

};



#endif //SBACKGROUND_H
