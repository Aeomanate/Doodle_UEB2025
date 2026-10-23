#ifndef SWALLTRANSFER_H
#define SWALLTRANSFER_H
#include "Simulation/ECS/System.h"


class SWallTransfer: public ECS::System
{
public:
    SWallTransfer();

    bool Update(float dt) override;

};



#endif //SWALLTRANSFER_H
