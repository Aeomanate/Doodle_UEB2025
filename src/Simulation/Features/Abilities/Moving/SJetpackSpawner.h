#ifndef SJETPACKSPAWNER_H
#define SJETPACKSPAWNER_H
#include "Simulation/ECS/System.h"


class SJetpackSpawner: public ECS::System
{
public:
    SJetpackSpawner();

    bool Update(float dt) override;
};



#endif //SJETPACKSPAWNER_H
