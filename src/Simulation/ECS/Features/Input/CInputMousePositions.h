#ifndef CINPUTMOUSEPOSITIONS_H
#define CINPUTMOUSEPOSITIONS_H

#include "Simulation/ECS/Component.h"
#include "Math/Vector2.h"

struct CInputMousePositions: public ECS::Component<CInputMousePositions, std::queue<Vector2f>>
{

};

#endif //CINPUTMOUSEPOSITIONS_H
