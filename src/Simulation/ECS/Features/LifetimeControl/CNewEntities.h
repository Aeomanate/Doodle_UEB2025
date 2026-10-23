#ifndef CTOSPAWNQUEUE_H
#define CTOSPAWNQUEUE_H

#include "Simulation/ECS/Component.h"
#include "Simulation/ECS/Entity.h"

struct CNewEntities: public ECS::Component<CNewEntities, std::vector<std::unique_ptr<ECS::Entity>>>
{
    
};

#endif //CTOSPAWNQUEUE_H
