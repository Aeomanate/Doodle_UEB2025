#ifndef CCAMERAOFFSET_H
#define CCAMERAOFFSET_H
#include "Simulation/ECS/Component.h"
#include "Math/Vector2.h"

struct CCameraOffset: public ECS::Component<CCameraOffset, Vector2f>
{

};

#endif //CCAMERAOFFSET_H
