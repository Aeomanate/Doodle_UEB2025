#ifndef CPOSITION_H
#define CPOSITION_H


#include "Simulation/ECS/Component.h"
#include "Math/Vector2.h"

struct ScenePosition
{
    Vector2f cur{};
    Vector2f prev{};

    ScenePosition& operator=(const Vector2f& pos)
    {
        cur = prev = pos;
        return *this;
    }
};

struct CPosition: public ECS::Component<CPosition, ScenePosition>
{

};


#endif //CPOSITION_H
