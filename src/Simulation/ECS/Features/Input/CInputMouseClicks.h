#ifndef CINPUTMOUSECLICKS_H
#define CINPUTMOUSECLICKS_H

#include "Simulation/ECS/Component.h"
#include "Math/Vector2.h"

struct CInputMouseClicks: public ECS::Component<CInputMouseClicks, std::queue<Vector2f>>
{

};

#endif //CINPUTMOUSECLICKS_H
