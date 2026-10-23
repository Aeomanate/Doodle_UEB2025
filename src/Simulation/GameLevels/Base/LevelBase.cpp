#include "LevelBase.h"
#include "Simulation/ECS/ECS.h"

void LevelBase::Transit(std::unique_ptr<LevelBase> prevLevel)
{
    dataStorageTransit = std::move(prevLevel->dataStorageTransit);
    entityPainter = prevLevel->entityPainter;
    inputInjector = prevLevel->inputInjector;
    prevLevel->entityPainter = nullptr;
    prevLevel->inputInjector = nullptr;
}

bool LevelBase::Update(float dt)
{
    if(levelSystemsCache.empty())
    {
        CacheSystems();
    }

    for (auto& system: levelSystemsCache)
    {
        Log("Updating system", typeid(*system).name(), Logger::Verbosity::GABBY);
        system->Update(dt);
    }

    return levelState == LevelState::RUNNING;
}

void LevelBase::Draw(Vector2f pos) const
{
    while (!drawQueue.empty())
    {
        drawQueue.front().sprite->Draw(pos + drawQueue.front().position);
        drawQueue.pop();
    }
}

LevelState LevelBase::GetLevelState() const
{
    return levelState;
}

void LevelBase::SetLevelState(LevelState newLevelState)
{
    levelState = newLevelState;
}

SInputInjector& LevelBase::GetInputInjector()
{
    return *inputInjector;
}


void LevelBase::CacheSystems()
{
    std::array<LevelDataStorage*, 2> levelDataStorages {
        &dataStorageTransit,
        &dataStorageLocal
    };

    std::size_t totalSystems = 0;
    for(const auto& levelDataStorage: levelDataStorages)
    {
        totalSystems += levelDataStorage->systems.size();
    }

    levelSystemsCache.reserve(totalSystems);

    for(auto& levelDataStorage: levelDataStorages)
    {
        for(auto& system: levelDataStorage->systems)
        {
            levelSystemsCache.emplace_back(system.get());
        }
    }

    std::ranges::sort(levelSystemsCache, [] (const ECS::System* a, const ECS::System* b) { return *a < *b; });
}
