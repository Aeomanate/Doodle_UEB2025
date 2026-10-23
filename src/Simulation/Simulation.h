#ifndef SIMULATION_H
#define SIMULATION_H


#include "Application/LowLevelApplication.h"
#include "EventsHandling/ListenersEmitters.h"
#include "Application/Details/Updatable.h"
#include "ECS/Features/Visual/SEntityPainter.h"
#include "Math/Vector2.h"

class LevelBase;

class Simulation: public Updatable, public Drawable
{
public:
    void Init();

    bool Update(float dt) override;

    void Draw(Vector2f pos) const override;

private: // listeners
    DATA_LISTENER(KeyPressed, FRKey);
    DATA_LISTENER(KeyReleased, FRKey);
    DATA_LISTENER(MouseButtonClicked, FRMouseButtonClick);
    DATA_LISTENER(MouseMoved, Vector2i);

private:
    LevelBase* currentLevel = nullptr;
    float passedTime = 0.0f;
    float lastUpdateTime = 0.0f;
};


#endif //SIMULATION_H
