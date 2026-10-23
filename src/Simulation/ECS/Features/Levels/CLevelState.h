#ifndef CLEVELSTATE_H
#define CLEVELSTATE_H

#include "Simulation/ECS/Component.h"

enum class LevelState
{
    STARTING,
    RUNNING,
    COMPLETED
};

struct CLevelState: public ECS::Component<CLevelState, LevelState>
{

};

#endif //CLEVELSTATE_H
