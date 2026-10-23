#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"

namespace ECS
{
    class Entity
    {
        template<class UserComponent>
        using UserDataT = typename ResolveComponentBaseT<UserComponent>::UserDataT;

        template <class UserComponent, class UserData>
        friend class Component;

    public:
        explicit Entity(std::string name)
        : name{ std::move(name) }
        { }

        virtual ~Entity() noexcept
        {
            Log("Destroying entity", name, Logger::Verbosity::VERBOSE);
            for (ECS::ComponentBase* component: attachedComponents)
            {
                component->RemoveEntityRequest(this);
            }
        }

    public:
        template<ECSComponent UserComponent, class... Params>
        UserDataT<UserComponent>& Claim(Params&&... initFieldsPack)
        {
            Log("Claiming component",
                format("For entity '{}' <- '{}'", name, typeid(UserComponent).name()),
                Logger::Verbosity::GABBY);
            using CBase = ResolveComponentBaseT<UserComponent>;
            attachedComponents.insert(&CBase::GetInstance());
            return CBase::Claim(this, std::forward<Params>(initFieldsPack)...);
        }

        template<ECSComponent UserComponent>
        Entity& Discard()
        {
            using CBase = ResolveComponentBaseT<UserComponent>;
            if (attachedComponents.erase(&CBase::GetInstance()))
            {
                CBase::Discard(this);
            }
            return *this;
        }

        template<ECSComponent UserComponent>
        UserDataT<UserComponent>* TryGet()
        {
            return ResolveComponentBaseT<UserComponent>::TryGetDataPtrFor(this);
        }

        template<ECSComponent UserComponent>
        const UserDataT<UserComponent>* TryGet() const
        {
            return ResolveComponentBaseT<UserComponent>::TryGetDataPtrFor(this);
        }

        template<ECSComponent UserComponent>
        UserDataT<UserComponent>& Get()
        {
            return ResolveComponentBaseT<UserComponent>::GetData(this);
        }

        template<ECSComponent UserComponent>
        bool Has()
        {
            return TryGet<UserComponent>();
        }

        std::string GetName() const
        {
            return name;
        }

    protected:
        // Usage in component destructor
        void RemoveComponentRequest(ComponentBase* component)
        {
            attachedComponents.erase(component);
        }

    private:
        std::string name;
        std::unordered_set<ECS::ComponentBase*> attachedComponents;
    };
}


#endif //ENTITY_H
