#ifndef COMPONENT_H
#define COMPONENT_H
#include "Application/Singleton.h"
#include "Application/Details/Logger.h"


namespace ECS
{
    class Entity;

    // ===================================================================================================

    struct SortedViewBuilder
    {
        template<class Comparator>
        struct Partial
        {
            Comparator comparator = { };

            template<class R>
            auto Sort(R&& range) const
            {
                using Value = r::range_value_t<R>;
                std::vector<Value> vec(r::begin(range), r::end(range));
                r::sort(vec, comparator);
                return vec;
            }

            template<class R>
            friend auto operator|(R&& range, const Partial& partial)
            {
                return partial.Sort(std::forward<R>(range));
            }
        };

        template<class Cmp = std::less<>>
        auto operator()(Cmp cmp = { }) const
        {
            return Partial<Cmp>{ std::move(cmp) };
        }
    };

    template<class... Ts>
    inline auto Concat()
    {
        return std::ranges::concat_view{
            Ts::AllEntities()...
        };
    }

    // ===================================================================================================

    struct EmptyTag
    { };

    class ComponentBase
    {
    public:
        virtual ~ComponentBase() = default;

        virtual void RemoveEntityRequest(Entity*) = 0;
    };

    template<class UserComponent, class UserData = EmptyTag>
    class Component
        : public ComponentBase,
          // Singleton needed to identify a component to correctly remove component from entity.
          public Singleton<Component<UserComponent, UserData>>
    {
        friend class Entity;

    public:
        using KeyEntityT = Entity;
        using KeyEntityPtrT = Entity*;
        using UserDataT = UserData;
        using UserDataPtrT = UserDataT*;
        using UserDataRef = UserData&;

        using UserComponentT = UserComponent;
        using UserComponentPtrT = UserComponent*;

        using StorageT = std::unordered_map<KeyEntityPtrT, UserDataT>;

    public:

        // Preventing a dangling pointer stored in entities if component removed first when the program is closed
        ~Component()
        {
            Log("Destroying component", typeid(*this).name(), Logger::Verbosity::VERBOSE);
            for (const auto& [key, value]: Component::entitiesStorage)
            {
                key->RemoveComponentRequest(this);
            }
        }

        static inline void Clear()
        {
            if (entitiesStorage.empty())
            {
                return;
            }
            Log("Remove component from all entities",
                typeid(Component).name(),
                Logger::Verbosity::VERBOSE);

            for (auto& [entity, _]: entitiesStorage)
            {
                entity->template RemoveComponentRequest(&Component::GetInstance());
            }

            entitiesStorage.clear();
        }

    public: // Utility
        static inline StorageT&& AllMove()
        {
            return std::move(entitiesStorage);
        }

        static inline auto AllEntities()
        {
            return std::views::keys(entitiesStorage);
        }

        static inline auto Filter()
        {
            return std::views::filter([](KeyEntityPtrT node) {
                return entitiesStorage.contains(node);
            });
        }

        static inline auto Sort()
        {
            SortedViewBuilder sortedView;
            return sortedView([](KeyEntityPtrT a, KeyEntityPtrT b) {
                return entitiesStorage[a] < entitiesStorage[b];
            });
        }

        static inline bool Empty()
        {
            return entitiesStorage.empty();
        }

        // For a utility single-entity components
        static inline UserDataPtrT TryGetData()
        {
            return !Empty() ? &entitiesStorage.begin()->second : nullptr;
        }

        static inline Entity& GetEntity()
        {
            return *entitiesStorage.begin()->first;
        }

        static inline UserDataT& GetData()
        {
            return entitiesStorage.begin()->second;
        }

    protected:
        // Used by entity. Don't use it directly,
        // it might be more complicated than access from entity.

        template<class... Params>
        static inline UserDataT& Claim(KeyEntityPtrT entity, Params&&... initFieldsPack)
        {
            auto [it, isEmplaced] = entitiesStorage.emplace(
                entity, UserDataT{ std::forward<Params>(initFieldsPack)... }
            );

            if (!isEmplaced)
            {
                Log("Component already exists on entity", Logger::Verbosity::WARNING);
                return it->second;
            }

            return it->second;
        }

        static inline void Discard(KeyEntityPtrT entity)
        {
            entitiesStorage.erase(entity);
        }

        static inline UserDataPtrT TryGetDataPtrFor(KeyEntityPtrT entity)
        {
            auto it = entitiesStorage.find(entity);
            return it != entitiesStorage.end() ? &it->second : nullptr;
        }

        static inline UserDataT& GetData(KeyEntityPtrT key)
        {
            return entitiesStorage.find(key)->second;
        }

        void RemoveEntityRequest(KeyEntityPtrT entity) override
        {
            auto it = Component::entitiesStorage.find(entity);
            if (!it->first)
            {
                Log("Deletion of entity that doesn't exist", Logger::Verbosity::WARNING);
                return;
            }

            Component::entitiesStorage.erase(it->first);
        }

    private:
        static inline StorageT entitiesStorage;
    };

    // ===================================================================================================

    template<class UserComponent, class UserData>
    struct DependenciesExpander
    {
        using type = Component<UserComponent, UserData>;
    };

    template<class UserComponent>
    using ResolveComponentBaseT = typename DependenciesExpander<
        typename UserComponent::UserComponentT,
        typename UserComponent::UserDataT
    >::type;

    template<class UserComponent>
    concept ECSComponent = std::is_base_of_v<ResolveComponentBaseT<UserComponent>, UserComponent>;
}


#endif //COMPONENT_H
