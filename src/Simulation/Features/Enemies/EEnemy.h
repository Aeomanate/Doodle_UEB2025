#ifndef EENEMY_H
#define EENEMY_H
#include "Simulation/ECS/Entity.h"
#include "Simulation/Features/Platforms/EPlatform.h"


class EEnemy: public ECS::Entity
{
public:
    EEnemy(Entity* platform);
};


#endif //EENEMY_H
