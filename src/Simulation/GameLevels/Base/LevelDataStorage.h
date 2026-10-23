#ifndef LEVELDATASTORAGE_H
#define LEVELDATASTORAGE_H

#include "Simulation/ECS/Entity.h"
#include "Simulation/ECS/System.h"

struct LevelDataStorage
{
    enum class ChangeLevelPolicy
    {
        UNDEFINED,
        LOCAL,
        TRANSIT
    };

    template<class EntOrSys, class... Params>
    auto& Add(Params&&... initPack)
    {
        if constexpr (std::is_base_of_v<ECS::System, EntOrSys>)
        {
            return systems.emplace_back(std::make_unique<EntOrSys>(std::forward<Params>(initPack)...));
        }
        else
        {
            return entities.emplace_back(std::make_unique<EntOrSys>(std::forward<Params>(initPack)...));
        }
    }

    template<typename Predicate>
    bool RemoveEntitiesIf(Predicate pred)
    {
        std::size_t sizeBefore = entities.size();
        entities.erase(
            std::remove_if(entities.begin(), entities.end(), pred),
            entities.end()
        );
        return sizeBefore != entities.size();
    }

    std::vector<std::unique_ptr<ECS::Entity>> entities;
    std::vector<std::unique_ptr<ECS::System>> systems;
};

struct LevelDataStorageTransit: public LevelDataStorage
{ };

struct LevelDataStorageLocal: public LevelDataStorage
{ };

#endif //LEVELDATASTORAGE_H
