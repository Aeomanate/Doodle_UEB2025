#ifndef APPLICATION_H
#define APPLICATION_H

#include "EventsHandling/ListenersEmitters.h"
#include "Singleton.h"
#include "LowLevelApplication.h"
#include "Config/ConfigGeneral.h"


class Application : public LowLevelApplication, public Singleton<Application>
{
    friend class Singleton<Application>;
public:
    int Run(std::optional<ConfigWindow> configWindow) override;
    unsigned TimeSinceStartMs() const;

private: // Game-related methods
    bool Init() override;
    void Update(float dt) override;
    void Draw(Vector2f pos) const;
    void Close() override;

private: // Listeners
    SIMPLE_LISTENER(LastMenuClosed);
    DATA_LISTENER(KeyEvent, FRKey);

protected:
    void InitListeners();
    void InitGameRelated();
};

#endif
