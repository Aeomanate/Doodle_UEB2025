#ifndef CPLATFORMSTORAGE_H
#define CPLATFORMSTORAGE_H
#include "Simulation/ECS/Component.h"

struct CPlatformsStorage: public ECS::Component<CPlatformsStorage, std::vector<ECS::Entity*>>
{

};

#endif //CPLATFORMSTORAGE_H
