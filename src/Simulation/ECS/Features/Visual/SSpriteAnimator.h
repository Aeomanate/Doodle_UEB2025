#ifndef SSPRITEANIMATOR_H
#define SSPRITEANIMATOR_H


#include "Simulation/ECS/System.h"

class SSpriteAnimator: public ECS::System
{
public:
    SSpriteAnimator();

protected:
    bool Update(float dt) override;

};


#endif //SSPRITEANIMATOR_H
