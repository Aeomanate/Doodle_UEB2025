#ifndef CPHYSICS_H
#define CPHYSICS_H

#include "Math/Vector2.h"
#include "Simulation/ECS/Component.h"

struct PhysicBody
{
    float mass = 0;
    Vector2f speed;
};

struct CPhysics: ECS::Component<CPhysics, PhysicBody>
{

};

#endif //CPHYSICS_H
