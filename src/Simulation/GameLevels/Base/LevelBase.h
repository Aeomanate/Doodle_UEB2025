#ifndef LEVELBASE_H
#define LEVELBASE_H

#include "EventsHandling/ListenersEmitters.h"
#include "Application/Details/Updatable.h"
#include "LevelDataStorage.h"
#include "Simulation/ECS/ECS.h"

class SEntityPainter;
class SInputInjector;

class LevelBase: public Updatable, public Drawable
{
    template<LevelDataStorage::ChangeLevelPolicy POLICY>
    struct AddHelper
    {
        LevelBase* levelPtr = nullptr;

        template<class EorS, class... Params>
        AddHelper& Add(Params&&... args)
        {
            levelPtr->template Add<EorS, POLICY, Params...>(std::forward<Params>(args)...);
            return *this;
        }
    };

public:
    using LevelUPtr = std::unique_ptr<LevelBase>;

    void Transit(std::unique_ptr<LevelBase> prevLevel);

    template<LevelDataStorage::ChangeLevelPolicy POLICY>
    AddHelper<POLICY> AddSeveral()
    {
        return AddHelper<POLICY>{ this };
    }

    template<class EntOrSys, LevelDataStorage::ChangeLevelPolicy CHANGE_LEVEL_POLICY, class... Params>
    void Add(Params&&... initPack)
    {
        choiceLevelDataStorage<CHANGE_LEVEL_POLICY>().template Add<EntOrSys>(std::forward<Params>(initPack)...);

        auto catchSystem = [this]
            <class CatchingSystem>(CatchingSystem*& catchingSysPtrRef) {
            if constexpr (std::is_convertible_v<EntOrSys, CatchingSystem>)
            {
                catchingSysPtrRef = static_cast<CatchingSystem*>(choiceLevelDataStorage<CHANGE_LEVEL_POLICY>().systems.
                    back().get());
                return true;
            }
            return false;
        };

        if (catchSystem(entityPainter))
        {
            listenerDrawRequest.SubscribeEmitter(entityPainter->emitterDrawRequest);
        }
        catchSystem(inputInjector);
    }

    template<LevelDataStorage::ChangeLevelPolicy CHANGE_LEVEL_POLICY>
    void Take(std::unique_ptr<ECS::Entity>&& freshEntity)
    {
        choiceLevelDataStorage<CHANGE_LEVEL_POLICY>().entities.emplace_back(std::move(freshEntity));
    }

    void Remove(ECS::Entity* entityToRemove)
    {
        bool removed = dataStorageLocal.RemoveEntitiesIf(
            [entityToRemove](const std::unique_ptr<ECS::Entity>& entity) {
                return entity.get() == entityToRemove;
            }
        );

        if (removed)
        {
            return;
        }

        dataStorageTransit.RemoveEntitiesIf(
            [entityToRemove](const std::unique_ptr<ECS::Entity>& entity) {
                return entity.get() == entityToRemove;
            }
        );
    }

public:
    bool Update(float dt) override;
    void Draw(Vector2f pos) const override;

public:
    LevelState GetLevelState() const;
    void SetLevelState(LevelState);

    SInputInjector& GetInputInjector();

    inline auto GetAllEntitiesView()
    {
        return rv::concat(
            dataStorageLocal.entities | rv::transform([](auto& entity) {
                return entity.get();
            }),
            dataStorageTransit.entities | rv::transform([](auto& entity) {
                return entity.get();
            })
        );
    }

public: // Emitters & Listeners
    DATA_EMITTER(LevelCompleted, LevelDataStorageTransit);

    DATA_LISTENER(DrawRequest, DrawNode)
    {
        drawQueue.emplace(std::move(data));
    }

protected:
    LevelBase() = default;

    template<LevelDataStorage::ChangeLevelPolicy CHANGE_LEVEL_POLICY>
    LevelDataStorage& choiceLevelDataStorage()
    {
        if constexpr (CHANGE_LEVEL_POLICY == LevelDataStorage::ChangeLevelPolicy::LOCAL)
        {
            return dataStorageLocal;
        }
        else if constexpr (CHANGE_LEVEL_POLICY == LevelDataStorage::ChangeLevelPolicy::TRANSIT)
        {
            return dataStorageTransit;
        }
    };

private:
    // Called when first entered into an update loop.
    // It collects raw pointers to all systems into one loop-friendly array
    // and sorts them by predefined order.
    void CacheSystems();

private:
    LevelState levelState = LevelState::STARTING;

    LevelDataStorageTransit dataStorageTransit; // From prev level moves to local storage
    LevelDataStorageLocal dataStorageLocal; // Exists only within the current level
    std::vector<ECS::System*> levelSystemsCache{ };

    SEntityPainter* entityPainter = nullptr;
    mutable std::queue<DrawNode> drawQueue{ };

    SInputInjector* inputInjector = nullptr;
};

#endif //LEVELBASE_H
