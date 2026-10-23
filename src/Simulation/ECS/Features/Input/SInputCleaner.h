#ifndef SINPUTCLEANER_H
#define SINPUTCLEANER_H


#include "Simulation/ECS/System.h"

class SInputCleaner: public ECS::System
{
public:
    SInputCleaner();

    bool Update(float queueComponent) override;
};


#endif //SINPUTCLEANER_H
