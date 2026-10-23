#ifndef SJUMP_H
#define SJUMP_H
#include "CJump.h"
#include "Simulation/ECS/System.h"


class SJump: public ECS::System
{
public:
    SJump();

    bool Update(float dt) override;

    void CheckCollision();
};



#endif //SJUMP_H
