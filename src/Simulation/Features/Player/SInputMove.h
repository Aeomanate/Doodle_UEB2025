#ifndef SINPUTHANDLER_H
#define SINPUTHANDLER_H


#include "3rd-party/Framework.h"
#include "Simulation/ECS/System.h"
#include "Math/Vector2.h"

class SInputMove: public ECS::System
{
public:
    SInputMove();

    bool Update(float dt) override;

private:
    void handleMovingPlayer();

private:
    using KeyToMoveF = Vector2i(*)();
    std::unordered_map<FRKey, KeyToMoveF> moveMapping;

    Vector2i currentMoveDir;
};

#endif //SINPUTHANDLER_H
