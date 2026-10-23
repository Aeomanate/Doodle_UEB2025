#include "SSpawner.h"

#include "CActivityTags.h"
#include "CTagDespawn.h"
#include "CNewEntities.h"
#include "Application/AppPartGetter.h"
#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/Features/Visual/CSceneElement.h"
#include "Simulation/GameLevels/Base/LevelsManager.h"

SSpawner::SSpawner()
: ECS::System(ECS::System::Order::ENTITY_ACTIVATION)
{

}

bool SSpawner::Update(float dt)
{
    for (std::unique_ptr<ECS::Entity>& freshEntity: CNewEntities::GetData())
    {
        Log("Adding new entity to the level", freshEntity->GetName(), Logger::Verbosity::GABBY);
        freshEntity->Claim<CTagActive>();
        getLevelsManager().GetCurrentLevel().Take<LevelDataStorage::ChangeLevelPolicy::LOCAL>(std::move(freshEntity));
    }
    CNewEntities::GetData().clear();
    return true;
}
