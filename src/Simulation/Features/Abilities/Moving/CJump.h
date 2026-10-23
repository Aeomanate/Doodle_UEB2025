#ifndef JUMP_H
#define JUMP_H
#include "Simulation/ECS/Component.h"

struct JumpData
{
    bool isActive = false;
    float maxHeight = 0.0f;
    float duration = 0.0f;
    float curDuration = 0.0f;
};

struct CJump: public ECS::Component<CJump, JumpData>
{

};



#endif //JUMP_H
