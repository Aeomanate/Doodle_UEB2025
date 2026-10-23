#ifndef SFALL_H
#define SFALL_H
#include "Simulation/ECS/System.h"


class SFall: public ECS::System
{
public:
    SFall();

    bool Update(float dt) override;
};


#endif //SFALL_H
