#ifndef SJETPACKCONTROLLER_H
#define SJETPACKCONTROLLER_H
#include "Simulation/ECS/System.h"


class SJetpackController: public ECS::System
{
public:
    SJetpackController();

    bool Update(float dt) override;
};



#endif //SJETPACKCONTROLLER_H
