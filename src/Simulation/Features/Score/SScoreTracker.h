#ifndef SSCORETRACKER_H
#define SSCORETRACKER_H


#include "Simulation/ECS/System.h"

class SScoreTracker: public ECS::System
{
public:
    SScoreTracker();

    bool Update(float dt) override;


};


#endif //SSCORETRACKER_H
