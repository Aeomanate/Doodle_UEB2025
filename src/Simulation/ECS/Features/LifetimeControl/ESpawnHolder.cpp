#include "ESpawnHolder.h"

#include "CNewEntities.h"

ESpawnHolder::ESpawnHolder()
: ECS::Entity("NewEntitiesContainer")
{
    Claim<CNewEntities>();

}
