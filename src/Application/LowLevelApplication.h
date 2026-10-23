#ifndef LOWLEVELAPPLICATION_H
#define LOWLEVELAPPLICATION_H

#include "EventsHandling/ListenersEmitters.h"
#include "3rd-party/Framework.h"
#include "Math/Vector2.h"
#include "Singleton.h"
#include "Config/ConfigGeneral.h"

struct FRMouseButtonClick
{
    Vector2i position;
    FRMouseButton button = FRMouseButton::NONE;
    bool isPressed = false;
};


class LowLevelApplication: public AeoGameFramework
{
public:
    LowLevelApplication();
    ~LowLevelApplication() override = default;

protected: // High-level callbacks
    virtual int Run(std::optional<ConfigWindow>);
    bool Init() override;
    virtual void Update(float dt) = 0;
    virtual void Draw(Vector2f pos) const = 0;
    void Close() override;


public: // Emitters
    DATA_EMITTER(KeyPressed, FRKey);
    DATA_EMITTER(KeyReleased, FRKey);
    DATA_EMITTER(MouseClicked, FRMouseButtonClick);
    DATA_EMITTER(MouseMoved, Vector2i);

private: // Window-handling methods
    void OnKeyPressed(FRKey k) override;
    void OnKeyReleased(FRKey k) override;

    void OnMouseMove(int x, int y, int xrelative, int yrelative) override;
    void OnMouseButtonPressed(FRMouseButton button) override;
    void OnMouseButtonReleased(FRMouseButton button) override;

private: // Framework
    bool Tick() override;

protected:
    bool isWorking = true;

private:
    Vector2i lastMousePos;
    unsigned msPassed = 0;
};

#endif //LOWLEVELAPPLICATION_H
