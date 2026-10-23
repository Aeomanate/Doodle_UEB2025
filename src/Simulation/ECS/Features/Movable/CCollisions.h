#ifndef CCOLLISION_H
#define CCOLLISION_H
#include "Simulation/ECS/Component.h"

struct CollisionData
{
    ECS::Entity* collider1 = nullptr;
    ECS::Entity* collider2 = nullptr;
    bool isBottomTopCollision = false;
};

struct CCollisions: public ECS::Component<CCollisions, std::vector<CollisionData>>
{

};

#endif //CCOLLISION_H
