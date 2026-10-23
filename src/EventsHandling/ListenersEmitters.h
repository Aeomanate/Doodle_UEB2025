#ifndef LISTENERSEMITTERS_H
#define LISTENERSEMITTERS_H


#include "BaseClasses.h"

// Listeners

template<class EventData>
class EventListener: public EventListenerBase<EventData>
{
public:
    using EventHandler = std::function<void(EventData&)>;

public:
    explicit EventListener(EventHandler&& eventHandler)
    : eventHandler{ std::move(eventHandler) }
    { }

    void Receive(EventData& eventData)
    {
        if (!isActive)
        {
            return;
        }
        eventHandler(eventData);
    }

    void SetActive(bool state)
    {
        isActive = state;
    }

protected:
    EventHandler eventHandler;
    bool isActive = true;
};

template<>
class EventListener<void>: public EventListenerBase<void>
{
public:
    using EventHandler = std::function<void()>;

public:
    explicit EventListener(EventHandler&& eventHandler)
    : eventHandler{ std::move(eventHandler) }
    { }

    void Receive() const
    {
        eventHandler();
    }

protected:
    EventHandler eventHandler;
};


// Emitters

template<class EventData>
class EventEmitter: public EventEmitterBase<EventData>
{
public:
    using Base = EventEmitterBase<EventData>;
    using Listener = EventListener<EventData>;

public:
    void Emit(EventData& eventData)
    {
        for (const auto& listener: Base::listeners)
        {
            static_cast<Listener*>(listener)->Receive(eventData);
        }
    }
};


template<>
class EventEmitter<void>: public EventEmitterBase<void>
{
    using Base = EventEmitterBase<void>;
    using Listener = EventListener<void>;

public:
    void Emit()
    {
        for (const auto& listener: Base::listeners)
        {
            static_cast<const Listener*>(listener)->Receive();
        }
    }

private:
};

#define SAME(X) X

#define DATA_LISTENER(Name, EventData)                                                     \
    EventListener<SAME(EventData)> listener##Name { [this] (SAME(EventData)& data) {       \
        On##Name(data);                                                                    \
    }};                                                                                    \
    void On##Name(SAME(EventData)& data)

#define SIMPLE_LISTENER(Name)                      \
    EventListener<void> listener##Name { [this] {  \
        On##Name();                                \
    }};                                            \
    void On##Name()

#define DATA_EMITTER(Name, EventData) \
    EventEmitter<EventData> emitter##Name

#define SIMPLE_EMITTER(Name) \
    EventEmitter<void> emitter##Name
#endif //LISTENERSEMITTERS_H
