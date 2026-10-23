#ifndef CSHIELD_H
#define CSHIELD_H
#include "Simulation/ECS/Component.h"

struct ShieldData
{
    float duration = 0.0f;
    float curDuration = 0.0f;
};

struct CShield: public ECS::Component<CShield>
{

};

#endif //CSHIELD_H
