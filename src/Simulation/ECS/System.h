#ifndef SYSTEM_H
#define SYSTEM_H

#include "Application/Details/Updatable.h"

namespace ECS
{
    class System : public Updatable
    {
    protected:
        enum class Order
        {
            ENTITY_CREATION,
            ENTITY_ACTIVATION,
            INPUT_INJECT,
            INPUT_PROPAGATE,
            PRE_PHYSICS,
            SPEED_BOOST,
            PHYSICS,
            GAMEPLAY,
            POST_GAMEPLAY,
            RENDER,
            GARBAGE_COLLECTOR,
        };

    public:
        inline System(Order order)
        : order { order }
        { }

        ~System() override = default;

        bool operator< (const System& other) const
        {
            return order < other.order;
        }

    private:
        Order order;
    };
}

#endif //SYSTEM_H
