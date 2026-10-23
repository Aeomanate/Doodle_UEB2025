#ifndef SDEBUGINFO_H
#define SDEBUGINFO_H


#include "Simulation/ECS/System.h"

class SDebugInfo : public ECS::System
{
public:
    SDebugInfo();

public:
    bool Update(float configTexture) override;
};


#endif //SDEBUGINFO_H
