#ifndef CPLAYERSCORE_H
#define CPLAYERSCORE_H

#include "Simulation/ECS/Component.h"

struct PlayerScore
{
    unsigned distance  = 0;
    unsigned platforms = 0.0f;
};

struct CPlayerScore: public ECS::Component<CPlayerScore>
{

};

#endif //CPLAYERSCORE_H
