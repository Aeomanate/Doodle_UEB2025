#ifndef EPLATFORM_H
#define EPLATFORM_H
#include "Math/Vector2.h"
#include "Simulation/ECS/Entity.h"


class EPlatform: public ECS::Entity
{
public:
    EPlatform(Vector2f position);

private:
    inline static unsigned int platformCount = 0;
};


#endif //EPLATFORM_H
